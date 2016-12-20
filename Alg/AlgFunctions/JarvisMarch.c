/* 
 * File:   JarvisMarch.c
 * Author: esteban
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "JarvisMarch.h"

/* 
 * Return:
 *      < 0 for a counterclockwise turn
 *      > 0 for a clockwise turn
 *      0 if they are collinear
 */
int ccwJarvis(Lpoint p, Lpoint q, Lpoint r) {
    int x = round((q.x) * 100) - round((p.x) * 100);
    int y = round((q.y) * 100) - round((p.y) * 100);
    return (x * (round((r.y) * 100) - round((p.y) * 100)))-(y * (round((r.x) * 100) - round((p.x) * 100)));

}

//Return 1 if p1 and p2 have the same id, 0 if they do not

int equal(Lpoint p1, Lpoint p2) {

    if (p1.id == p2.id)
        return 1;
    else
        return 0;

}

// Return point with lowest X value

void leftMostPointJarvis(Group points, Lpoint *leftmostPoint) {
    Node aux;
    *leftmostPoint = points->start->elem;

    aux = points->start->next;
    while (aux->next != NULL) {
        if (aux->elem.x <= (*leftmostPoint).x)
        {
            if(aux->elem.x < (*leftmostPoint).x)
                *leftmostPoint = aux->elem;
            else if(aux->elem.x == (*leftmostPoint).x && aux->elem.y < (*leftmostPoint).y)
                *leftmostPoint = aux->elem;
        }
        
        aux = aux->next;
    }
}

//Return distance between points 'a' and 'b'

double getDistanceJarvis(Lpoint a, Lpoint b) {
    double distance;
    distance = sqrt((round((a.x)*100) - round((b.x)*100)) * (round((a.x)*100) - round((b.x)*100)) + (round((a.y)*100) - round((b.y)*100)) *(round((a.y)*100) - round((b.y)*100)));
    return distance;
}

//Remove points with same angle respect to point with lowest X value in the group

void RemovePointsSamePositionJarvis(Group *group) {

    Node aux = NULL;
    Lpoint leastX;

    leftMostPointJarvis((*group), &leastX);
    aux = (*group)->start;
    while (aux->next != NULL) {
        if(aux->elem.x == leastX.x && aux->elem.y == leastX.y)
            removeNode(group,aux);
        else
            aux = aux->next;
    }
}

void displayPointsJarvis(Group points) {
    Node aux = NULL;

    printf("\nPoints of the convex hull, JARVIS MARCH:\n");
    aux = points->start;
    while (aux->next != NULL) {
        printf("X: %.6lf\tY: %.6lf\t ID: %d\n", aux->elem.x, aux->elem.y, aux->elem.id);
        aux = aux->next;
    }
}

int JarvisMarch(Group *boundaryGroup, Group group) {

    if (group->size < 3)
        return 1;
    else if (group->size == 3) {
        newNode(boundaryGroup, group->start->elem);
        newNode(boundaryGroup, group->start->next->elem);
        newNode(boundaryGroup, group->start->next->next->elem);
        return 0;
    }
    if (*boundaryGroup == NULL)
        return 2;
    if (group == NULL)
        return 3;

    Lpoint currentPoint, boundaryPoint;
    Node auxBoundaryGroup, auxGroup,aux;
    int validPoint = 0;
    Group *tempGroup;
    
    //Make sure boundaryGroup is empty
    removeGroup(boundaryGroup);
    createGroup(boundaryGroup, 0);

    (*boundaryGroup)->id = group->id;
    
    //Points are saved into another structure so the original Group does not get modified
    tempGroup = (Group*) malloc(sizeof (Group));
    createGroup(tempGroup, 0);
    aux = group->start;
    while (aux->next != NULL) {
        newNode(tempGroup, aux->elem);
        aux = aux->next;
    }

    //RemovePointsSamePositionJarvis(tempGroup);
    
    //Find point with lowest x value
    leftMostPointJarvis((*tempGroup), &boundaryPoint);
    auxBoundaryGroup = (*boundaryGroup)->start;
    auxGroup = (*tempGroup)->start->next;

    //Jarvis March
    do {
        newNode(boundaryGroup, boundaryPoint);
        currentPoint = (*tempGroup)->start->elem;

        auxGroup = (*tempGroup)->start->next;
        //Search next point of the hull with lowest angle
        while (auxGroup->next != NULL) {
            validPoint = ccwJarvis(auxBoundaryGroup->elem, currentPoint, auxGroup->elem);
            if (equal(currentPoint, boundaryPoint) || (validPoint < 0) || (validPoint == 0 && getDistanceJarvis(auxBoundaryGroup->elem, currentPoint) < getDistanceJarvis(auxBoundaryGroup->elem, auxGroup->elem))) {
                currentPoint = auxGroup->elem;
            }
            auxGroup = auxGroup->next;
        }
        auxBoundaryGroup = auxBoundaryGroup->next;
        boundaryPoint = currentPoint;
    } while (!equal(currentPoint, (*boundaryGroup)->start->elem)); //Finish when last point added is the same as first one

    //Calculate area and save it in the variable "area" 
    GaussArea(boundaryGroup);
    
    

    return (EXIT_SUCCESS);
}