#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void
test_sum(void)
{
  CU_ASSERT_EQUAL(40 + 2, 42);
}

int
main()
{
  CU_pSuite pSuite1 = NULL;

  // Initialize CUnit test registry
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  // Add suite1 to registry
  pSuite1 = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);
  if (NULL == pSuite1) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // add test1 to suite1
  if ((NULL == CU_add_test(pSuite1, "\n\n=== Testing Sum function ===\n\n", test_sum)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run test suite
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return CU_get_error();
}
