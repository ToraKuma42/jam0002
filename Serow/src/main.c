/**
 * Use Plan9 regular expressions and dependent typing to compile walkable ASTs.
 * Low level pattern match is done with lambda calculus to modify the AST.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>

#include "lang/tokenizer.h"
#include "lang/regex.h"
#include "lib/resources.h"

int16_t global_resource_count = 0;
int string_buffer_len = GLOBAL_STRING_BUFFER_LEN;
size_t token_buffer_len = GLOBAL_TOKEN_BUFFER_LEN;

char *global_string_buffer = NULL;
char *global_token_buffer = NULL;
size_t token_buffer_idx = 0;

/**
 * Main entry point for Serow lang.
 */
int
main(int argc, char* argv[])
{
  if (argc < 2) {
    puts("No input files provided.");
    return 0;
  }

  // TODO: Compile lazy list of resources to compile
  // TODO: Iterate on list above
  // Init global resources at bootstrap
  global_string_buffer =
    (char *) global_resource_alloc_default(
      malloc(GLOBAL_STRING_BUFFER_LEN * sizeof(char)),
      "Error! Could not allocate memory"
    );

  global_token_buffer =
    (char *) global_resource_alloc_default(
      malloc(GLOBAL_TOKEN_BUFFER_LEN * sizeof(char)),
      "Error! Could not allocate memory"
    );

  // Get file size
  FILE* resource_file =
    (FILE *) global_resource_alloc_named(
      fopen(argv[1], "r+"),
      "Error! Could not open file %s",
      argv[1],
      &file_destructor
    );

  fseek(resource_file, 0, SEEK_END);
  size_t resource_file_size = ftell(resource_file);
  fseek(resource_file, 0, SEEK_SET);

  char *file_buffer =
    (char *) global_resource_alloc_default_named(
      malloc(resource_file_size * sizeof(char)),
      "Error! Could not allocate memory for file %s",
      argv[1]
    );

  // Read program into buffer
  fread(file_buffer, sizeof(char), resource_file_size, resource_file);

  // Decrement to handle NULL at end of resource
  resource_file_size--;

  // Starting state of lexer
  enum lex_state_t lex_state = LEX_STATE_START;
  int word_len = 0;
  size_t line_count = 1;

  // Lexing phase
  for (size_t i = 0; i < resource_file_size;) {
    char c = file_buffer[i];

    switch (lex_state) {
      case LEX_STATE_START:
      case LEX_STATE_WHITESPACE:
        // Initial state of table
        if (isalpha(c) || c == '_') {
          lex_state = LEX_STATE_WORD;
          word_len++;
        } else if (c == ' ' || c == '\t') {
          lex_state = LEX_STATE_WHITESPACE;
        } else if (c == '\n' || c == '\r') {
          lex_state = LEX_STATE_WHITESPACE;
        } else if (c == ':') {
          create_token(TOKEN_COLON, file_buffer + i, 1);
          lex_state = LEX_STATE_START;
        } else if (c == ';') {
          create_token(TOKEN_SEMICOLON, file_buffer + i, 1);
          lex_state = LEX_STATE_START;
        } else if (c == '=') {
          create_token(TOKEN_EQUALS, file_buffer + i, 1);
          lex_state = LEX_STATE_START;
        } else if (c == '"') {
          lex_state = LEX_STATE_QUOTATION;
        } else {
          printf("Error! Unrecognized character 0x%02x => '%c'\n", c, c);
          lex_state = LEX_STATE_START;
        }
        i++;
        break;
      case LEX_STATE_SEMICOLON:
        create_token(TOKEN_SEMICOLON, file_buffer + i, 1);
        lex_state = LEX_STATE_START;
        i++;
        break;
      case LEX_STATE_COLON:
        create_token(TOKEN_COLON, file_buffer + i, 1);
        lex_state = LEX_STATE_START;
        i++;
        break;
      case LEX_STATE_EQUALS:
        create_token(TOKEN_EQUALS, file_buffer + i, 1);
        lex_state = LEX_STATE_START;
        i++;
        break;
      case LEX_STATE_NEWLINE:
        line_count++;
        c = file_buffer[++i];
        lex_state = LEX_STATE_TABLE[(unsigned char) c];
        break;
      case LEX_STATE_CARRIAGE_RETURN:
        line_count++;
        if (c == '\n') {
          c = file_buffer[++i];
        }
        lex_state = LEX_STATE_TABLE[(unsigned char) c];
        break;
      case LEX_STATE_WORD:
        while (isalnum(c) || c == '_') {
          word_len++;
          c = file_buffer[++i];
        }

        // TODO: Check if it's keyword, function, or variable
        // TODO: Copy memory over to some kind of string table if it isn't
        char *word_ptr = file_buffer + i - word_len;
        if ((word_len == 7) && strncmp("pattern", word_ptr, 7) == 0) {
          puts("Got 'pattern' keyword");
          create_token(TOKEN_PATTERN, word_ptr, word_len);
        } else if ((word_len == 6) && strncmp("string", word_ptr, 6) == 0) {
          puts("Got 'string' keyword");
          create_token(TOKEN_STRING, word_ptr, word_len);
        } else {
          printf("Read in %.*s as potential var\n", word_len, word_ptr);
          create_token(TOKEN_WORD, word_ptr, word_len);
        }

        word_len = 0;
        lex_state = LEX_STATE_TABLE[(unsigned char) c];
        break;
      case LEX_STATE_QUOTATION:
        {
          int string_buffer_idx = 0;
          char in_backslash = 0;
          char in_string = 1;

          do {
            // Check if we have enough memory for global stretchy buffer
            if (string_buffer_idx >= string_buffer_len) {
              global_string_buffer = double_string_buffer_size(); 
            }

            // Insert next character in buffer
            if (in_backslash) {
              global_string_buffer[string_buffer_idx++] = c;
              word_len++;
              c = file_buffer[++i];
              in_backslash = 0;
              continue;
            }

            if (c == '\\') {
              global_string_buffer[string_buffer_idx++] = c;
              word_len++;
              in_backslash = 1;
              i++;
            } else if (c == '\n' || c == '\r') {
              FAILED("Error! Illegal new line in string");
            } else if (c == '"') {
              i++;
              in_string = 0;
              break;
            } else if (c == 0) {
              FAILED("Error! Illegal end of string");
            } else {
              global_string_buffer[string_buffer_idx++] = c;
              i++;
            }

            c = file_buffer[i];
          } while (i < resource_file_size);

          if (in_string) {
            FAILED("Error! Illegal end of string");
          }

          printf("Read in %.*s as potential quotation\n", string_buffer_idx, global_string_buffer);
          create_token(TOKEN_QUOTATION, global_string_buffer, string_buffer_idx);

          if (i < resource_file_size) {
            lex_state = LEX_STATE_TABLE[(unsigned char) c];
          }
        }
        break;
      default:
        printf("Error! Unrecognized character 0x%02x => '%c'\n", c, c);
        i++;
        break;
    }
  }

  // Wrap up with resource cleanup
  global_resources_cleanup(); 
  return 0;
}

