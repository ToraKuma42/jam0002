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

/* Function declarations */
int def_destructor(void *);
int file_destructor(void *);

void *global_resource_alloc_default(void *, const char *);
void *global_resource_alloc(void *, const char *, int (*)(void *));
void *global_resource_alloc_default_named(void *, const char *, const char *);
void *global_resource_alloc_named(void *, const char *, const char *, int (*)(void *));
void global_resources_cleanup();

static int16_t global_resource_count = 0;

static struct global_resource_t {
  void *item;
  int (*destructor)(void *);
} global_resources[GLOBAL_RESOURCE_LIMIT];


#endif /* __RESOURCES_H__ */
