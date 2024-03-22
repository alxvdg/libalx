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
typedef struct _slist_node
{
    void                    *pData;             /*!< Data to handle. */
    struct _slist_node      *pNext;             /*!< Next node. */
} slist_node;

typedef struct _slist_node slist_node;

/*!
 * List.
 */
typedef struct _slist
{
    slist_node               *pHead;            /*!< Head of the list. */
    slist_node               *pTail;            /*!< Tail of the list. */
    size_t                    nrNodes;          /*!< Number of nodes in the list. */
} slist;

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a new list.
 *
 * \param[in]   nodeSize            Node size.
 * \return                          Pointer to a new list.
 */
slist* slist_init(void);

/*!
 * Destroy a list.
 *
 * \param[in]   pList               List to destroy.
 */
void slist_destroy(slist *pList);

/*!
 * Push a node on the head of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void slist_pushHead(slist *pList, void *pData);

/*!
 * Push a node on the tail of the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pData               Data to push.
 */
void slist_pushTail(slist *pList, void *pData);

/*!
 * Pop a node from the list.
 *
 * \param[in]   pList               List.
 * \return                          Data to pop.
 */
void *slist_pop(slist *pList);

#endif // SLIST_H