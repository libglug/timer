#include "asserts.h"
#include <CUnit/Assert.h>

void assert_time_equal(struct glug_time *t1, struct glug_time *t2)
{
    CU_ASSERT_EQUAL(t1->sec, t2->sec);
    CU_ASSERT_EQUAL(t1->nsec, t2->nsec)
}
