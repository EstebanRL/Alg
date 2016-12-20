#ifndef GROUP_H

#include "point.h"

#define	GROUP_H

typedef struct Node *Node; // Linked list that stores a point

struct Node 
{
    Lpoint elem;
    Node next;
    Node prev;
};

typedef struct Group *Group;

struct Group // Group of points
{
    unsigned int id;
    unsigned int size;
    int numBounds;
    int numNeighs; 
    char type;     
    char planar;
    double totalZ;
    double totalI;
    double totalX;
    double totalY;   
    float area;
    float volume;
    float maxJump;
    float *normal;
    int *neighbors;
    Node start;
    Node end;
    Node *bounds; 
};  


void createGroup(Group *g, long int id);

Node newNode(Group *g, Lpoint e);

void removePoint(Group *g, Lpoint p);

void removeNode(Group *g, Node n);

void removeGroup(Group *g);

void calculateMaxMinCoordinates(Group group,double *maxX, double *maxY, double *minX, double *minY);

//void mergeGroups(Group *groups, Group g1, Group g2);


#endif	/* GROUP_H */

