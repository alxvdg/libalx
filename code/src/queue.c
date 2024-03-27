// Library headers
#include <standard.h>

// Local headers
#include "queue.h"

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
static queue_node *queue_node_init(void *pData)
{
    queue_node          *pNode;

    assert(pData);

    pNode           = malloc(sizeof(queue_node));
    pNode->pData    = pData;
    pNode->pNext    = NULL;

    return pNode;
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

queue* queue_init(void)
{
    queue *pQueue = (queue*) malloc(sizeof(queue));

    pQueue->pHead        = NULL;
    pQueue->pTail        = NULL;
    pQueue->nrNodes      = 0;

    return pQueue;
}

void queue_destroy(queue *pQueue)
{
    queue_node      *pHead;

    if (!pQueue)
    {
        return;
    }

    while (pQueue->pHead)
    {
        pHead           = pQueue->pHead;
        pQueue->pHead   = pHead->pNext;

        free(pHead);
    }

    free(pQueue);
}

void queue_enqueue(queue *pQueue, void *pData)
{
    queue_node      *pNode;
    queue_node      *pTail;

    if (!pQueue)
    {
        return;
    }

    pNode = queue_node_init(pData);

    if (pQueue->nrNodes == 0)
    {
        pQueue->pHead = pNode;
    }
    else
    {
        pTail           = pQueue->pTail;
        pTail->pNext    = pNode;
    }
    
    pQueue->pTail   = pNode;
    pQueue->nrNodes++;
}

void *queue_dequeue(queue *pQueue)
{
    void*           *pData;

    if (!pQueue || !pQueue->pHead)
    {
        pData = NULL;
    }
    else
    {
        queue_node      *pHead;
    
        pHead = pQueue->pHead;
        pData = pHead->pData;

        pQueue->pHead = pHead->pNext;
        pQueue->nrNodes--;

        free(pHead);
    }

    return pData;
}