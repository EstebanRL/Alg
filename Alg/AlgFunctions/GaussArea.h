/* 
 * File:   GaussArea.h
 * Author: esteban
 *
 */

#include "../DataFunctions/group.h"
/*      
 *      Return 0 if successful, if not:
 *              - 1: 'group' not inicialized
 *              - 2: 'group' contains less than 3 points
 *      Points must be sorted in clockwise or counter-clockwise order
 */
int GaussArea(Group *group);
