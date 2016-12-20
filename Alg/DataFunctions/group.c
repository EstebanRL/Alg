#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "group.h"
#include "util.h"
#include "../Alg.h"

void createGroup(Group *g, long int id) 
{
    (*g) =(Group)malloc(sizeof (struct Group));
    (*g)->start = (Node) malloc(sizeof (struct Node));
    (*g)->end = (*g)->start;
    ((*g)->end)->next = NULL;
    ((*g)->start)->prev = NULL;
    (*g)->bounds = NULL;
    (*g)->numBounds = 0;
    (*g)->size = 0;
    (*g)->totalZ = 0.0;
    (*g)->totalI = 0.0;
    (*g)->totalX = 0.0;
    (*g)->totalY = 0.0;
    (*g)->id = id; 
    (*g)->type = GROUND;		
    (*g)->neighbors = NULL;
    (*g)->numNeighs = 0;
    (*g)->normal = (float*)calloc(3, sizeof(float)); 
    (*g)->planar = 0;
    (*g)->area = 0.0;
    (*g)->volume = 0.0;
}

Node newNode(Group *g, Lpoint e) 
{
    Node aux = NULL;

    aux = (*g)->end;
    
    e.gId = (*g)->id;
    aux->elem = e;
    aux->next = (Node)malloc(sizeof(struct Node));
    (*g)->end = aux->next;
    ((*g)->end)->next = NULL;
    ((*g)->end)->prev = aux;    
    (*g)->totalZ += e.z;
    (*g)->totalI += e.intensity;  
    (*g)->totalX += e.x;
    (*g)->totalY += e.y;  
    (*g)->normal[0] += e.normal[0];
    (*g)->normal[1] += e.normal[1];
    (*g)->normal[2] += e.normal[2];
    (*g)->size++;
    
    return aux;
}

void removePoint(Group *g, Lpoint p){
    
    Node aux = NULL;
    aux=(*g)->start;
    int found = 0;
    
    while(aux->next!=NULL && found == 0)
    {
        if(aux->elem.id == p.id)
        {
            removeNode(g,aux);
            found=1;
        }
        aux=aux->next;
    }
}


void removeNode(Group *g, Node n) 
{
    Node firstNode = NULL, nextNode = NULL, prevNode = NULL;
    
    firstNode = (*g)->start;
    
    if(firstNode->elem.id == n->elem.id) 
    {
        (*g)->start = n->next;      
    }
    else
    {
            nextNode = n->next;
            prevNode = n->prev;      
            prevNode->next = nextNode;
            nextNode->prev = prevNode;     

    }
    memset (&(n->elem),0,sizeof(Lpoint));
    free(n);
    (*g)->size--;
}

void removeGroup(Group *g) 
{
    Node aux = NULL, next = NULL;
    
    aux = (*g)->start;

    while((*g)->size != 0) 
    {
        next = aux->next;
        free(aux);
        (*g)->size--;
        aux = next;
    }

    free((*g)->neighbors);          
    free((*g)->normal);  
    free((*g)->bounds); 
    (*g)->numNeighs = 0;
    (*g)->numBounds = 0;
}




void calculateMaxMinCoordinates(Group group,double *maxX, double *maxY, double *minX, double *minY){
    
     Node aux = NULL;
    
        //Points are sorted by x value 
    *minX=(group)->start->elem.x;  
    *maxX=(group)->start->elem.x;
    *minY=(group)->start->elem.y;
    *maxY=(group)->start->elem.y;
    aux=(group)->start;
    while((aux->next)!=NULL)
    {
      if(aux->elem.x<*minX)
          *minX=aux->elem.x;
      if(aux->elem.x>*maxX)
          *maxX=aux->elem.x;
      if(aux->elem.y<*minY)
          *minY=aux->elem.y;
      if(aux->elem.y>*maxY)
          *maxY=aux->elem.y;
     aux=aux->next;
    }

}

int ContainsPointWithID(Group group, unsigned int id){
    
     Node aux = NULL;
    
    aux=(group)->start;
    while((aux->next)!=NULL)
    {
      if(aux->elem.id == id)
          return 1;
     aux=aux->next;
    }
    
    return 0;
}

// Calculate the boundary cube of a group with equal {x, y, z} lengths
/*
Vector3D boundingBoxGroup(Group g, float *maxRadius)
{
    long i = 0;
    Vector3D center, min, max, radius;
    Node n = NULL;
    
    min.x = DBL_MAX, min.y = DBL_MAX, min.z = DBL_MAX, max.x = -DBL_MAX, max.y = -DBL_MAX, max.z = -DBL_MAX;
    
    n = g->start;
    
    for(i = 0; i < g->size; i++)
    {
        if(n->elem.x < min.x) min.x = n->elem.x; if(n->elem.x > max.x) max.x = n->elem.x;
        if(n->elem.y < min.y) min.y = n->elem.y; if(n->elem.y > max.y) max.y = n->elem.y;
        if(n->elem.z < min.z) min.z = n->elem.z; if(n->elem.z > max.z) max.z = n->elem.z;
        
        n = n->next;
    }  
    
    radius = getRadius(min, max, maxRadius);
    center = getCenter(min, radius);

    return center;
}
*/