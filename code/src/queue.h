/*!
 * \file		queue.h
 *
 * \brief		This file handles generic queue.
 *              A queue is a linear data structure following the order
 *              First In First Out (FIFO).
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <standard.h>

//----------------------------------------------------------------------------//
//- Structure definitions                                                    -//
//----------------------------------------------------------------------------//

/*!
 * Queue node.
 */
typedef struct _queue_node
{
    void                    *pData;             /*!< Data to handle. */
    struct _queue_node      *pNext;             /*!< Next node. */
} queue_node;

typedef struct _queue_node queue_node;

/*!
 * Queue.
 */
typedef struct _queue
{
    queue_node               *pHead;            /*!< Head of the queue. */
    queue_node               *pTail;            /*!< Tail of the queue. */
    size_t                    nrNodes;          /*!< Number of nodes in the list. */
} queue;

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a queue.
 *
 * \return                          Initialized queue.
 */
queue *queue_init(void);

/*!
 * Destroy a queue.
 *
 * \param[in]   pQueue              Queue to destroy.
 */
void queue_destroy(queue *pQueue);

/*!
 * Enqueue a node on the queue.
 *
 * \param[in]   pQueue              Queue.
 * \param[in]   pData               Data to queue.
 */
void queue_enqueue(queue *pQueue, void *pData);

/*!
 * Dequeue a node from the queue.
 *
 * \param[in]   pQueue              Queue.
 * \return                          Dequeued data.
 */
void *queue_dequeue(queue *pQueue);

#endif // QUEUE_H