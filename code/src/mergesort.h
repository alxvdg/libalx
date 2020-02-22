/*!
 * \file		mergesort.h
 *
 * \brief		This file handles the merge sort of a list.
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include <standard.h>

typedef bool (*MergesortCmpFn)(void *pArgA, void *pArgB);

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

void mergesort(Dlist *pList, MergesortCmpFn compare);

#endif // MERGESORT_H