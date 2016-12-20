/* 
 * File:   Concave.c
 * Author: esteban
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Concave.h"

/*
 * Check if point with 'testx' and 'testy' coordinates is inside polygon formed by
 * 'vertx' and 'verty' coordinates. 'nvert' is the number of vertices.
 * Return 1 if is inside, 0 if outside
*/
int pnpoly(int nvert, double *vertx, double *verty, double testx, double testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}

/*
* Auxiliar method to know if a point is inside a polygon 
* Return 1 if is inside, 0 if outside
*/

int PointInPolygon(Lpoint point, Group *polygon){
    
    Node aux = NULL;
    double *vertx,*verty;
    int i=0, isInside = 0;
    
    vertx = (double*)malloc((*polygon)->size*(sizeof(double)));
    verty = (double*)malloc((*polygon)->size*(sizeof(double)));
    
    aux = (*polygon)->start;
    while(aux->next!=NULL)
    {
        vertx[i] = round((aux->elem.x)*100);
        verty[i] = round((aux->elem.y)*100);
        aux = aux->next;
        i++;      
    }
    
    isInside = pnpoly((*polygon)->size,vertx,verty,round((point.x)*100),round((point.y)*100));
    
    free(vertx);
    free(verty);
    
    return isInside;
    
}

double getDistance(Lpoint a, Lpoint b)
{
    double distance;
    distance = sqrt((round((a.x)*100) - round((b.x)*100)) * (round((a.x)*100) - round((b.x)*100)) + (round((a.y)*100)-round((b.y)*100)) *(round((a.y)*100)-round((b.y)*100)));  
    return distance;
}


void FindNearestPoints(Group *nearestPoints, Group *tempGroup, Lpoint point, int neighbours){
    
    Node aux = NULL, nodeDiscarted = NULL;
    Group *tempForAngles;
    Lpoint pointDiscarted;
    int i=0;
    double minDistance, testDistance;

    removeGroup(nearestPoints);
    createGroup(nearestPoints,0);
    
    tempForAngles=(Group*)malloc(sizeof(Group));
    createGroup(tempForAngles,0);
    aux=(*tempGroup)->start;
    while(aux->next!=NULL)
    {
        newNode(tempForAngles, aux->elem);
        aux=aux->next;
    }
    
     if((*tempGroup)->size <= neighbours)
        neighbours = (*tempGroup)->size;
    
    for(i=0;i<neighbours;i++)
    {
        aux = (*tempForAngles)->start;
        minDistance = getDistance((*tempForAngles)->start->elem,point);
        pointDiscarted = aux->elem;
        nodeDiscarted = aux;
        while(aux->next!=NULL)
        {
            testDistance = getDistance(aux->elem,point);
            if(testDistance < minDistance)
            {
                minDistance = testDistance;
                pointDiscarted = aux->elem;
                nodeDiscarted = aux;
            }
            aux = aux->next;
        }
        newNode(nearestPoints,pointDiscarted);
        removeNode(tempForAngles,nodeDiscarted);
    }
    
    removeGroup(tempForAngles);
    
}

// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
char IntersectRoundedValues(double p0_x, double p0_y, double p1_x, double p1_y, 
    double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}

// Returns 1 if the lines intersect, otherwise 0
int Intersect(Lpoint p0,Lpoint p1,Lpoint p2,Lpoint p3){
    
    double point1,point2;
    int value = 0;
    value =  IntersectRoundedValues(round((p0.x)*100), round((p0.y)*100), round((p1.x)*100), round((p1.y)*100), round((p2.x)*100), round((p2.y)*100), round((p3.x)*100), round((p3.y)*100),&point1,&point2);

    if(value == 0)
        return 0;
    else if(point1 == round((p3.x)*100) && point2 == round((p3.y)*100))
        return 0;
    else if(point1 == round((p1.x)*100) && point2 == round((p1.y)*100))
        return 0;
    else 
        return 1; 
}

// Return point with lowest Y value

void downMostPointPortuguese(Group points, Lpoint *downMostPoint) {
    Node aux;
    *downMostPoint = points->start->elem;

    aux = points->start->next;
    while (aux->next != NULL) {
        if (aux->elem.y <= (*downMostPoint).y)         
        {
            if(aux->elem.y < (*downMostPoint).y)
                *downMostPoint = aux->elem;
            else if(aux->elem.y == (*downMostPoint).y && aux->elem.x < (*downMostPoint).x)
                *downMostPoint = aux->elem;
        }
        aux = aux->next;
    }
}

