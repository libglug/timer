#include "frac.h"
#include <CUnit/Assert.h>

#include <frac_t.h>

void assert_frac_equal(const struct frac *f1, const struct frac *f2)
{
    CU_ASSERT_EQUAL(f1->numer, f2->numer);
    CU_ASSERT_EQUAL(f1->denom, f2->denom)
}
