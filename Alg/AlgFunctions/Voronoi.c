/* 
 * File:   Voronoi.c
 * Author: esteban
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "Voronoi.h"

int SetClosestPointsVoronoi(int idGroup, Group *closestPoints, Group *allGroups, unsigned int numGroups, unsigned short UNITSAPPROXIMATION){
    
    if(*closestPoints==NULL)
        return 1;
    if(*allGroups==NULL)
        return 2;
    
    int i=0, j=0;
    unsigned int numPoints = 1;
    double maxX=0,maxY=0,minX=0,minY=0;
    Lpoint minXmaxY ,minXminY, maxXminY, maxXmaxY;
    Group fourPoints;
    Node aux = NULL,aux2=NULL;
    
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
        
    removeGroup(closestPoints);
    createGroup(closestPoints, 0);

    (*closestPoints)->id = idGroup;
    
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
                        aux->elem.id=numPoints;
                        newNode(closestPoints, aux->elem); 
                        (*closestPoints)->end->prev->elem.planar = allGroups[i-1]->type;
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
                        aux->elem.id=numPoints;
                        newNode(closestPoints, aux->elem);
                        (*closestPoints)->end->prev->elem.planar = allGroups[i-1]->type;
                        numPoints++;
                    }
                aux=aux->next;
            }
            j++;

        }
    }
   

    aux=allGroups[idGroup]->start;
    while(aux->next!=NULL)
    {
        aux2=(*closestPoints)->start;
        while(aux2->next!=NULL)
        {
            if(aux2->elem.id == aux->elem.id)
            {
                removeNode(closestPoints,aux2);
            }
            aux2=aux2->next;
        }
        aux=aux->next;
    }

    
    return (EXIT_SUCCESS);
}

int VoronoiAlgorithm(Group *voronoiBoundaryGroup, Group buildingGroup, Group *allGroups, int numGroups, int k){
    
    unsigned short UNITSAPPROXIMATION = 1;
    Group *buildingBoundaryGroup, *externalPointsGroup, *externalPointsBoundaryGroup, *closestPointsGroup, *closestPointsBoundaryGroup;
    Node aux, aux2;
    Lpoint p;
    int id=0, *idStart, *idEnd;
    char path[50], pathEle[50], pathNode[50];
    double ExternalHeight = 0, InternalHeight = 0; 
    
    if(buildingGroup->id == 34)
        return 1;
    
    removeGroup(voronoiBoundaryGroup);
    createGroup(voronoiBoundaryGroup, 0);
    
    buildingBoundaryGroup = (Group*) malloc(sizeof (Group));
    createGroup(buildingBoundaryGroup, 0);
    closestPointsGroup = (Group*) malloc(sizeof (Group));
    createGroup(closestPointsGroup, 0);
    closestPointsBoundaryGroup = (Group*) malloc(sizeof (Group));
    createGroup(closestPointsBoundaryGroup, 0);
    externalPointsGroup = (Group*) malloc(sizeof (Group));
    createGroup(externalPointsGroup, 0);
    externalPointsBoundaryGroup = (Group*) malloc(sizeof (Group));
    createGroup(externalPointsBoundaryGroup, 0);
    idStart = (int*)malloc(sizeof(int));
    idEnd = (int*)malloc(sizeof(int));
    
    RemovePointsSamePosition(buildingGroup);
    
    //Calculate min concave hull 
    if(ConcaveAlgorithm(buildingBoundaryGroup, buildingGroup,k) == EXIT_SUCCESS)
    {      
	mkdir("data/buildingsBoundaries", 0777);
        sprintf(path,"data/buildingsBoundaries/%d",buildingGroup->id);
        mkdir(path, 0777);
        
	system("gcc -o Triangle/triangle Triangle/triangle.c -lm");
	
        //Write points in triangle format
        sprintf(path,"data/buildingsBoundaries/%d/%dMin.poly",buildingGroup->id, buildingGroup->id);
        if( WriteGroupAndBoundary(buildingGroup, *buildingBoundaryGroup,path)!= EXIT_SUCCESS)
                printf("Error writing on file %s",path);
        
        //Search closest points to building points
         SetClosestPointsVoronoi(buildingGroup->id, closestPointsGroup, allGroups, numGroups, UNITSAPPROXIMATION);
         RemovePointsSamePosition(*closestPointsGroup);
                      
         JarvisMarch(closestPointsBoundaryGroup, *closestPointsGroup);
                
           aux=(*closestPointsBoundaryGroup)->start;
           while(aux->next!=NULL)
           {
               aux2=(*closestPointsGroup)->start;
               while(aux2->next!=NULL)
               {
                   if(aux2->elem.id == aux->elem.id)
                   {
                       removeNode(closestPointsGroup,aux2);
                   }
                   aux2=aux2->next;
               }
               aux=aux->next;
            }

         //Write closest points, external and internal boundary
         sprintf(path,"data/buildingsBoundaries/%d/ExIn%d.poly",buildingGroup->id,buildingGroup->id);
         if( WriteGroupAndDoubleBoundary(*closestPointsGroup, *closestPointsBoundaryGroup, *buildingBoundaryGroup,path, idStart, idEnd)!= EXIT_SUCCESS)
                printf("Error writing on file %s",path);
         
         sprintf(path,"./Triangle/triangle -pQ data/buildingsBoundaries/%d/ExIn%d.poly",buildingGroup->id, buildingGroup->id);
         system(path);
         
         sprintf(pathEle,"data/buildingsBoundaries/%d/ExIn%d.1.ele",buildingGroup->id,buildingGroup->id);
         sprintf(pathNode,"data/buildingsBoundaries/%d/ExIn%d.1.node",buildingGroup->id,buildingGroup->id);
         ExternalPointsBoundary(pathEle, pathNode, *idStart, *idEnd, externalPointsGroup);
         
         aux= (*buildingBoundaryGroup)->start;
         id = (*externalPointsGroup)->end->prev->elem.id +1; 
         while(aux->next!=NULL)
         {
             p.id=id;
             p.x=aux->elem.x;
             p.y=aux->elem.y;
             p.z=aux->elem.z;
             newNode(externalPointsGroup,p);
             id++;
             aux=aux->next;
         }
         
         if(ConcaveAlgorithm(externalPointsBoundaryGroup, *externalPointsGroup,k) == EXIT_SUCCESS)
         {
             //Calculate external height
            aux= (*externalPointsBoundaryGroup)->start;
            while(aux->next!=NULL)
            {
               if(aux->elem.planar == GROUND)
                   ExternalHeight+=aux->elem.z;

               aux=aux->next;
            }
            ExternalHeight = ExternalHeight /((*voronoiBoundaryGroup)->size);    

            sprintf(path,"data/buildingsBoundaries/%d/%dMax.poly",buildingGroup->id, buildingGroup->id);
            if( WriteGroupAndBoundary(*externalPointsGroup, *externalPointsBoundaryGroup,path)!= EXIT_SUCCESS)
                printf("Error writing on file %s","P.poly");
            else
            {
                sprintf(path,"data/buildingsBoundaries/%d/Vor%d.poly",buildingGroup->id,buildingGroup->id);
                if( WriteDoubleBoundary(*externalPointsBoundaryGroup, *buildingBoundaryGroup,path)!= EXIT_SUCCESS)
                       printf("Error writing on file %s",path);
                
                sprintf(path,"./Triangle/triangle -q20vQQ data/buildingsBoundaries/%d/Vor%d.poly",buildingGroup->id, buildingGroup->id);
                system(path);
         
                sprintf(pathEle,"data/buildingsBoundaries/%d/Vor%d.1.v.edge",buildingGroup->id,buildingGroup->id);
                sprintf(pathNode,"data/buildingsBoundaries/%d/Vor%d.1.v.node",buildingGroup->id, buildingGroup->id);
                if(ReadVoronoi(pathNode, pathEle, voronoiBoundaryGroup)==1)
                {
                    sprintf(path,"./Triangle/triangle -q25vQQ data/buildingsBoundaries/%d/Vor%d.poly",buildingGroup->id, buildingGroup->id);
                    system(path);

                    sprintf(pathEle,"data/buildingsBoundaries/%d/Vor%d.1.v.edge",buildingGroup->id,buildingGroup->id);
                    sprintf(pathNode,"data/buildingsBoundaries/%d/Vor%d.1.v.node",buildingGroup->id, buildingGroup->id);
                    createGroup(voronoiBoundaryGroup, 0);
                    if(ReadVoronoi(pathNode, pathEle, voronoiBoundaryGroup)==1)
                    {
                        sprintf(path,"./Triangle/triangle -DvQQ data/buildingsBoundaries/%d/Vor%d.poly",buildingGroup->id, buildingGroup->id);
                        system(path);

                        sprintf(pathEle,"data/buildingsBoundaries/%d/Vor%d.1.v.edge",buildingGroup->id,buildingGroup->id);
                        sprintf(pathNode,"data/buildingsBoundaries/%d/Vor%d.1.v.node",buildingGroup->id, buildingGroup->id);
                        createGroup(voronoiBoundaryGroup, 0);
                        ReadVoronoi(pathNode, pathEle, voronoiBoundaryGroup);
                        
                    }
                }
                
                if((*voronoiBoundaryGroup)->size > 0)
                {
                    GaussArea(voronoiBoundaryGroup);
                    
                    //Volume

                    //Calculate internal height
                    aux= buildingGroup->start;
                    while(aux->next!=NULL)
                    {
                       InternalHeight+=aux->elem.z;
                       aux=aux->next;
                    }
                    InternalHeight = InternalHeight /(buildingGroup->size);

                   (*voronoiBoundaryGroup)->volume = ((*voronoiBoundaryGroup)->area)*(InternalHeight-ExternalHeight);                       
                
                }        
            }
         }
        else
                printf("Error,Portuguese Algorithm , group id: %d\n\n",buildingGroup->id);                
    }
    else
        printf("Error,Portuguese Algorithm , group id: %d\n\n",buildingGroup->id);
    
    
    return (EXIT_SUCCESS);
}