void RemovePointsSamePosition(Group group) {

    Node aux = NULL,aux2 = NULL;
    Lpoint a;
    int i=0;
    aux = group->start;
    while (aux->next != NULL) {
        i++;
        a = aux->elem;
        aux2 = aux->next;
        while(aux2->next!=NULL) 
        {
            if(a.x == aux2->elem.x && a.y == aux2->elem.y)
                removeNode(&group, aux2);
            aux2=aux2->next;
        }
        aux = aux->next;
    }
    
    aux = group->start;
    while(aux->next!=NULL){
        if(aux->elem.id + 1 != aux->next->elem.id && aux->next->elem.id != 0)
        {
            i=aux->next->elem.id - (aux->elem.id+1);
            aux2 = aux->next;
            while(aux2->next!=NULL){
                aux2->elem.id -= i;
                aux2=aux2->next;
            }
        }
        aux=aux->next;
    }
}

//Return angle formed by points 'a','b' and 'c'; a is the vertex
double AngleBetweenThreePoints(Lpoint a, Lpoint b, Lpoint c)
{
        double result = atan2(round((c.y)*100) - round((a.y)*100), round((c.x)*100) - round((a.x)*100))- atan2(round((b.y)*100) - round((a.y)*100), round((b.x)*100) - round((a.x)*100)) ;
        double val = result*180/3.14;
        if(val<0)
            return val+360;
        else
            return val;
        
}

void SortByY(Group group){
    
    int n = 0;
    Node cur;
    double YValue =0.0;

    cur = group->start;
    if (cur->next == NULL)
        return;
    Node ptr = NULL, tmp = NULL;
    cur = cur->next;
    while (cur->next != NULL) {
        n = 0;
        ptr = cur;
        tmp = cur->prev;
        cur = cur->next;
        YValue = ptr->elem.y;
        while (tmp != NULL && tmp->elem.y > YValue) {
            n++;
            tmp = tmp->prev;
        }
        if (n) {
            ptr->prev->next = ptr->next;
            if (ptr->next != NULL)
                ptr->next->prev = ptr->prev;
            if (tmp == NULL) {
                tmp = group->start;
                ptr->prev = NULL;
                ptr->next = tmp;
                ptr->next->prev = ptr;
                group->start = ptr;
            } else {
                tmp = tmp->next;
                tmp->prev->next = ptr;
                ptr->prev = tmp->prev;
                tmp->prev = ptr;
                ptr->next = tmp;
            }
        }
    }
}

void SortByX(Group group){
    
    int n = 0;
    Node cur;
    double XValue =0.0;

    cur = group->start;
    if (cur->next == NULL)
        return;
    Node ptr = NULL, tmp = NULL;
    cur = cur->next;
    while (cur->next != NULL) {
        n = 0;
        ptr = cur;
        tmp = cur->prev;
        cur = cur->next;
        XValue = ptr->elem.x;
        while (tmp != NULL && tmp->elem.x > XValue) {
            n++;
            tmp = tmp->prev;
        }
        if (n) {
            ptr->prev->next = ptr->next;
            if (ptr->next != NULL)
                ptr->next->prev = ptr->prev;
            if (tmp == NULL) {
                tmp = group->start;
                ptr->prev = NULL;
                ptr->next = tmp;
                ptr->next->prev = ptr;
                group->start = ptr;
            } else {
                tmp = tmp->next;
                tmp->prev->next = ptr;
                ptr->prev = tmp->prev;
                tmp->prev = ptr;
                ptr->next = tmp;
            }
        }
    }
}

void SortByAngle(Group group, Lpoint currentPoint, Lpoint lastPoint){
    
    int n=0;
    Node cur;
    double AngleValue=0.0;

    cur = group->start;
    if (cur->next == NULL)
        return;
    Node ptr = NULL, tmp = NULL;
    cur = cur->next;
    while (cur->next != NULL) {
        n = 0;
        ptr = cur;
        tmp = cur->prev;
        cur = cur->next;
        AngleValue = AngleBetweenThreePoints(currentPoint,lastPoint,ptr->elem);
        while (tmp != NULL && AngleBetweenThreePoints(currentPoint,lastPoint,tmp->elem) > AngleValue) {
            n++;
            tmp = tmp->prev;
        }
        if (n) {
            ptr->prev->next = ptr->next;
            if (ptr->next != NULL)
                ptr->next->prev = ptr->prev;
            if (tmp == NULL) {
                tmp = group->start;
                ptr->prev = NULL;
                ptr->next = tmp;
                ptr->next->prev = ptr;
                group->start = ptr;
            } else {
                tmp = tmp->next;
                tmp->prev->next = ptr;
                ptr->prev = tmp->prev;
                tmp->prev = ptr;
                ptr->next = tmp;
            }
        }
    } 
}


