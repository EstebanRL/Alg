/* 
 * File:   Exterior.h
 * Author: esteban
 *
 */

#include "../DataFunctions/group.h"
#include "../Alg.h"
#include "Concave.h"
#include "JarvisMarch.h"
#include "GaussArea.h"

int ExteriorAlgorithm(Group *externalPointsBoundaryGroup, Group buildingGroup, Group *allGroups, int numGroups, int k);