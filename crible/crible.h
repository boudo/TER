#ifndef CRIBLE_H
#define CRIBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "../liste/liste.h"
#include "../liste/listegmp.h"

listegmp Eratosthene(mpz_t n);

#endif
