/* 
 * File:   Statistically.c
 * Author: esteban
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Statistically.h"

int calculateAreaVolumeStatistically(Group *group, Group *allGroups, unsigned int numGroups, unsigned short UNITSAPPROXIMATION){
    
    if(*group==NULL)
        return 1;
    if(*allGroups==NULL)
        return 2;
    
    int i=0, idGroup=0, j=0, groundPoints = 0;
    unsigned int numPoints = 0;
    double maxX=0,maxY=0,minX=0,minY=0,externalHeight =0, internalHeight = 0;
    Lpoint minXmaxY ,minXminY, maxXminY, maxXmaxY, a;
    Group fourPoints, *allPoints;
    Node aux = NULL, aux2 = NULL;
    
    allPoints = (Group*) malloc(sizeof (Group));
    createGroup(allPoints, 0);
    
    
    idGroup=(*group)->id;
    
    calculateMaxMinCoordinates(allGroups[idGroup], &maxX, &maxY, &minX, &minY);
    createGroup(&fourPoints, idGroup);
    
    minXmaxY.x = minX - UNITSAPPROXIMATION;
    minXmaxY.y = maxY + UNITSAPPROXIMATION;
    newNode(&fourPoints, minXmaxY); 
    
    minXminY.x = minX - UNITSAPPROXIMATION;
    minXminY.y = minY - UNITSAPPROXIMATION;
    newNode(&fourPoints, minXminY); 
    
    maxXminY.x = maxX + UNITSAPPROXIMATION;
    maxXminY.y = minY - UNITSAPPROXIMATION;
    newNode(&fourPoints, maxXminY); 
    
    maxXmaxY.x = maxX + UNITSAPPROXIMATION;
    maxXmaxY.y = maxY + UNITSAPPROXIMATION;
    newNode(&fourPoints, maxXmaxY); 
    
    GaussArea(&fourPoints);
    
    
    i=idGroup;
    if(i>1)
    {
        while( i>1)
        {
            aux=allGroups[i-1]->start;
            while((aux->next)!=NULL)
            {
                if(aux->elem.x >= minX-UNITSAPPROXIMATION && aux->elem.x <=maxX+UNITSAPPROXIMATION)
                    if(aux->elem.y <= maxY+UNITSAPPROXIMATION && aux->elem.y >= minY-UNITSAPPROXIMATION)
                    {
                        aux->elem.planar = allGroups[i-1]->type;
                        newNode(allPoints,aux->elem);
                        numPoints++;              
                    }
                aux=aux->next;
            }
            i--;

        }
    }
    
    j=idGroup;
    if(j<numGroups)
    {      
        while(j+1<numGroups)
        {
            aux=allGroups[j-1]->start;
            while((aux->next)!=NULL)
            {
                if(aux->elem.x >= minX-UNITSAPPROXIMATION && aux->elem.x <=maxX+UNITSAPPROXIMATION)
                    if(aux->elem.y <= maxY+UNITSAPPROXIMATION && aux->elem.y >= minY-UNITSAPPROXIMATION)
                    {
                        aux->elem.planar = allGroups[j-1]->type;
                        newNode(allPoints,aux->elem);
                        numPoints++;
                    }
                aux=aux->next;
            }
            j++;

        }
    }
    
    //Remove repeated points
    aux = (*allPoints)->start;
    while (aux->next != NULL) {
        i++;
        a = aux->elem;
        aux2 = aux->next;
        while(aux2->next!=NULL) 
        {
            if(a.x == aux2->elem.x && a.y == aux2->elem.y)
                numPoints--;
            aux2=aux2->next;
        }
        aux = aux->next;
    }
    
    //Calculate external height
    aux= (*allPoints)->start;
    while(aux->next!=NULL)
    {
       if(aux->elem.planar == GROUND)
       {
           groundPoints++;
           externalHeight+=aux->elem.z;
       }
       aux=aux->next;
    }
    externalHeight = externalHeight / groundPoints; 
         
    //Calculate internal height
    aux= (*group)->start;
    while(aux->next!=NULL)
    {
       internalHeight+=aux->elem.z;
       aux=aux->next;
    }
    internalHeight = internalHeight /((*group)->size);    
    
    (*group)->area = (fourPoints->area * (*group)->size)/numPoints;
    (*group)->volume = ((*group)->area)*(internalHeight-externalHeight);
    
    return (EXIT_SUCCESS);
}


int calculateVolumeStatistically(Group *group, Group *allGroups, unsigned int numGroups, unsigned short UNITSAPPROXIMATION){
    
    if(*group==NULL)
        return 1;
    if(*allGroups==NULL)
        return 2;
    
    int i=0, idGroup=0, j=0, groundPoints = 0;
    unsigned int numPoints = 0;
    double maxX=0,maxY=0,minX=0,minY=0,externalHeight =0, internalHeight = 0;
    Lpoint minXmaxY ,minXminY, maxXminY, maxXmaxY, a;
    Group fourPoints, *allPoints;
    Node aux = NULL, aux2 = NULL;
    
    allPoints = (Group*) malloc(sizeof (Group));
    createGroup(allPoints, 0);
    
    
    idGroup=(*group)->id;
    
    calculateMaxMinCoordinates(allGroups[idGroup], &maxX, &maxY, &minX, &minY);
    createGroup(&fourPoints, idGroup);
    
    minXmaxY.x = minX - UNITSAPPROXIMATION;
    minXmaxY.y = maxY + UNITSAPPROXIMATION;
    newNode(&fourPoints, minXmaxY); 
    
    minXminY.x = minX - UNITSAPPROXIMATION;
    minXminY.y = minY - UNITSAPPROXIMATION;
    newNode(&fourPoints, minXminY); 
    
    maxXminY.x = maxX + UNITSAPPROXIMATION;
    maxXminY.y = minY - UNITSAPPROXIMATION;
    newNode(&fourPoints, maxXminY); 
    
    maxXmaxY.x = maxX + UNITSAPPROXIMATION;
    maxXmaxY.y = maxY + UNITSAPPROXIMATION;
    newNode(&fourPoints, maxXmaxY);
    
    
    i=idGroup;
    if(i>1)
    {
        while( i>1)
        {
            aux=allGroups[i-1]->start;
            while((aux->next)!=NULL)
            {
                if(aux->elem.x >= minX-UNITSAPPROXIMATION && aux->elem.x <=maxX+UNITSAPPROXIMATION)
                    if(aux->elem.y <= maxY+UNITSAPPROXIMATION && aux->elem.y >= minY-UNITSAPPROXIMATION)
                    {
                        aux->elem.planar = allGroups[i-1]->type;
                        newNode(allPoints,aux->elem);
                        numPoints++;              
                    }
                aux=aux->next;
            }
            i--;

        }
    }
    
    j=idGroup;
    if(j<numGroups)
    {      
        while(j+1<numGroups)
        {
            aux=allGroups[j-1]->start;
            while((aux->next)!=NULL)
            {
                if(aux->elem.x >= minX-UNITSAPPROXIMATION && aux->elem.x <=maxX+UNITSAPPROXIMATION)
                    if(aux->elem.y <= maxY+UNITSAPPROXIMATION && aux->elem.y >= minY-UNITSAPPROXIMATION)
                    {
                        aux->elem.planar = allGroups[j-1]->type;
                        newNode(allPoints,aux->elem);
                        numPoints++;
                    }
                aux=aux->next;
            }
            j++;

        }
    }
    
    //Remove repeated points
    aux = (*allPoints)->start;
    while (aux->next != NULL) {
        i++;
        a = aux->elem;
        aux2 = aux->next;
        while(aux2->next!=NULL) 
        {
            if(a.x == aux2->elem.x && a.y == aux2->elem.y)
                numPoints--;
            aux2=aux2->next;
        }
        aux = aux->next;
    }
    
    //Calculate external height
    aux= (*allPoints)->start;
    while(aux->next!=NULL)
    {
       if(aux->elem.planar == GROUND)
       {
           groundPoints++;
           externalHeight+=aux->elem.z;
       }
       aux=aux->next;
    }
    externalHeight = externalHeight / groundPoints; 
         
    //Calculate internal height
    aux= (*group)->start;
    while(aux->next!=NULL)
    {
       internalHeight+=aux->elem.z;
       aux=aux->next;
    }
    internalHeight = internalHeight /((*group)->size);    
    
    (*group)->volume = ((*group)->area)*(internalHeight-externalHeight);
    
    return (EXIT_SUCCESS);
}