/*!
 * \file		stack.h
 *
 * \brief		This file handles generic stack.
 *              A queue is a linear data structure following the order
 *              Last In First Out (LIFO).
 */

#ifndef STACK_H
#define STACK_H

#include <standard.h>

//----------------------------------------------------------------------------//
//- Structure definitions                                                    -//
//----------------------------------------------------------------------------//

/*!
 * Stack node.
 */
typedef struct _stack_node
{
    void                    *pData;             /*!< Data to handle. */
    struct _stack_node      *pNext;             /*!< Next node. */
} stack_node;

typedef struct _stack_node stack_node;

/*!
 * Stack.
 */
typedef struct _stack
{
    stack_node               *pTop;            /*!< Head of the stack. */
    size_t                    nrNodes;          /*!< Number of nodes in the list. */
} stack;

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a stack.
 *
 * \return                          Initialized stack.
 */
stack *stack_init(void);

/*!
 * Destroy a stack.
 *
 * \param[in]   pStack             Stack to destroy.
 */
void stack_destroy(stack *pStack);

/*!
 * Push a node on the top of stack.
 *
 * \param[in]   pStack              Stack.
 * \param[in]   pData               Data to stack.
 */
void stack_push(stack *pStack, void *pData);

/*!
 * Pop a node from the top of the stack.
 *
 * \param[in]   pStack              Stack.
 * \return                          Destack data.
 */
void *stack_pop(stack *pStack);

#endif // STACK_H