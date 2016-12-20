/* 
 * File:   Voronoi.h
 * Author: esteban
 *
 */

#include "../DataFunctions/group.h"
#include "../Alg.h"
#include "../DataFunctions/file.h"
#include "GaussArea.h"
#include "Concave.h"
#include "JarvisMarch.h"

int VoronoiAlgorithm(Group *voronoiBoundaryGroup, Group buildingGroup, Group *allGroups, int numGroups, int k);