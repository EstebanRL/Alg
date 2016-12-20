/* 
 * File:   Statistically.h
 * Author: esteban
 *
 */

#include "../DataFunctions/group.h"
#include "../Alg.h"
#include "GaussArea.h"
/*      
 *      Return 0 if succesussful, if not:
 *              - 1: 'group' not inicilized
 *              - 2: 'allGroups' not inicialized
 */
int calculateAreaVolumenStatistically(Group *group, Group *allGroups, unsigned int numGroups, unsigned short UNITSAPPROXIMATION);

int calculateVolumenStatistically(Group *group, Group *allGroups, unsigned int numGroups, unsigned short UNITSAPPROXIMATION);