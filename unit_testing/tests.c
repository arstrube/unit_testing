#include "System.h"
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

    IT("should do all kinds of marvelleous things") IT_END
    IT("should self-destruct after 10 minutes") IT_END

    __list_destroy(&l);

  DESCRIBE_END

  DESCRIBE("__list_insert(list*, element*, index)")

    IT("should increment list size when inserting an element");
      __list_t* l = __list_create(sizeof(int));
      int element = 25;
      __list_insert(l, &element, 0);
      SHOULD_EQ(1, __list_size(l)+1); // provoke failure
      __list_destroy(&l);
    IT_END;

    IT("should be able to insert an element before another");
      int before = 7;
      int another = 8;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &another, 0);
      __list_insert(l, &before, 0);
      SHOULD_EQ(0, __list_index(l, &before));
      __list_destroy(&l);
    IT_END;

    IT("should be able to insert an element after another");
      int after = 9;
      int another = 8;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &another, 0);
      __list_insert(l, &after, 1);
      SHOULD_EQ(1, __list_index(l, &after));
      __list_destroy(&l);
    IT_END;

    IT("should return an error when passed an invalid index 1");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_insert(l, &element, 1));
      __list_destroy(&l);
    IT_END;

    IT("should return an error when passed an invalid index 2");
      int first = 3;
      int second = 0;
      int test = 15;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &first, 0);
      __list_insert(l, &second, 1);
      SHOULD_EQ(-1, __list_insert(l, &test, 4));
      __list_destroy(&l);
    IT_END;

    IT("should return an error when passed a negative index");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_insert(l, &element, -1));
      __list_destroy(&l);
    IT_END;

  DESCRIBE_END

  DESCRIBE("List")

    IT("is NULL after destruction");
      __list_t* l = __list_create(sizeof(int));
      __list_destroy(&l);
      SHOULD_BE_NULL(l);
    IT_END;

    IT("is empty after removing the last element");
      int input_elem = 5;
      int output_elem = -1;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &input_elem, 0);
      __list_rem(l, &output_elem, 0);
      SHOULD_EQ(5, input_elem);
      SHOULD_EQ(5, output_elem);
      SHOULD_EQ(0, __list_size(l));
      __list_destroy(&l);
    IT_END;

    IT("can get the first element");
      int element = 3;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, &element, 0);
      __list_get(l, &element, 0);
      SHOULD_EQ(3, element);
      __list_destroy(&l);
    IT_END;

    IT("can get the second element");
      int elements[] = {4, 3};
      int result;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, elements, 0);
      __list_insert(l, elements + 1, 1);
      __list_get(l, &result, 1);
      SHOULD_EQ(3, result);
      __list_destroy(&l);
    IT_END;

    IT("returns an error for trying to get at -1");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_get(l, &element, -1));
      __list_destroy(&l);
    IT_END;

    IT("returns an error for trying to get beyond end");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_get(l, &element, 1));
      __list_destroy(&l);
    IT_END;

    IT("can remove the second element");
      int elements[] = {4, 3};
      int result;
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, elements, 0);
      __list_insert(l, elements + 1, 1);
      __list_rem(l, &result, 1);
      SHOULD_EQ(3, result);
      SHOULD_EQ(1, __list_size(l));
      __list_destroy(&l);
    IT_END;

    IT("returns an error for trying to remove at -1");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_rem(l, &element, -1));
      __list_destroy(&l);
    IT_END;

    IT("returns an error for trying to remove beyond end");
      int element = 5;
      __list_t* l = __list_create(sizeof(int));
      SHOULD_EQ(-1, __list_rem(l, &element, 1));
      __list_destroy(&l);
    IT_END;

    IT("can find an element");
      int elements[] = {4, 5};
      __list_t* l = __list_create(sizeof(int));
      __list_insert(l, elements, 0);
      __list_insert(l, elements+1, 1);
      SHOULD_EQ(1, __list_index(l, &elements[1]));
      __list_destroy(&l);
    IT_END;

  DESCRIBE_END
}

void Testsuite_List(void)
{
  UCSPEC_UseStaticsAtLeastOnce();
  Specifications();
  UCSPEC_WriteSummary();
}
