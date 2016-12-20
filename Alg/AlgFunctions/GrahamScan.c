/* 
 * File:   GrahamScan.c
 * Author: esteban
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GrahamScan.h"

/* 
 * Return:
 *      -1 for a counterclockwise turn
 *      +1 for a clockwise turn
 *      0 if they are collinear
 */
int ccwGraham(Lpoint a, Lpoint b, Lpoint c) {
    double area = (round((b.x)*100) - round((a.x)*100)) * (round((c.y)*100) - round((a.y)*100)) - (round((b.y)*100) - round((a.y)*100)) * (round((c.x)*100) - round((a.x)*100));
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}

// Return point with lowest Y value

void downMostPointGraham(Group points, Lpoint *downMostPoint) {
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

// Return polar angle formed by 'a' and 'b'

double polarAngle(Lpoint a, Lpoint b) {
    double x = round((a.x)*100) - round((b.x)*100);
    double y = round((a.y)*100) - round((b.y)*100);
    if (a.id == b.id)
        return 0;
    if (x > 0)
        return atan(y / x)*180 / 3.14;
    if (x == 0)
        return 90;
    else
        return 180 + atan(y / x)*180 / 3.14;
}

//Remove points with same angle respect to point with lowest Y value in the group

void RemovePointsSameAngle(Group group) {

    Node aux = NULL;
    Lpoint leastY, a, b;
    double distance1, distance2;

    downMostPointGraham(group, &leastY);
    a = leastY;
    aux = group->start->next;
    while (aux->next != NULL) {
        if (polarAngle(aux->elem, leastY) == polarAngle(aux->prev->elem, leastY)) {
            b = aux->elem;
            distance1 = sqrt((round((a.x)*100) - round((b.x)*100)) * (round((a.x)*100) - round((b.x)*100)) + (round((a.y)*100) - round((b.y)*100)) *(round((a.y)*100) - round((b.y)*100)));

            b = aux->prev->elem;
            distance2 = sqrt((round((a.x)*100) - round((b.x)*100)) * (round((a.x)*100) - round((b.x)*100)) + (round((a.y)*100) - round((b.y)*100)) *(round((a.y)*100) - round((b.y)*100)));

            if ((distance1 == distance2) || (distance1 > distance2))
                removeNode(&group, aux->prev);
            else
                removeNode(&group, aux);
        } else
            aux = aux->next;
    }
}


//Sort group by polar angle starting with point with lowest Y

void InsertionSort(Group group) {

    int n = 0;
    Node cur;
    Lpoint leastY;
    double polarAngleValue = 0.0;

    downMostPointGraham(group, &leastY);
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
        polarAngleValue = polarAngle(ptr->elem, leastY);
        while (tmp != NULL && polarAngle(tmp->elem, leastY) > polarAngleValue) {
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

void displayPointsGraham(Group group) {

    Node aux = NULL;

    printf("\nPoints of the convex hull, GRAHAM SCAN:\n");
    aux = group->start;
    while (aux->next != NULL) {
        printf("X: %.6lf\tY: %.6lf\t ID: %d\n", aux->elem.x, aux->elem.y, aux->elem.id);
        aux = aux->next;
    }
}

int GrahamScan(Group *boundaryGroup, Group group) {


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

    Lpoint top;
    Node aux = NULL;
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

    //Points must be sorted before starting to form convex hull
    InsertionSort(*tempGroup);

    RemovePointsSameAngle(*tempGroup);

    //First 3 poinst are added to boundary group
    newNode(boundaryGroup, (*tempGroup)->start->elem);
    newNode(boundaryGroup, (*tempGroup)->start->next->elem);
    newNode(boundaryGroup, (*tempGroup)->start->next->next->elem);


    //Graham scan
    aux = (*tempGroup)->start->next->next->next;
    while (aux->next != NULL) {
        top = (*boundaryGroup)->end->prev->elem;
        removeNode(boundaryGroup, (*boundaryGroup)->end->prev);
        //Check if next point is a good option for adding it to the hull
        while (ccwGraham((*boundaryGroup)->end->prev->elem, top, aux->elem) != -1) {
            top = (*boundaryGroup)->end->prev->elem;
            removeNode(boundaryGroup, (*boundaryGroup)->end->prev);
        }
        newNode(boundaryGroup, top);
        newNode(boundaryGroup, aux->elem);
        aux = aux->next;
    }

    //Calculate area and save it in the variable "area" 
    GaussArea(boundaryGroup);

    //displayPointsGraham(*boundaryGroup);

    free(tempGroup);

    return (EXIT_SUCCESS);
}


