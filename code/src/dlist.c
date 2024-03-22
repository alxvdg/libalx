// Library headers
#include <standard.h>

// Local headers
#include "dlist.h"

//----------------------------------------------------------------------------//
//- Private functions                                                        -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a node.
 *
 * \param[in]   pData                   Data node.
 * \return                              Initialized node.
 */
static dlist_node *dlist_node_init(void *pData)
{
    dlist_node          *pNode;

    if (pData == NULL)
    {
        pNode = NULL;
    }
    else
    {
        pNode           = malloc(sizeof(dlist_node));
        pNode->pData    = pData;
        pNode->pNext    = NULL;
        pNode->pPrev    = NULL;
    }

    return pNode;
}

/*!
 * Get the 'index' node of the list from the head.
 *
 * Get just a node according to the given index.
 * Do no take the node from the list. The ownership of the node
 * still belongs to the list.
 *
 * \param[in]   pList               List.
 * \param[in]	index		        Node index within the list.
 * \return                          Index node, may be NULL.
 */
static dlist_node *dlist_getNode(dlist *pList, size_t index)
{
    dlist_node          *pNode;

    if (!pList)
    {
        return NULL;
    }

    pNode = pList->pHead;

    for (size_t i = 1; i < index; i++)
    {
	    pNode = pNode->pPrev;
    }
    
    return pNode;
}

/*!
 * Take the node at the head of the list.
 *
 * Do not free the node, the ownership of the returned node
 * is pass from the list to the caller.
 *
 * It is the responsability of the caller to free the node
 * correctly.
 *
 * \param[in]   pList               List.
 * \return                          Head node, may be NULL.
 */
static dlist_node *dlist_takeHead(dlist *pList)
{
    dlist_node      *pHead;

    if (pList == NULL || pList->nrNodes == 0)
    {
        pHead = NULL;
    }
    else
    {
        pHead = pList->pHead;

        pList->pHead = pHead->pPrev;
        pList->nrNodes--;
    }

    return pHead;
}

/*!
 * Take the node at the tail of the list.
 *
 * Do not free the node, the ownership of the returned node
 * is pass from the list to the caller.
 *
 * It is the responsability of the caller to free the node
 * correctly.
 *
 * \param[in]   pList               List.
 * \return                          Tail node, may be NULL.
 */
static dlist_node *dlist_takeTail(dlist *pList)
{
    dlist_node      *pTail;

    if (pList == NULL || pList->nrNodes == 0)
    {
        pTail = NULL;
    }
    else
    {
        pTail = pList->pTail;

        pList->pTail = pTail->pNext;
        pList->nrNodes--;
    }

    return pTail;
}

/*!
 * Insert the given node at the head of the list.
 *
 * The given node must be allocated.
 * 
 * The ownership of the given node is given by the caller
 * to the list.
 *
 * \param[in]   pList               List.
 * \return                          Node to insert, may be NULL.
 */
