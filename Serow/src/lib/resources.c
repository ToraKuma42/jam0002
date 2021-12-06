#include "resources.h"

static int16_t global_resource_count;

/* Global resource function declarations */
DECLARE_RESOURCE_DESTRUCTOR(def, free)
DECLARE_RETURNABLE_RESOURCE_DESTRUCTOR(file, fclose)

void *
global_resource_alloc_default(void *resource_item, const char *error_msg)
{
  return global_resource_alloc(resource_item, error_msg, &def_destructor);
}

void *
global_resource_alloc(void *resource_item, const char *error_msg, int (*destructor)(void *))
{
  if (VALIDATE_GLOBAL_RESOURCE_LIMIT() || !resource_item) {
    FAILED(error_msg);
  }

  global_resources[global_resource_count].item = resource_item;
  global_resources[global_resource_count].destructor = destructor;
  global_resource_count++;
  return resource_item;
}

void *
global_resource_alloc_default_named(void *resource_item, const char *error_msg, const char *resource_name)
{
  return global_resource_alloc_named(resource_item, error_msg, resource_name, &def_destructor);
}

void *
global_resource_alloc_named(void *resource_item, const char *error_msg, const char *resource_name, int (*destructor)(void *))
{
  if (VALIDATE_GLOBAL_RESOURCE_LIMIT() || !resource_item) {
    FAILED_WITH_NAME(error_msg, resource_name);
  }

  global_resources[global_resource_count].item = resource_item;
  global_resources[global_resource_count].destructor = destructor;
  global_resource_count++;
  return resource_item;

}

void *
global_resource_realloc(void *resource_item, size_t new_res_size, const char *error_msg)
{
  // Get old record from original pointer location
  char success = 0;
  int i = global_resource_count;
  struct global_resource_t local_data;

  // Backward linear probe to find old resource location
  while (--i >= 0 && !success) {
    local_data = global_resources[global_resource_count];
    if (local_data.item == resource_item) {
      global_resource_count--;
      success = 1;
    }
  }

  if (!success) {
    FAILED(error_msg);
  }

  for (; i < global_resource_count; i++) {
    global_resources[i] = global_resources[i + 1];
  }

  // Realloc according to given size
  return global_resource_alloc(realloc(resource_item, new_res_size), error_msg, local_data.destructor);
}

/**
 * Globally effectful function to release all global resources
 * that were allocated in the program's lifetime.
 */
void
global_resources_cleanup()
{
  while (--global_resource_count >= 0) {
    void *resource_item = global_resources[global_resource_count].item;
    global_resources[global_resource_count].destructor(resource_item);
  }
}

