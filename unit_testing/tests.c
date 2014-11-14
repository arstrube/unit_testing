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

    IT("should not return NULL")
    IT_END

    IT("should create an empty list")
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_insert(list*, element*, index)")

    IT("should increment list size when inserting an element")
    IT_END

    IT("should be able to insert an element before another")
    IT_END

    IT("should be able to insert an element after another")
    IT_END

    IT("should return an error when passed an invalid positive index")
    IT_END

    IT("should return an error when passed a negative index")
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_index(list*, element*)")

    IT("should be able to find an element")
    IT_END

    IT("should should return an error for a non-existent element")
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_get(list*, element*, index)")

    IT("should be able to get the first element")
    IT_END

    IT("should be able to get the second element")
    IT_END

    IT("should return an error when passed an invalid positive index");
    IT_END;

    IT("should return an error when passed a negative index")
    IT_END

  DESCRIBE_END

  DESCRIBE("__list_destroy(list**)")

    IT("should set the list pointer to NULL after destruction")
    IT_END;

  DESCRIBE_END

  DESCRIBE("__list_rem(list*, element*, index")

    IT("should be able to remove the second element")
    IT_END

    IT("should leave the list empty after removing the last element")
    IT_END

    IT("should return an error when passed a negative index")
    IT_END

    IT("should return an error when passed an invalid positive index")
    IT_END

  DESCRIBE_END
}

void Testsuite_List(void)
{
  UCSPEC_UseStaticsAtLeastOnce();
  Specifications();
  UCSPEC_WriteSummary();
}
