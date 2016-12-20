/* 
 * File:   JarvisMarch.h
 * Author: esteban
 *
 */

#include "../DataFunctions/group.h"
#include "GaussArea.h"
/*      
 *      Return 0 if succesussful, if not:
 *              - 1: 'group' contains less than 3 points
 *              - 2: 'boundaryGroup' not inicialized
 *              - 3: 'group' not inicialized
 */
int JarvisMarch(Group *boundaryGroup, Group group);