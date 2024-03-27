// Library headers
#include <standard.h>

// Local headers
#include "stack.h"

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
static stack_node *stack_node_init(void *pData)
{
    stack_node          *pNode;

    assert(pData);

    pNode           = malloc(sizeof(stack_node));
    pNode->pData    = pData;
    pNode->pNext    = NULL;

    return pNode;
}

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

stack* stack_init(void)
{
    stack *pStack = (stack*) malloc(sizeof(stack));

    pStack->pTop        = NULL;
    pStack->nrNodes     = 0;

    return pStack;
}

void stack_destroy(stack *pStack)
{
    stack_node      *pTop;

    if (!pStack)
    {
        return;
    }

    while (pStack->pTop)
    {
        pTop = pStack->pTop;
        pStack->pTop = pTop->pNext;

        free(pTop);
    }

    free(pStack);
}

void stack_push(stack *pStack, void *pData)
{
    stack_node      *pNode;

    if (!pStack)
    {
        return;
    }

    pNode = stack_node_init(pData);

    pNode->pNext    = pStack->pTop;
    pStack->pTop    = pNode;
    pStack->nrNodes++;
}

void *stack_pop(stack *pStack)
{
    void*           *pData;

    if (!pStack || !pStack->pTop)
    {
        pData = NULL;
    }
    else
    {
        stack_node      *pTop;
    
        pTop = pStack->pTop;
        pData = pTop->pData;

        pStack->pTop = pTop->pNext;
        pStack->nrNodes--;

        free(pTop);
    }

    return pData;
}