static void dlist_insertHead(dlist *pList, dlist_node *pNode)
{
    if (pList == NULL || pNode == NULL)
    {
        return;
    }

    pNode->pNext = NULL;
    pNode->pPrev = pList->pHead;

    if (pList->nrNodes == 0)
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

/*!
 * Insert the given node at the tail of the list.
 *
 * The given node must be allocated.
 * 
 * The ownership of the given node is given by the caller
 * to the list.
 *
 * \param[in]   pList               List.
 * \return                          Node to insert, may be NULL.
 */
static void dlist_insertTail(dlist *pList, dlist_node *pNode)
{
    if (pList == NULL || pNode == NULL)
    {
        return;
    }

    pNode->pNext = pList->pTail;
    pNode->pPrev = NULL;

    if (pList->nrNodes == 0)
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

/*!
 * Insert the given node pInsertNode next to pNode.
 *
 * The given node must be allocated.
 * 
 * The ownership of the given node is given by the caller
 * to the list.
 *
 * \param[in]   pList               List.
 * \param[in]   pNode               Node.
 * \param[in]   pInsertNode         Node to insert.
 */
static void dlist_insertNextTo(dlist *pList, dlist_node *pNode, dlist_node *pInsertNode)
{
    if (pList == NULL || pNode == NULL || pInsertNode == NULL)
    {
        return;
    }

    pInsertNode->pNext = pNode->pNext;
    pInsertNode->pPrev = pNode;

    if (pNode->pNext == NULL)
    {
        pList->pHead = pInsertNode;
    }
    else
    {
        dlist_node      *pNext;
    
        pNext = pNode->pNext;
        pNext->pPrev = pInsertNode;
    }

    pNode->pNext = pInsertNode;

    pList->nrNodes++;
}

/*!
 * Merge the two given list according to the given comparison function.
 *
 * \param[in]   pListA              List A.
 * \param[in]   pListB              List B.
 * \param[in]   compare             Comparision function.
 */
static void merge(dlist *pListA, dlist *pListB, DListCmpFn compare)
{
    dlist_node      *pNodeA;
    dlist_node      *pNodeB;
    size_t          listA_nrNodes;

    if (pListA == NULL || pListB == NULL)
    {
        return;
    }
    
    if ((pListA->pHead == NULL) || (pListA->nrNodes == 0))
    {
        return;
    }

    if ((pListB->pHead == NULL) || (pListB->nrNodes == 0))
    {
        return;
    }

    //
    // initialy take both heads of the lists
    //
    pNodeA = pListA->pHead;
    pNodeB = pListB->pHead;

    listA_nrNodes = pListA->nrNodes;

    while (listA_nrNodes > 0 && pListB->nrNodes > 0)
    {
        int             result;

        result = compare(pNodeA->pData, pNodeB->pData);

        if (result >= 0)
        {
            pNodeB = dlist_takeHead(pListB);

            dlist_insertNextTo(pListA, pNodeA, pNodeB);

            //
            // actualize the head of the list
            //
            pNodeB = pListB->pHead;
        }
        else
        {
            pNodeA = pNodeA->pPrev;
            listA_nrNodes--;
        }
    }

    //
    // No list A elements remaining to compare, empty list B
    // at the tail of list A.
    //
    while (pListB->nrNodes > 0)
    {
        pNodeB = dlist_takeHead(pListB);

        dlist_insertTail(pListA, pNodeB);
    }
}

/*!
 * First part of the mergesort algorithm.
 *
 * Split the given list into a series of 1 element list.
 *
 * Then compare each list with its adjacent list and merge them
 * according to the given comparison function.
 * 
 * To optimize memory allocation, we allocate only temporary lists
 * for the "right side". 
 * 
 * \param[in]   pList               List to sort.
 * \param[in]   compare             Comparison function.
 */
static void mergesort(dlist *pList, DListCmpFn compare)
{
    dlist            *pRightList;

    if ((pList == NULL) || (pList->nrNodes <= 1))
    {
        return;
    }

    pRightList = dlist_init();

    dlist_split(pList, pRightList);

    mergesort(pList, compare);
    mergesort(pRightList, compare);
    merge(pList, pRightList, compare);

    dlist_destroy(pRightList);
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

dlist *dlist_init(void)
{
    dlist *pList = (dlist*) malloc(sizeof(dlist));

    pList->pHead        = NULL;
    pList->pTail        = NULL;
    pList->nrNodes      = 0;

    return pList;
}

void dlist_destroy(dlist *pList)
{
    dlist_node      *pCurrent;

    if (pList == NULL)
    {
        return;
    }

    while (pList->nrNodes != 0)
    {
        pCurrent        = pList->pHead;
        pList->pHead    = pCurrent->pPrev;

        pList->nrNodes--;
        free(pCurrent);
    }

    free(pList);
}

void dlist_pushHead(dlist *pList, void *pData)
{
    dlist_node      *pNode;

    if (pList == NULL)
    {
        return;
    }

    pNode = dlist_node_init(pData);

    dlist_insertHead(pList, pNode);
}

void dlist_pushTail(dlist *pList, void *pData)
{
    dlist_node      *pNode;

    if (!pList)
    {
        return;
    }

    pNode = dlist_node_init(pData);

    dlist_insertTail(pList, pNode);
}

void *dlist_popHead(dlist *pList)
{
    dlist_node      *pHead = NULL;
    void            *pData = NULL;

    pHead = dlist_takeHead(pList);

    if (pHead)
    {
        pData = pHead->pData;

        free(pHead);
    }

    return pData;
}

void *dlist_popTail(dlist *pList)
{
    dlist_node      *pTail = NULL;
    void            *pData = NULL;

    pTail = dlist_takeTail(pList);

    if (pTail)
    {
        pData = pTail->pData;

        free(pTail);
    }

    return pData;
}

void printList(dlist *pList)
{
    uint32_t	*res;
    dlist_node *pHead;

    if (pList == NULL)
    {
        return;
    }
    
    pHead = pList->pHead;

    while(pHead != NULL)
    {
        res = pHead->pData;
        printf("%u ", *res);
        pHead = pHead->pPrev;
    }
    printf("\n");
}

void dlist_split(dlist *pListA, dlist *pListB)
{
    size_t	midList;
    dlist_node *pMidNode;
    dlist_node *pPrev;

    if (!pListA || !pListB)
    {
        return;
    }

    midList 		= pListA->nrNodes / 2;
    
    pMidNode	= dlist_getNode(pListA, midList);

    if (pMidNode)
    {
        pPrev	= pMidNode->pPrev;

        pPrev->pNext	 = NULL;
        pListB->pHead        = pPrev;
        pListB->pTail        = pListA->pTail;
        pListB->nrNodes      = pListA->nrNodes - midList;

        pMidNode->pPrev	 = NULL;
        pListA->pTail        = pMidNode;
        pListA->nrNodes      = midList;
    }
    else
    {
        pListB->pHead        = NULL;
        pListB->pTail        = NULL;
        pListB->nrNodes      = 0;
    }
}

void dlist_join(dlist *pDstList, dlist *pSrcList)
{
    if (!pDstList || !pSrcList)
    {
        return;
    }

   pDstList->pTail->pPrev	= pSrcList->pHead;
   pSrcList->pHead->pNext   = pDstList->pTail;
   pDstList->pTail          = pSrcList->pTail;
   pDstList->nrNodes	    += pSrcList->nrNodes;

   pSrcList->pHead	= NULL;
   pSrcList->pTail	= NULL;
   pSrcList->nrNodes	= 0;
}

void dlist_sort(dlist *pList, DListCmpFn cmp)
{
    if (pList == NULL)
    {
        return;
    }

    if (cmp == NULL)
    {
        return;
    }

    mergesort(pList, cmp);
}