void displayPointsPortuguese(Group points, int neighbours) {
    Node aux = NULL;

    printf("\nPoints of the non-convex hull, PORTUGUESE ALGORITHM:\n");
    printf("\tNeighbours used, k = %d\n",neighbours);
    aux = points->start;
    while (aux->next != NULL) {
        printf("X: %.6lf\tY: %.6lf\t ID: %d\n", aux->elem.x, aux->elem.y, aux->elem.id);
        aux = aux->next;
    }
}

int ConcaveAlgorithm(Group *boundaryGroup, Group group, int neighbours) {

    if (group->size < 3)
        return 1;
    else if(group->size == 3)
    {
        newNode(boundaryGroup, group->start->elem);
        newNode(boundaryGroup, group->start->next->elem);
        newNode(boundaryGroup, group->start->next->next->elem);
        return 0;
    }
    if(*boundaryGroup==NULL)
        return 2;
    if(group==NULL)
        return 3;
    
            
    //Make sure neighbours has a correct value
    if(neighbours < 3 )
        neighbours = 3;
    if(group->size <= neighbours)
        neighbours = group->size-1;

       
    Lpoint currentPoint, firstPoint;
    Node auxNearestPoints=NULL, auxBoundaryGroup=NULL, auxGroup= NULL, aux;
    Group *tempGroup,*nearestPoints;
    int valid = 1, i = 0, allInside = 1;
    
    //Points are saved into another structure so they original Group does not get modified
    tempGroup = (Group*) malloc(sizeof (Group));
    createGroup(tempGroup, 0);
    (*tempGroup)->id = group->id;
    auxNearestPoints=group->start;
    while(auxNearestPoints->next!=NULL)
    {
        newNode(tempGroup, auxNearestPoints->elem);
        auxNearestPoints = auxNearestPoints->next;
    }
    
    RemovePointsSamePosition(*tempGroup);
    
    nearestPoints = (Group*) malloc(sizeof (Group));
    createGroup(nearestPoints, 0);
            
     //Make sure boundaryGroup is empty
    removeGroup(boundaryGroup);
    createGroup(boundaryGroup, 0);

    (*boundaryGroup)->id = group->id;
    
    //Find point with lowest Y value and remove it from the Group
    downMostPointPortuguese((*tempGroup), &firstPoint);
    newNode(boundaryGroup, firstPoint);
    currentPoint = firstPoint;
    removePoint(tempGroup,firstPoint);
    
    i=1;
    do
    {       
        if(i == 6)
            newNode(tempGroup, firstPoint);
        
        FindNearestPoints(nearestPoints, tempGroup,currentPoint, neighbours);
        if((*boundaryGroup)->size == 1)
                SortByAngle(*nearestPoints,currentPoint,(*boundaryGroup)->end->prev->elem);
        else
                SortByAngle(*nearestPoints,currentPoint,(*boundaryGroup)->end->prev->prev->elem);
        auxNearestPoints = (*nearestPoints)->start; 
        valid = 1;
        while((valid == 1) && (auxNearestPoints->next!=NULL))
        {
            auxNearestPoints=auxNearestPoints->next; 
            auxBoundaryGroup = (*boundaryGroup)->start; 
            valid=0;
            while((valid == 0) && (auxBoundaryGroup->next->next!=NULL))
            {
                valid = Intersect((*boundaryGroup)->end->prev->elem,auxNearestPoints->prev->elem,auxBoundaryGroup->elem,auxBoundaryGroup->next->elem);
                auxBoundaryGroup = auxBoundaryGroup->next;          
            }   
        }
        
        if(valid == 1)
            return ConcaveAlgorithm(boundaryGroup, group, neighbours+1);
        currentPoint=auxNearestPoints->prev->elem;
        newNode(boundaryGroup,currentPoint);
        removePoint(tempGroup,currentPoint);
        i++;

    }while(currentPoint.id != firstPoint.id);
    removePoint(boundaryGroup,currentPoint);
    allInside = 1;
    i = ((*tempGroup)->size);
    auxGroup = (*tempGroup)->end->prev;
    while(allInside == 1 && i > 0)
    {
        allInside = PointInPolygon(auxGroup->elem,boundaryGroup);
        auxGroup= auxGroup->prev;
        i--;
    }
    if(allInside==0)
        return ConcaveAlgorithm(boundaryGroup, group, neighbours+1);
    else
    {
        GaussArea(boundaryGroup);
        //displayPointsPortuguese(*boundaryGroup,neighbours);
        return (EXIT_SUCCESS);
    }

}

