#include "System.h"

#ifndef UCUNIT_MODE_SILENT
#define UCUNIT_MODE_SILENT
#endif

#include "uCUnit-v1.0.h"
#include "uCSpec-v1.0.h"
#include "__list.h"
#include "tests.h"

static void Specifications(void)
{
  DESCRIBE("__list_create(sizeof(int))")

      __list_t* l = __list_create(sizeof(int));

    IT("should not return NULL");
      SHOULD_NOT_BE_NULL(l);
    IT_END

    IT("should create an empty list");
      SHOULD_EQ(0, __list_size(l));
    IT_END

    __list_destroy(&l);

  DESCRIBE_END

  DESCRIBE("__list_insert(list*, element*, index)")

    IT("should increment list size when inserting an element")
      __list_t* l = __list_create(sizeof(int));
      int element = 25;
      __list_insert(l, &element, 0);
      SHOULD_EQ(1, __list_size(l)+1); // provoke failure
      __list_destroy(&l);
    IT_END

    IT("should be able to insert an element before another")
      int before = 7;
      int another = 8;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &another, 0);
      __list_insert(l, &before, 0);
      SHOULD_EQ(0, __list_index(l, &before));
      __list_destroy(&l);
    IT_END

    IT("should return an error when passed an invalid positive index")
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_insert(l, &element, 1));
      __list_destroy(&l);
    IT_END

    IT("should return an error when passed a negative index")
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_insert(l, &element, -1));
      __list_destroy(&l);
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_index(list*, element*)")

    IT("should be able to find an element")
      int element = 6;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &element, 0);
      SHOULD_EQ(0, __list_index(l, &element));
      __list_destroy(&l);
    IT_END

    IT("should should return an error for a non-existent element")
      int elements[] = {4, 5};
      int non_existent = 7;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, elements, 0);
      __list_insert(l, elements+1, 1);
      SHOULD_EQ(-1, __list_index(l, &non_existent));
      __list_destroy(&l);
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_get(list*, element*, index)")

    IT("should be able to get an element")
      int elements[] = {4, 3};
      int result = 7;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, elements, 0);
      __list_insert(l, elements + 1, 1);
      __list_get(l, &result, 1);
      SHOULD_EQ(3, result);
      __list_destroy(&l);
    IT_END

    IT("should return an error when passed an invalid positive index");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_get(l, &element, 1));
      __list_destroy(&l);
    IT_END;

    IT("should return an error when passed a negative index")
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_get(l, &element, -1));
      __list_destroy(&l);
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_rem(list*, element*, index)")

    IT("should be able to remove an element")
      int elements[] = {4, 3};
      int result;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, elements, 0);
      __list_insert(l, elements + 1, 1);
      __list_rem(l, &result, 1);
      SHOULD_EQ(3, result);
      SHOULD_EQ(1, __list_size(l));
      __list_destroy(&l);
    IT_END

    IT("should return an error when passed a negative index")
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_rem(l, &element, -1));
      __list_destroy(&l);
    IT_END

    IT("should return an error when passed an invalid positive index")
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_rem(l, &element, 1));
      __list_destroy(&l);
    IT_END

  DESCRIBE_END
}

void Testsuite_List(void)
{
  UCSPEC_UseStaticsAtLeastOnce();
  Specifications();
  UCSPEC_WriteSummary();
}
