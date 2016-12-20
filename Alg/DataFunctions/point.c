#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "point.h"
#include "util.h"

Lpoint createPoint(unsigned int id, double x, double y, double z, double intensity, double normal[3])
{
    Lpoint p;

    p.id = id;
    p.x = x;
    p.y = y;
    p.z = z;
    p.intensity = intensity;
    p.border = 0;
    p.boundUsed = 0;
    p.normal[0] = normal[0];
    p.normal[1] = normal[1];
    p.normal[2] = normal[2];

    return p;
}

void resetPoint(Lpoint *point)
{
    (*point).id = 0;
    (*point).x = 0;
    (*point).y = 0;
    (*point).z = 0;
    (*point).intensity = 0;
    (*point).border = 0;
    (*point).boundUsed = 0;
    (*point).normal[0] = 0;
    (*point).normal[1] = 0;
    (*point).normal[2] = 0;
}

/*
// Copy points coordinates between points
void copyCoords(Lpoint *dest, Lpoint *source)
{
    dest->x = source->x;
    dest->y = source->y;
    dest->z = source->z;
}

// Calculate the mid point of two points
Lpoint midPoint(Lpoint *p1, Lpoint *p2)
{
    Lpoint mid;
    
    mid.x = (p1->x + p2->x) / 2.0;
    mid.y = (p1->y + p2->y) / 2.0;
    mid.z = (p1->z + p2->z) / 2.0;

    return mid;
}

// Calculate the average point of a set of points
Lpoint avgPoint(Lpoint *points, int num)
{
    int i = 0;
    Lpoint avg;
    
    avg.x = 0;
    avg.y = 0;
    avg.z = 0;
    
    for(i = 0; i < num; i++)
    {
        avg.x += points[i].x;
        avg.y += points[i].y;
        avg.z += points[i].z;
    }
    
    avg.x /= num;
    avg.y /= num;
    avg.z /= num;
    
    return avg;
}

// Join two arrays with points in one array
Lpoint* mergePoints(Lpoint *pts1, int num1, Lpoint *pts2, int num2)
{    
    Lpoint *merged = NULL;
    
    merged = (Lpoint*)malloc((num1 + num2) * sizeof(Lpoint));   
    memcpy(merged, pts1, num1 * sizeof(Lpoint));
    memcpy(&merged[num1], pts2, num2 * sizeof(Lpoint));
    
    return merged;
}

// Return the different points of two sets of points
Lpoint** distinctPoints(Lpoint **pts1, int numPts1, Lpoint **pts2, int numPts2, int *distNum) // TODO: It should be a better way
{
    int i = 0, j = 0, duplicate = 0, numDist = 0;
    Lpoint **distinct = NULL;
    
    for(i = 0; i < numPts1; i++)
    {
        duplicate = 0;
        
        for(j = 0; j < numPts2; j++)
        {
            if(pts1[i]->id == pts2[j]->id)
            {
                duplicate = 1; break;
            }
        }
        
        if(!duplicate)
        {
            distinct = realloc(distinct, ++numDist * sizeof(Lpoint*));
            distinct[numDist-1] = pts1[i];
        }
    }
    
    *distNum = numDist;
    
    return distinct;
}

// Sort the points in inverse order
void invertPoints(Lpoint *points, int num)
{
    int i = 0;
    Lpoint *aux = NULL;
    
    aux = (Lpoint*)malloc(num * sizeof(Lpoint));
    memcpy(aux, points, num * sizeof(Lpoint));
    
    for(i = 0; i < num; i++)
    {
        points[i] = aux[num-1-i];
    }
    
    free(aux);
}

// Rotate a point from origin
void rotatePoint(Lpoint *p, double sin, double cos, Lpoint *orig)
{
    double x = 0.0, y = 0.0;
    
    x = cos * (p->x - orig->x) - sin * (p->y - orig->y) + orig->x;
    y = sin * (p->x - orig->x) + cos * (p->y - orig->y) + orig->y;
    p->x = x;
    p->y = y;
}
*/
