/*!
 * \file		astar.h
 *
 * \brief		This file handles astar algorithm.
 */

#ifndef ASTAR_H
#define ASTAR_H

#include <standard.h>

//----------------------------------------------------------------------------//
//- Structure definitions                                                    -//
//----------------------------------------------------------------------------//

/*!
 * AStar node.
 */
typedef struct _astar_node
{
    point               coord;
    size_t              cost;
    double              heuristic;
} astar_node;

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

/*!
 * Initialize a new list.
 *
 * \param[in]   pStart              Start point.
 * \param[in]   pDestination        Destination point.
 * \param[in]   pGrid               Grid to go through.
 * \return                          The path as a list of points.
 */
dlist *astar_compute(point *pStart, point *pDestination, int **pGrid);

#endif // SLIST_H