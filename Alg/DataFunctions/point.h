#ifndef POINT_H

#define	POINT_H

typedef struct // TODO: Reset char flag fields for memory reduction 
{
    unsigned int id;
    unsigned int gId;   
    double x;
    double y;
    double z;
    double intensity;
    float normal[3];
    char planar;       
    char border;        
    char boundUsed;             

} Lpoint; // LiDAR point data structure

Lpoint createPoint(unsigned int id, double x, double y, double z, double intensity, double normal[3]);

void resetPoint(Lpoint *point);
/*
void copyCoords(Lpoint *dest, Lpoint *source);

Lpoint midPoint(Lpoint *p1, Lpoint *p2);

Lpoint avgPoint(Lpoint *points, int num);

Lpoint* mergePoints(Lpoint *pts1, int num1, Lpoint *pts2, int num2);

Lpoint** distinctPoints(Lpoint **pts1, int numPts1, Lpoint **pts2, int numPts2, int *distNum);

void invertPoints(Lpoint *points, int num);

void rotatePoint(Lpoint *p, double sin, double cos, Lpoint *orig);
*/

#endif	/* POINT_H */
