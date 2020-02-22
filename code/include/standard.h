/*!
 * \file		standard.h
 *
 * \brief		Header file that contains standard C library includes.
 */

#ifndef STANDARD_H
#define STANDARD_H

// C library standard headers
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

// Personal library headers
#include <dlist.h>
#include <slist.h>
#include <mergesort.h>

//----------------------------------------------------------------------------//
//- Macro definitions                                                        -//
//----------------------------------------------------------------------------//

#define ARRAY_SIZE(a)               (sizeof(a) / sizeof(a[0]))
#define UNUSED_PARAMETER(a)         ((void)(a))

#define foreach(item, array)                                \
    for (int keep   = 1,                                    \
            count   = 0,                                    \
            size    = ARRAY_SIZE(array);                    \
            keep && count != size;                          \
            keep = !keep, count++)                          \
      for (item = (array) + count; keep; keep = !keep)

#endif // STANDARD_H