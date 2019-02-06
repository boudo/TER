#ifndef MILLER_H
#define MILLER_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../liste/liste.h"

void Miller_Rabin(mpz_t n, mpz_t rep);

#endif
