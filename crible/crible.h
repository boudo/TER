#ifndef CRIBLE_H
#define CRIBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "../liste/liste.h"
#include "../liste/listegmp.h"

liste crible_era(int n);
listegmp crible_era_gmp(mpz_t n);

#endif
