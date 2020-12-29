#include "clocktime.h"
#include <CUnit/Assert.h>

void assert_clocktime_equal(const clocktime_t *ct1, const clocktime_t *ct2)
{
    CU_ASSERT_EQUAL(ct1->sec, ct2->sec);
    CU_ASSERT_EQUAL(ct1->nsec, ct2->nsec)
}
