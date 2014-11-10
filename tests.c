#include "System.h"
#include "uCUnit-v1.0.h"
#include "__list.h"
#include "tests.h"

static void Test__list_init(void)
{
  UCUNIT_TestcaseBegin("Test__list_init");
  UCUNIT_CheckIsEqual(0, 1);
  UCUNIT_TestcaseEnd();
}

static void Test__list_index(void)
{
  int i;
  int sample[] = {  2, 11, 47,  2,  2 };
  int result[] = { -1,  0,  1, -1, -1 };
  int elements[] = {11, 47 };
  __list_t l;
  __list_init(&l, sizeof(int));
  __list_insert(&l, elements, 0);
  __list_insert(&l, elements+1, 1);

  UCUNIT_TestcaseBegin("Test__list_index");
  UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
  for (i = 0; i < 5; i++)
  {
    UCUNIT_CheckIsEqual(result[i], __list_index(&l, sample + i));
  }
  UCUNIT_ChecklistEnd();
  UCUNIT_TestcaseEnd();
}

void Testsuite__list_h(void)
{
    Test__list_init();
    Test__list_index();

    UCUNIT_WriteSummary();
}
