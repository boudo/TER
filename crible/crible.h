#ifndef CRIBLE_H
#define CRIBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "../liste/listegmp.h"


listegmp crible_era_gmp(mpz_t n);
int Test_Era(mpz_t n);

#endif
