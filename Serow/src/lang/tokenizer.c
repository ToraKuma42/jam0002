#include <string.h>

#include "../lib/resources.h"
#include "tokenizer.h"

void
create_token(enum token_type_t type, char *buffer, int len)
{
  size_t next_idx = token_buffer_idx + sizeof(struct token_t) + 1;
  if (next_idx > token_buffer_len) {
    global_token_buffer = double_token_buffer_size();
  }

  struct token_t *token_head = (struct token_t *) (global_token_buffer + token_buffer_idx);

  token_head->type = type;
  token_head->len = len;

  memcpy(token_head->data, buffer, len);
  token_head->data[len + 1] = '\0';
  token_buffer_idx = next_idx;
}

