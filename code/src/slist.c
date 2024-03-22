// Library headers
#include <standard.h>

// Local headers
#include "slist.h"

//----------------------------------------------------------------------------//
//- Private functions                                                        -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a node.
 *
 * \param[in]   pData                   Data node.
 * \param[in]   pNext                   Next node, can be NULL.
 * \return                              Constructed node.
 */
static slist_node *slist_node_init(void *pData)
{
    slist_node          *pNode;

    assert(pData);

    pNode           = malloc(sizeof(slist_node));
    pNode->pData    = pData;
    pNode->pNext    = NULL;

    return pNode;
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

slist* slist_init(void)
{
    slist *pList = (slist*) malloc(sizeof(slist));

    pList->pHead        = NULL;
    pList->pTail        = NULL;
    pList->nrNodes      = 0;

    return pList;
}

void slist_destroy(slist *pList)
{
    slist_node      *pCurrent;

    if (!pList)
    {
        return;
    }

    while (pList->pHead)
    {
        pCurrent = pList->pHead;
        pList->pHead = pCurrent->pNext;

        free(pCurrent);
    }

    free(pList);
}

void slist_pushHead(slist *pList, void *pData)
{
    slist_node      *pNode;

    if (!pList)
    {
        return;
    }

    pNode = slist_node_init(pData);

    pNode->pNext    = pList->pHead;
    pList->pHead    = pNode;

    if (pList->nrNodes == 0)
    {
        pList->pTail = pNode;
    }

    pList->nrNodes++;
}

void slist_pushTail(slist *pList, void *pData)
{
    slist_node      *pNode;

    if (!pList)
    {
        return;
    }

    pNode = slist_node_init(pData);

    if (pNode)
    {
        if (pList->nrNodes == 0)
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
}

void *slist_pop(slist *pList)
{
    void*           *pData;

    if (!pList || pList->nrNodes == 0)
    {
        pData = NULL;
    }
    else
    {
        slist_node      *pHead;
    
        pHead = pList->pHead;
        pData = pHead->pData;

        pList->pHead = pHead->pNext;
        pList->nrNodes--;

        free(pHead);
    }

    return pData;
}