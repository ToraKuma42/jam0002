#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Global resource functions */
#define GLOBAL_RESOURCE_LIMIT 30
#define VALIDATE_GLOBAL_RESOURCE_LIMIT() (global_resource_count >= GLOBAL_RESOURCE_LIMIT)

#define DECLARE_RETURNABLE_RESOURCE_DESTRUCTOR(res_type, lambda) \
    int \
    res_type##_destructor(void *resource_ptr) \
    { \
      return lambda(resource_ptr); \
    }

#define DECLARE_RESOURCE_DESTRUCTOR(res_type, lambda) \
    int \
    res_type##_destructor(void *resource_ptr) \
    { \
      lambda(resource_ptr); \
      return 0; \
    }

#define FAILED(...) \
    do { \
        fprintf(stderr, "%s", __VA_ARGS__); \
        fprintf(stderr, "\n"); \
        global_resources_cleanup(); \
        exit(1); \
    } \
    while (0)


#define FAILED_WITH_NAME(formatted_str, resource_name) \
    do { \
        fprintf(stderr, formatted_str, resource_name); \
        fprintf(stderr, "\n"); \
        global_resources_cleanup(); \
        exit(1); \
    } \
    while (0)

/* Resource structs */
struct global_resource_t {
  void *item;
  int (*destructor)(void *);
}; 

/* Function declarations */
int def_destructor(void *);
int file_destructor(void *);

void *global_resource_alloc_default(void *, const char *);
void *global_resource_alloc(void *, const char *, int (*)(void *));
void *global_resource_alloc_default_named(void *, const char *, const char *);
void *global_resource_alloc_named(void *, const char *, const char *, int (*)(void *));

void *global_resource_realloc(void *, size_t, const char *);

void global_resources_cleanup();

char *double_string_buffer_size();
char *double_token_buffer_size();

/* Static compiler global resource location */
#define GLOBAL_STRING_BUFFER_LEN 512

#define AVERAGE_TOKEN_LEN 25
#define TOKEN_NUMBER 50
#define GLOBAL_TOKEN_BUFFER_LEN ((AVERAGE_TOKEN_LEN) * (TOKEN_NUMBER))

extern int16_t global_resource_count;
extern int string_buffer_len;
extern size_t token_buffer_len;
extern size_t token_buffer_idx;

static struct global_resource_t global_resources[GLOBAL_RESOURCE_LIMIT];

extern char *global_string_buffer;
extern char *global_token_buffer;

#endif /* __RESOURCES_H__ */

