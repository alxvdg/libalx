// Library headers
#include <standard.h>

// Local headers
#include "dlist.h"

//----------------------------------------------------------------------------//
//- Private functions                                                        -//
//----------------------------------------------------------------------------//

/*!
 * Return the head of the list.
 *
 * \param[in]   pList           List.
 * \return                      Head of the list.
 */
static Dlist_node *dlist_head(Dlist *pList)
{
    assert(pList);

    return pList->pHead;
}

/*!
 * Return the tail of the list.
 *
 * \param[in]   pList           List.
 * \return                      Head of the list.
 */
static Dlist_node *dlist_tail(Dlist *pList)
{
    assert(pList);

    return pList->pTail;
}

/*!
 * Return the number of nodes within the list.
 *
 * \param[in]   pList           List.
 * \return                      Number of nodes.
 */
static size_t dlist_nrNodes(Dlist *pList)
{
    assert(pList);

    return pList->nrNodes;
}

/*!
 * Construct a node.
 *
 * \param[in]   nodeSize                Node size, in bytes.
 * \param[in]   pData                   Data node.
 * \param[in]   pNext                   Next node, can be NULL.
 * \param[in]   pPrev                   Previous node, can be NULL.
 * \return                              Constructed node.
 */
static Dlist_node *dlist_node_construct(size_t nodeSize, void *pData, Dlist_node *pNext, Dlist_node *pPrev)
{
    Dlist_node          *pNode;

    assert(pData);

    pNode           = malloc(sizeof(Dlist_node));

    pNode->pData    = malloc(nodeSize);
    memcpy(pNode->pData, pData, nodeSize);

    pNode->pNext    = pNext;
    pNode->pPrev    = pPrev;

    return pNode;
}



/*!
 * Return the next node of a node.
 *
 * \param[in]   pNode               Node.
 * \return                          Next node, may be NULL.
 */
static Dlist_node *dlist_node_next(Dlist_node *pNode)
{
    assert(pNode);

    return pNode->pNext;
}

/*!
 * Return the previous node of a node.
 *
 * \param[in]   pNode               Node.
 * \return                          Next node, may be NULL.
 */
static Dlist_node *dlist_node_prev(Dlist_node *pNode)
{
    assert(pNode);

    return pNode->pPrev;
}

/*!
 * Return the data of a node.
 *
 * \param[in]   pNode               Node.
 * \param[out]  pData               Data.
 */
static void dlist_node_data(Dlist_node *pNode, void *pData)
{
    assert(pNode);
    assert(pData);

    pData = pNode->pData;
}

/*!
 * Get the 'index' node of the list from the head.
 *
 * \param[in]   pList               List.
 * \param[in]	index		    Node index within the list.
 * \return                          Index node, may be NULL.
 */
static Dlist_node *dlist_getNode(Dlist *pList, size_t index)
{
    Dlist_node          *pNode;

    assert(pList);

    pNode = dlist_head(pList);

    for (size_t i = 1; i < index; i++)
    {
	pNode = dlist_node_prev(pNode);
    }
    
    return pNode;
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

void dlist_construct(Dlist *pList, size_t nodeSize)
{
    assert(pList);
    assert(nodeSize > 0);

    pList->pHead        = NULL;
    pList->pTail        = NULL;
    pList->nodeSize     = nodeSize;
    pList->nrNodes      = 0;
}

void dlist_destroy(Dlist *pList)
{
    Dlist_node      *pCurrent;

    assert(pList);

    while (pList->pHead)
    {
        pCurrent = pList->pHead;
        pList->pHead = pCurrent->pNext;

        free(pCurrent->pData);
        free(pCurrent);
    }
}

void dlist_pushHead(Dlist *pList, void *pData)
{
    Dlist_node      *pNode;

    assert(pList);

    pNode = dlist_node_construct(sizeof(pList->nodeSize) ,pData, NULL, pList->pHead);

    if (dlist_nrNodes(pList) == 0)
    {
        pList->pTail = pNode;
    }
    else
    {
        pList->pHead->pNext = pNode;
    }
    
    pList->pHead = pNode;

    pList->nrNodes++;
}

void dlist_pushTail(Dlist *pList, void *pData)
{
    Dlist_node      *pNode;

    assert(pList);

    pNode = dlist_node_construct(sizeof(pList->nodeSize) , pData, pList->pTail, NULL);

    if (dlist_nrNodes(pList) == 0)
    {
        pList->pHead = pNode;
    }
    else
    {
        pList->pTail->pPrev = pNode;
    }

    pList->pTail = pNode;

    pList->nrNodes++;
}

void dlist_pushAfter(Dlist *pNode, Dlist *pNext)
{

}

void dlist_pushBefore(Dlist *pNode, Dlist *pPrev)
{

}

void dlist_popHead(Dlist *pList, void *pData)
{
    Dlist_node      *pHead;

    assert(pList);
    assert(pList->pHead);
    assert(pData);

    pHead = dlist_head(pList);
    memcpy(pData, pHead->pData, pList->nodeSize);
    dlist_node_data(pHead, pData);

    pList->pHead = dlist_node_prev(pHead);
    pList->nrNodes--;

    free(pHead->pData);
    free(pHead);
}

void dlist_popTail(Dlist *pList, void *pData)
{
    Dlist_node      *pTail;

    assert(pList);
    assert(pList->pTail);
    assert(pData);

    pTail = dlist_tail(pList);
    memcpy(pData, pTail->pData, pList->nodeSize);
    dlist_node_data(pTail, pData);

    pList->pTail = dlist_node_next(pTail);
    pList->nrNodes--;

    free(pTail->pData);
    free(pTail);
}

void dlist_split(Dlist *pListA, Dlist *pListB)
{
    size_t	midList;
    Dlist_node *pMidNode;
    Dlist_node *pPrev;

    assert(pListA);
    assert(pListB);
    assert(pListA->nodeSize == pListB->nodeSize);

    midList 		= pListA->nrNodes / 2;
    
    pMidNode	= dlist_getNode(pListA, midList);
    pPrev	= dlist_node_prev(pMidNode);

    pPrev->pNext	 = NULL;
    pListB->pHead        = pPrev;
    pListB->pTail        = pListA->pTail;
    pListB->nrNodes      = pListA->nrNodes - midList;

    pMidNode->pPrev	 = NULL;
    pListA->pTail        = pMidNode;
    pListA->nrNodes      = midList;
}

void dlist_join(Dlist *pListA, Dlist *pListB)
{
    assert(pListA);
    assert(pListB);
    assert(pListA->nodeSize == pListB->nodeSize);

   pListB->pHead->pNext	= pListA->pTail;
   pListA->pTail->pPrev	= pListB->pHead;
   pListA->nrNodes	+= pListB->nrNodes;

   pListB->pHead	= NULL;
   pListB->pTail	= NULL;
   pListB->nrNodes	= 0;
}
