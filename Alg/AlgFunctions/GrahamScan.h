/* 
 * File:   GrahamScan.h
 * Author: esteban
 *
 */

#include "../DataFunctions/group.h"
#include "GaussArea.h"
/*      
 *      Return 0 if successful, if not:
 *              - 1: 'group' contains less than 3 points
 *              - 2: 'boundaryGroup' not inicialized
 *              - 3: 'group' not inicialized'
 */
int GrahamScan(Group *boundaryGroup, Group group);

