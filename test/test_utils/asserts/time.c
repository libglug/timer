#include "time.h"
#include <CUnit/Assert.h>

#include <glug/timer/time_t.h>

void assert_time_equal(const struct glug_time *t1, const struct glug_time *t2)
{
    CU_ASSERT_EQUAL(t1->sec, t2->sec);
    CU_ASSERT_EQUAL(t1->nsec, t2->nsec)
}
