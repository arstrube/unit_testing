#include "System.h"
#include "uCUnit-v1.0.h"
#include "__list.h"
#include "tests.h"

static void Test_ListIsEmptyAfterInit(void)
{
  __list_t l;
  UCUNIT_TestcaseBegin("List is empty after initialization");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(0, __list_size(&l));
  UCUNIT_TestcaseEnd();
}

static void Test_ListHeaderNextIsNullAfterInit(void)
{
  __list_t l;
  UCUNIT_TestcaseBegin("First elemenent is NULL after initialization");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsNull((void*)l.header.next);
  UCUNIT_TestcaseEnd();
}

static void Test_ListHasCorrectElementSizeAfterInit(void)
{
  #define ELEM_SIZE 357
  __list_t l;
  UCUNIT_TestcaseBegin("List has correct element size after initialization");
  __list_init(&l, ELEM_SIZE);
  UCUNIT_CheckIsEqual(ELEM_SIZE, l.elem_size+1);
  UCUNIT_TestcaseEnd();
}

static void Test_ListSizeIsOneAfterInsertingAnElement(void)
{
  __list_t l;
  int element = 25;
  UCUNIT_TestcaseBegin("List size is 1 after inserting an element");
  __list_insert(&l, &element, 0);
  UCUNIT_CheckIsEqual(1, __list_size(&l));
  UCUNIT_TestcaseEnd();
}

static void Test_ListElementIsInsertedBeforeAnother(void)
{
  __list_t l;
  int before = 7;
  int another = 8;
  UCUNIT_TestcaseBegin("List element is inserted before another");
  __list_insert(&l, &another, 0);
  __list_insert(&l, &before, 0);
  UCUNIT_CheckIsEqual(7, __list_index(&l, &before));
  UCUNIT_TestcaseEnd();
}

static void Test_ListElementIsInsertedAfterAnother(void)
{
  __list_t l;
  int after = 9;
  int another = 8;
  UCUNIT_TestcaseBegin("List element is inserted before another");
  __list_insert(&l, &another, 0);
  __list_insert(&l, &after, 1);
  UCUNIT_CheckIsEqual(9, __list_index(&l, &after));
  UCUNIT_TestcaseEnd();
}

static void Test_VeryDenseTestInvolvingIndex(void)
{
  int i;
  int sample[] = {  2, 11, 47,  2,  2 };
  int result[] = { -1,  0,  1, -1, -1 };
  int elements[] = {11, 47 };
  __list_t l;
  __list_init(&l, sizeof(int));
  __list_insert(&l, elements, 0);
  __list_insert(&l, elements+1, 1);

  UCUNIT_TestcaseBegin("Very dense test involving index");
  for (i = 0; i < 5; i++)
  {
    UCUNIT_CheckIsEqual(result[i], __list_index(&l, sample + i));
  }
  UCUNIT_TestcaseEnd();
}

void Testsuite_List(void)
{
  Test_ListIsEmptyAfterInit();
  Test_ListHeaderNextIsNullAfterInit();
  Test_ListHasCorrectElementSizeAfterInit();
  Test_ListSizeIsOneAfterInsertingAnElement();
  Test_ListElementIsInsertedBeforeAnother();
  Test_ListElementIsInsertedAfterAnother();
  Test_VeryDenseTestInvolvingIndex();

  UCUNIT_WriteSummary();
}
