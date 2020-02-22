// Library headers
#include <standard.h>

// Local headers
#include "slist.h"

//----------------------------------------------------------------------------//
//- Private functions                                                        -//
//----------------------------------------------------------------------------//

/*!
 * Return the head of the list.
 *
 * \param[in]   pList           List.
 * \return                      Head of the list.
 */
static Slist_node *slist_head(Slist *pList)
{
    assert(pList);

    return pList->pHead;
}

/*!
 * Return the number of nodes within the list.
 *
 * \param[in]   pList           List.
 * \return                      Number of nodes.
 */
static size_t slist_nrNodes(Slist *pList)
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
 * \return                              Constructed node.
 */
static Slist_node *slist_node_construct(size_t nodeSize, void *pData, Slist_node *pNext)
{
    Slist_node          *pNode;

    assert(pData);

    pNode           = malloc(sizeof(Slist_node));

    pNode->pData    = malloc(nodeSize);
    memcpy(pNode->pData, pData, nodeSize);

    pNode->pNext    = pNext;

    return pNode;
}

/*!
 * Return the next node of a node.
 *
 * \param[in]   pNode               Node.
 * \return                          Next node, may be NULL.
 */
static Slist_node *slist_node_next(Slist_node *pNode)
{
    assert(pNode);

    return pNode->pNext;
}

/*!
 * Return the data of a node.
 *
 * \param[in]   pNode               Node.
 * \param[out]  pData               Data.
 */
static void slist_node_data(Slist_node *pNode, void *pData)
{
    assert(pNode);
    assert(pData);

    pData = pNode->pData;
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

void slist_construct(Slist *pList, size_t nodeSize)
{
    assert(pList);
    assert(nodeSize > 0);

    pList->pHead        = NULL;
    pList->pTail        = NULL;
    pList->nodeSize     = nodeSize;
    pList->nrNodes      = 0;
}

void slist_destroy(Slist *pList)
{
    Slist_node      *pCurrent;

    assert(pList);

    while (pList->pHead)
    {
        pCurrent = pList->pHead;
        pList->pHead = pCurrent->pNext;

        free(pCurrent->pData);
        free(pCurrent);
    }
}

void slist_pushHead(Slist *pList, void *pData)
{
    Slist_node      *pNode;

    assert(pList);

    pNode = slist_node_construct(pList->nodeSize, pData, pList->pHead);

    pList->pHead    = pNode;

    if (slist_nrNodes(pList) == 0)
    {
        pList->pTail = pNode;
    }

    pList->nrNodes++;
}

void slist_pushTail(Slist *pList, void *pData)
{
    Slist_node      *pNode;

    assert(pList);

    pNode = slist_node_construct(pList->nodeSize, pData, NULL);

    if (slist_nrNodes(pList) == 0)
    {
        pList->pHead            = pNode;
        pList->pTail            = pNode;
    }
    else
    {
        pList->pTail->pNext     = pNode;
        pList->pTail            = pNode;
    }

    pList->nrNodes++;
}

void slist_pop(Slist *pList, void *pData)
{
    Slist_node      *pHead;

    assert(pList);
    assert(pList->pHead);
    assert(pData);

    pHead = slist_head(pList);
    memcpy(pData, pHead->pData, pList->nodeSize);
    slist_node_data(pHead, pData);

    pList->pHead = slist_node_next(pHead);
    pList->nrNodes--;

    free(pHead->pData);
    free(pHead);
}