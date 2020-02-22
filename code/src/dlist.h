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
typedef struct _Dlist_node
{
    void                    *pData;             /*!< Data to handle. */
    struct _Dlist_node      *pNext;             /*!< Next node. */
    struct _Dlist_node      *pPrev;             /*!< Previous node. */
} DList_node;

typedef struct _Dlist_node Dlist_node;

/*!
 * List.
 */
typedef struct _Dlist
{
    Dlist_node               *pHead;            /*!< Head of the list. */
    Dlist_node               *pTail;            /*!< Tail of the list. */
    size_t                    nodeSize;         /*!< Size of one node. */
    size_t                    nrNodes;          /*!< Number of nodes in the list. */
} Dlist;

//typedef int (*MergesortCmpFn)(Dlist_node *pNodeA, Dlist_node *pNodeB);

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Construct a simple list.
 *
 * \param[in]   pList               List to construct.
 * \param[in]   nodeSize            Node size.
 */
void dlist_construct(Dlist *pList, size_t nodeSize);

/*!
 * Destroy a list.
 *
 * \param[in]   pList               List to destroy.
 */
void dlist_destroy(Dlist *pList);

/*!
 * Push a node on the head of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void dlist_pushHead(Dlist *pList, void *pData);

/*!
 * Push a node on the tail of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void dlist_pushTail(Dlist *pList, void *pData);

/*!
 * Pop the head node from the list.
 *
 * \param[in]   pList               List.
 * \param[out]  pData               Data to pop.
 */
void dlist_popHead(Dlist *pList, void *pData);

/*!
 * Pop the tail node from the list.
 *
 * \param[in]   pList               List.
 * \param[out]  pData               Data to pop.
 */
void dlist_popTail(Dlist *pList, void *pData);

/*!
 * Split one list into two list.
 *
 * nrNodes of srcList will be added in dstList.
 *
 * \param[in]   pSrcList            Source list.
 * \param[in]   pDstList            Destination list.
 * \param[in]   nrNodes             nrNodes.
 */
void dlist_split(Dlist *pSrcList, Dlist *pDstList);

/*!
 * Join src list at the end of dst list.
 *
 * \param[in]   pSrcList            Source list.
 * \param[in]   pDstList            Destination list.
 * \param[in]   nrNodes             nrNodes.
 */
void dlist_join(Dlist *pDstList, Dlist *pSrcList);

#endif // DLIST_H
