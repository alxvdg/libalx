/*!
 * \file		slist.h
 *
 * \brief		This file handles a simple list.
 */

#ifndef SLIST_H
#define SLIST_H

#include <standard.h>

//----------------------------------------------------------------------------//
//- Structure definitions                                                    -//
//----------------------------------------------------------------------------//

/*!
 * List node.
 */
typedef struct _Slist_node
{
    void                    *pData;             /*!< Data to handle. */
    struct _Slist_node      *pNext;             /*!< Next node. */
} SList_node;

typedef struct _Slist_node Slist_node;

/*!
 * List.
 */
typedef struct _Slist
{
    Slist_node               *pHead;            /*!< Head of the list. */
    Slist_node               *pTail;            /*!< Tail of the list. */
    size_t                    nodeSize;         /*!< Size of one node. */
    size_t                    nrNodes;          /*!< Number of nodes in the list. */
} Slist;

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Construct a simple list.
 *
 * \param[in]   pList               List to construct.
 * \param[in]   nodeSize            Node size.
 */
void slist_construct(Slist *pList, size_t nodeSize);

/*!
 * Destroy a list.
 *
 * \param[in]   pList               List to destroy.
 */
void slist_destroy(Slist *pList);

/*!
 * Push a node on the head of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void slist_pushHead(Slist *pList, void *pData);

/*!
 * Push a node on the tail of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void slist_pushTail(Slist *pList, void *pData);
/*!
 * Pop a node from the list.
 *
 * \param[in]   pList               List.
 * \param[out]  pData               Data to pop.
 */
void slist_pop(Slist *pList, void *pData);

#endif // SLIST_H