/*!
 * \file		dlist.h
 *
 * \brief		This file handles a double list.
 */

#ifndef DLIST_H
#define DLIST_H

#include <standard.h>

//----------------------------------------------------------------------------//
//- Structure definitions                                                    -//
//----------------------------------------------------------------------------//

/*!
 * List node.
 */
typedef struct _dlist_node
{
    void                    *pData;             /*!< Data to handle. */
    struct _dlist_node      *pNext;             /*!< Next node. */
    struct _dlist_node      *pPrev;             /*!< Previous node. */
} dlist_node;

typedef struct _dlist_node dlist_node;

/*!
 * List.
 */
typedef struct _dlist
{
    dlist_node               *pHead;            /*!< Head of the list. */
    dlist_node               *pTail;            /*!< Tail of the list. */
    size_t                    nrNodes;          /*!< Number of nodes in the list. */
} dlist;

typedef int (*DListCmpFn)(const void *pA, const void *pB);

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a double list.
 *
 * \return                          Initialized list .
 */
dlist *dlist_init(void);

/*!
 * Destroy a list.
 *
 * \param[in]   pList               List to destroy.
 */
void dlist_destroy(dlist *pList);

/*!
 * Push a node on the head of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void dlist_pushHead(dlist *pList, void *pData);

/*!
 * Push a node on the tail of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void dlist_pushTail(dlist *pList, void *pData);

/*!
 * Insert a node at the given index.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to insert.
 * \param[in]   index               Index.
 */
void dlist_insert(dlist *pList, void *pData, size_t index);

/*!
 * Pop the head node from the list.
 *
 * \param[in]   pList               List.
 * \return                          Popped data.
 */
void *dlist_popHead(dlist *pList);

/*!
 * Pop the tail node from the list.
 *
 * \param[in]   pList               List.
 * \return                          Popped data.
 */
void *dlist_popTail(dlist *pList);

/*!
 * Print all data of the list.
 *
 * \param[in]   pList               List.
 */
void printList(dlist *pList);

/*!
 * Split one list into two list.
 *
 * nrNodes of srcList will be added in dstList.
 *
 * \param[in]   pSrcList            Source list.
 * \param[in]   pDstList            Destination list.
 * \param[in]   nrNodes             nrNodes.
 */
void dlist_split(dlist *pSrcList, dlist *pDstList);

/*!
 * Join src list at the end of dst list.
 *
 * \param[in]   pSrcList            Source list.
 * \param[in]   pDstList            Destination list.
 * \param[in]   nrNodes             nrNodes.
 */
void dlist_join(dlist *pDstList, dlist *pSrcList);

/*!
 * Sort the list according to the given comparison function.
 *
 * Sort the list with the stable mergesort algorithm.
 *
 * \param[in]   pList               List to sort.
 * \param[in]   compare             Comparison function.
 */
void dlist_sort(dlist *pList, DListCmpFn compare);

#endif // DLIST_H
