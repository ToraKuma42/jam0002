#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

/**
 * Basic lexer and tokenizer structs/functions
 */

enum token_type_t {
   TOKEN_WORD,
   TOKEN_NUMBER,
   TOKEN_QUOTATION,
   TOKEN_LPAREN,
   TOKEN_RPAREN,
   TOKEN_COLON,
   TOKEN_SEMICOLON,
   TOKEN_EQUALS,
   TOKEN_PATTERN,
   TOKEN_STRING,
};

enum lex_state_t {
  LEX_STATE_START,
  LEX_STATE_WHITESPACE,
  LEX_STATE_WORD,
  LEX_STATE_NUMBER,
  LEX_STATE_QUOTATION,
  LEX_STATE_LPAREN,
  LEX_STATE_RPAREN,
  LEX_STATE_SEMICOLON,
  LEX_STATE_COLON,
  LEX_STATE_EQUALS,
  LEX_STATE_NEWLINE,
  LEX_STATE_CARRIAGE_RETURN,
  LEX_END,
};

struct token_t {
  enum token_type_t type;
  int len;
  char data[1];
};

static const unsigned char LEX_STATE_TABLE[256] = {
  // Numbers
  ['0'] = LEX_STATE_NUMBER,
  ['1'] = LEX_STATE_NUMBER,
  ['2'] = LEX_STATE_NUMBER,
  ['3'] = LEX_STATE_NUMBER,
  ['4'] = LEX_STATE_NUMBER,
  ['5'] = LEX_STATE_NUMBER,
  ['6'] = LEX_STATE_NUMBER,
  ['7'] = LEX_STATE_NUMBER,
  ['8'] = LEX_STATE_NUMBER,
  ['9'] = LEX_STATE_NUMBER,

  // Lower case letters and underscore
  ['a'] = LEX_STATE_WORD,
  ['b'] = LEX_STATE_WORD,
  ['c'] = LEX_STATE_WORD,
  ['d'] = LEX_STATE_WORD,
  ['e'] = LEX_STATE_WORD,
  ['f'] = LEX_STATE_WORD,
  ['g'] = LEX_STATE_WORD,
  ['h'] = LEX_STATE_WORD,
  ['i'] = LEX_STATE_WORD,
  ['j'] = LEX_STATE_WORD,
  ['k'] = LEX_STATE_WORD,
  ['l'] = LEX_STATE_WORD,
  ['m'] = LEX_STATE_WORD,
  ['n'] = LEX_STATE_WORD,
  ['o'] = LEX_STATE_WORD,
  ['p'] = LEX_STATE_WORD,
  ['q'] = LEX_STATE_WORD,
  ['r'] = LEX_STATE_WORD,
  ['s'] = LEX_STATE_WORD,
  ['t'] = LEX_STATE_WORD,
  ['u'] = LEX_STATE_WORD,
  ['v'] = LEX_STATE_WORD,
  ['w'] = LEX_STATE_WORD,
  ['x'] = LEX_STATE_WORD,
  ['y'] = LEX_STATE_WORD,
  ['z'] = LEX_STATE_WORD,
  ['_'] = LEX_STATE_WORD,

  // Upper case letters
  ['A'] = LEX_STATE_WORD,
  ['B'] = LEX_STATE_WORD,
  ['C'] = LEX_STATE_WORD,
  ['D'] = LEX_STATE_WORD,
  ['E'] = LEX_STATE_WORD,
  ['F'] = LEX_STATE_WORD,
  ['G'] = LEX_STATE_WORD,
  ['H'] = LEX_STATE_WORD,
  ['I'] = LEX_STATE_WORD,
  ['J'] = LEX_STATE_WORD,
  ['K'] = LEX_STATE_WORD,
  ['L'] = LEX_STATE_WORD,
  ['M'] = LEX_STATE_WORD,
  ['N'] = LEX_STATE_WORD,
  ['O'] = LEX_STATE_WORD,
  ['P'] = LEX_STATE_WORD,
  ['Q'] = LEX_STATE_WORD,
  ['R'] = LEX_STATE_WORD,
  ['S'] = LEX_STATE_WORD,
  ['T'] = LEX_STATE_WORD,
  ['U'] = LEX_STATE_WORD,
  ['V'] = LEX_STATE_WORD,
  ['W'] = LEX_STATE_WORD,
  ['X'] = LEX_STATE_WORD,
  ['Y'] = LEX_STATE_WORD,
  ['Z'] = LEX_STATE_WORD,

  // Special characters
  [':'] = LEX_STATE_COLON,
  ['='] = LEX_STATE_EQUALS,

  // Whitespace/New line
  ['\n'] = LEX_STATE_NEWLINE,
  ['\r'] = LEX_STATE_CARRIAGE_RETURN,
  [' '] = LEX_STATE_WHITESPACE,
  ['\t'] = LEX_STATE_WHITESPACE,
};

void create_token(enum token_type_t type, char *buffer, int len);

#endif /* __TOKENIZER_H__ */

