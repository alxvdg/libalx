// Library headers
#include <standard.h>

// Local headers
#include "dlist.h"
#include "mergesort.h"

//----------------------------------------------------------------------------//
//- Private functions                                                        -//
//----------------------------------------------------------------------------//
#if 0
static void merge(Dlist *pMerge, Dlist *pListOne, Dlist *pListTwo, MergesortCmpFn compare)
{
    bool             result;

    result = compare(pListOne->pHead->pData, pListTwo->pHead->pData);

    if (result)
    {
        dlist_join(pMerge, pListOne, 1);
    }
    else
    {
        dlist_join(pMerge, pListTwo, 1);
    }
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

void mergesort(Dlist *pList, MergesortCmpFn compare)
{
    Dlist            leftList;
    Dlist            rightList;
    Dlist            sortedList;
    size_t           midList;

    assert(pList);

    if (pList->nrNodes <= 1)
    {
        return;
    }

    midList = pList->nrNodes / 2;

	dlist_construct(&leftList, pList->nodeSize);
	dlist_construct(&rightList, pList->nodeSize);
	dlist_construct(&sortedList, pList->nodeSize);

	dlist_split(pList, &leftList, midList);
	dlist_split(pList, &rightList, midList);

    mergesort(&leftList, compare);
    mergesort(&rightList, compare);
    merge(pList, &leftList, &rightList, compare);

    //dlist_destroy(&leftList);
    //dlist_destroy(&rightList);
}
#endif
