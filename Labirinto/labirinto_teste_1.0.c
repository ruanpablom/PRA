#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
//#include "CUnit/Automated.h"
//#include "CUnit/Console.h"

#include "max.h"

#include <stdio.h>  // for printf

/* Test Suite setup and cleanup functions: */

arquivo="labirinto_test_1";
int totLinhas=10;
int totColunas=36;
int linEntrada=2;
int colEntrada=0;
int linSaida=5;
int colSaida=35;
int linQueijo=3;
int colQUeijo=34;


int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************* Test case functions ****************/

int test_carga() {
    CU_ASSERT_EQUAL(carga(),totLinhas);
}

int mock_test(void)
{
	CU_ASSERT_EQUAL(0,-1);
}

/************* Test Runner Code goes here **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "max_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
	/*MOCK TEST*/
   if ( (NULL == CU_add_test(pSuite, "Labirinto carregou", test_carga)) ||
        (NULL == CU_add_test(pSuite, "É início", mock_test)) ||
        (NULL == CU_add_test(pSuite, "verifica saída", mock_test))||
	     (NULL == CU_add_test(pSuite, "Anda frente", mock_test))||
	     (NULL == CU_add_test(pSuite, "Anda trás", mock_test))||
	     (NULL == CU_add_test(pSuite, "Anda esquerda", mock_test))||
	     (NULL == CU_add_test(pSuite, "Anda direita", mock_test))||
	     (NULL == CU_add_test(pSuite, "Comeu queijo", mock_test))||
	     (NULL == CU_add_test(pSuite, "Parede barra", mock_test))||
	     (NULL == CU_add_test(pSuite, "Para na saída", mock_test))||
	     (NULL == CU_add_test(pSuite, "caminho impresso", mock_test))
	/*MOCK TEST*/
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
