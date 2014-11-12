#include "System.h"
#include "uCUnit-v1.0.h"
#include "__list.h"
#include "tests.h"

static void Test_ListIsNotNullAfterCreation(void)
{
  UCUNIT_TestcaseBegin("List is not NULL after creation");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsNotNull(l);
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListHeaderNextIsNullAfterCreation(void)
{
  // Tests can no longer check internal data
}

static void Test_ListHasCorrectElementSizeAfterInit(void)
{
  // Tests can no longer check internal data
}

static void Test_ListSizeIsOneAfterInsertingAnElement(void)
{
  UCUNIT_TestcaseBegin("List size is 1 after inserting an element");
  __list_t* l = __list_create(sizeof(int));
  int element = 25;
  __list_insert(l, &element, 0);
  UCUNIT_CheckIsEqual(1, __list_size(l)+1); // provoke failure
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListIsNullAfterDestruction(void)
{
  UCUNIT_TestcaseBegin("List is NULL after destruction");
  __list_t* l = __list_create(sizeof(int));
  __list_destroy(&l);
  UCUNIT_CheckIsNull(l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListIsEmptyAfterCleanup(void)
{
  //This test no longer makes sense
}

static void Test_ListElementIsInsertedBeforeAnother(void)
{
  int before = 7;
  int another = 8;
  UCUNIT_TestcaseBegin("List element is inserted before another");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, &another, 0);
  __list_insert(l, &before, 0);
  UCUNIT_CheckIsEqual(0, __list_index(l, &before));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListElementIsInsertedAfterAnother(void)
{
  int after = 9;
  int another = 8;
  UCUNIT_TestcaseBegin("List element is inserted after another");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, &another, 0);
  __list_insert(l, &after, 1);
  UCUNIT_CheckIsEqual(1, __list_index(l, &after));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}
static void Test_ListElementInsertedBeyondEndReturnsError(void)
{
  int first = 3;
  int second = 0;
  int test = 15;
  UCUNIT_TestcaseBegin("List element inserted beyond the end of the list results in error");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, &first, 0);
  __list_insert(l, &second, 1);
  UCUNIT_CheckIsEqual(-1, __list_insert(l, &test, 4));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListIsEmptyAfterRemovingTheLastElement(void)
{
  int input_elem = 5;
  int output_elem = -1;
  UCUNIT_TestcaseBegin("List is empty after removing the last element");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, &input_elem, 0);
  __list_rem(l, &output_elem, 0);
  UCUNIT_CheckIsEqual(5, input_elem);
  UCUNIT_CheckIsEqual(5, output_elem);
  UCUNIT_CheckIsEqual(0, __list_size(l));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForInsertingAtMinusOne(void)
{
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for inserting at index -1");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_insert(l, &element, -1));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForInsertingBeyondEnd(void)
{
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for inserting beyond end");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_insert(l, &element, 1));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListCanGetFirstElement()
{
  int element = 3;
  UCUNIT_TestcaseBegin("List can get the first element");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, &element, 0);
  __list_get(l, &element, 0);
  UCUNIT_CheckIsEqual(3, element);
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListCanGetSecondElement()
{
  int elements[] = {4, 3};
  int result;
  UCUNIT_TestcaseBegin("List can get the second element");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, elements, 0);
  __list_insert(l, elements + 1, 1);
  __list_get(l, &result, 1);
  UCUNIT_CheckIsEqual(3, result);
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToGetAtIndexMinusOne()
{
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to get at -1");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_get(l, &element, -1));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToGetBeyondEnd()
{
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to get beyond end");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_get(l, &element, 1));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListCanRemoveSecondElement()
{
  int elements[] = {4, 3};
  int result;
  UCUNIT_TestcaseBegin("List can remove the second element");
  __list_t* l = __list_create(sizeof(int));
  __list_insert(l, elements, 0);
  __list_insert(l, elements + 1, 1);
  __list_rem(l, &result, 1);
  UCUNIT_CheckIsEqual(3, result);
  UCUNIT_CheckIsEqual(1, __list_size(l));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToRemoveAtMinusOne()
{
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to remove at -1");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_rem(l, &element, -1));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

static void Test_ListReturnsErrorForTryingToRemoveBeyondEnd()
{
  int element = 5;
  UCUNIT_TestcaseBegin("List returns an error for trying to remove beyond end");
  __list_t* l = __list_create(sizeof(int));
  UCUNIT_CheckIsEqual(-1, __list_rem(l, &element, 1));
  __list_destroy(&l);
  UCUNIT_TestcaseEnd();
}

void Testsuite_List(void)
{
  Test_ListIsNotNullAfterCreation();
  Test_ListSizeIsOneAfterInsertingAnElement();
  Test_ListIsNullAfterDestruction();
  Test_ListElementIsInsertedBeforeAnother();
  Test_ListElementIsInsertedAfterAnother();
  Test_ListElementInsertedBeyondEndReturnsError();
  Test_ListIsEmptyAfterRemovingTheLastElement();
  Test_ListReturnsErrorForInsertingAtMinusOne();
  Test_ListReturnsErrorForInsertingBeyondEnd();
  Test_ListCanGetFirstElement();
  Test_ListCanGetSecondElement();
  Test_ListReturnsErrorForTryingToGetAtIndexMinusOne();
  Test_ListReturnsErrorForTryingToGetBeyondEnd();
  Test_ListCanRemoveSecondElement();
  Test_ListReturnsErrorForTryingToRemoveAtMinusOne();
  Test_ListReturnsErrorForTryingToRemoveBeyondEnd();

  UCUNIT_WriteSummary();
}
