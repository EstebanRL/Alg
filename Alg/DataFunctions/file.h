#include "group.h"


int WriteGroupOnTriangleFormat(Group minGroup, Group maxGroup, Group voronoiGroup, char *path);

int WriteGroupOnFile(Group boundaryGroup,char *path, int type);

int ExternalPointsBoundary(char *pathEle, char *pathNode, int idStart, int idEnd, Group *boundaryGroup);

int WriteGroupAndBoundary(Group group, Group boundaryPoints, char *path);

int WriteGroupAndDoubleBoundary(Group group, Group externalBoundaryPoints, Group internalBoundaryPoints,  char *path, int *idStart, int *idEnd );

int WriteDoubleBoundary(Group externalBoundaryPoints, Group internalBoundaryPoints,  char *path);

int ReadVoronoi(char *pathNode, char* pathEdge, Group *boundaryPoints);