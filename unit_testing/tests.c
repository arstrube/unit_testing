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
  __list_init(&l, sizeof(int));
  __list_insert(&l, &element, 0);
  UCUNIT_CheckIsEqual(1, __list_size(&l));
  __list_cleanup(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_CleanupOfEmptyListDoesNothing(void)
{
  __list_t l;
  int element = 25;
  UCUNIT_TestcaseBegin("Cleanup of empty list does nothing");
  __list_init(&l, sizeof(int));
  __list_cleanup(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListIsEmptyAfterCleanup(void)
{
  __list_t l;
  int element = 3;
  UCUNIT_TestcaseBegin("List is empty after cleanup");
  __list_init(&l, sizeof(int));
  __list_insert(&l, &element, 0);
  __list_cleanup(&l);
  UCUNIT_CheckIsEqual(0, __list_size(&l));
  UCUNIT_CheckIsNull(l.header.next);
  UCUNIT_TestcaseEnd();
}

static void Test_ListElementIsInsertedBeforeAnother(void)
{
  __list_t l;
  int before = 7;
  int another = 8;
  UCUNIT_TestcaseBegin("List element is inserted before another");
  __list_init(&l, sizeof(int));
  __list_insert(&l, &another, 0);
  __list_insert(&l, &before, 0);
  UCUNIT_CheckIsEqual(0, __list_index(&l, &before));
  __list_cleanup(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListElementIsInsertedAfterAnother(void)
{
  __list_t l;
  int after = 9;
  int another = 8;
  UCUNIT_TestcaseBegin("List element is inserted after another");
  __list_init(&l, sizeof(int));
  __list_insert(&l, &another, 0);
  __list_insert(&l, &after, 1);
  UCUNIT_CheckIsEqual(1, __list_index(&l, &after));
  __list_cleanup(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListElementInsertedBeyondEndReturnsError(void)
{
  __list_t l;
  int first = 3;
  int second = 0;
  int test = 15;
  UCUNIT_TestcaseBegin("List element inserted beyond the end of the list results in error");
  __list_init(&l, sizeof(int));
  __list_insert(&l, &first, 0);
  __list_insert(&l, &second, 1);
  UCUNIT_CheckIsEqual(-1, __list_insert(&l, &test, 4));
  __list_cleanup(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListIsEmptyAfterRemovingTheLastElement(void)
{
  __list_t l;
  int input_elem = 5;
  int output_elem = -1;
  UCUNIT_TestcaseBegin("List is empty after removing the last element");
  __list_init(&l, sizeof(int));
  __list_insert(&l, &input_elem, 0);
  __list_rem(&l, &output_elem, 0);
  UCUNIT_CheckIsEqual(5, input_elem);
  UCUNIT_CheckIsEqual(5, output_elem);
  UCUNIT_CheckIsNull(l.header.next);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForInsertingAtMinusOne(void)
{
  __list_t l;
  __list_init(&l, sizeof(int));
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for inserting at index -1");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_insert(&l, &element, -1));
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForInsertingBeyondEnd(void)
{
  __list_t l;
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for inserting beyond end");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_insert(&l, &element, 1));
  UCUNIT_TestcaseEnd();
}

static void Test_ListCanGetFirstElement()
{
  __list_t l;
  int element = 3;
  UCUNIT_TestcaseBegin("List can get the first element");
  __list_init(&l, sizeof(int));
  __list_insert(&l, &element, 0);
  __list_get(&l, &element, 0);
  UCUNIT_CheckIsEqual(3, element);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToGetAtIndexMinusOne()
{
  __list_t l;
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to get at -1");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_get(&l, &element, -1));
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToGetBeyondEnd()
{
  __list_t l;
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to get beyond end");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_get(&l, &element, 1));
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToRemoveAtMinusOne()
{
  __list_t l;
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to remove at -1");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_rem(&l, &element, 1));
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToRemoveBeyondEnd()
{
  __list_t l;
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to remove beyond end");
  __list_init(&l, sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_rem(&l, &element, 1));
  UCUNIT_TestcaseEnd();
}

static void Test_ThisTestCoversALotOfStuff(void)
{
  int i;
  int sample[] = {  2, 11, 47,  2,  2 };
  int result[] = { -1,  0,  1, -1, -1 };
  int elements[] = {11, 47 };
  __list_t l;
  __list_init(&l, sizeof(int));
  __list_insert(&l, elements, 0);
  __list_insert(&l, elements+1, 1);

  UCUNIT_TestcaseBegin("This test covers a lot of stuff");
  for (i = 0; i < 5; i++)
  {
    UCUNIT_CheckIsEqual(result[i], __list_index(&l, sample + i));
  }
  __list_cleanup(&l);
  UCUNIT_TestcaseEnd();
}

void Testsuite_List(void)
{
  Test_ListIsEmptyAfterInit();
  Test_ListHeaderNextIsNullAfterInit();
  Test_ListHasCorrectElementSizeAfterInit();
  Test_CleanupOfEmptyListDoesNothing();
  Test_ListSizeIsOneAfterInsertingAnElement();
  Test_ListElementIsInsertedBeforeAnother();
  Test_ListElementIsInsertedAfterAnother();
  Test_ListElementInsertedBeyondEndReturnsError();
  Test_ListIsEmptyAfterCleanup();
  Test_ListIsEmptyAfterRemovingTheLastElement();
  Test_ThisTestCoversALotOfStuff();
  Test_ListReturnsErrorForInsertingAtMinusOne();
  Test_ListReturnsErrorForInsertingBeyondEnd();
  Test_ListCanGetFirstElement();
  Test_ListReturnsErrorForTryingToGetAtIndexMinusOne();
  Test_ListReturnsErrorForTryingToGetBeyondEnd();
  Test_ListReturnsErrorForTryingToRemoveAtMinusOne();
  Test_ListReturnsErrorForTryingToRemoveBeyondEnd();

  UCUNIT_WriteSummary();
}
