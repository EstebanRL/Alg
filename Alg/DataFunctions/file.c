#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>
#include "group.h"
#include "file.h"


int WriteGroupOnTriangleFormat(Group minGroup, Group maxGroup, Group voronoiGroup, char *path){
    
    Node aux;
    int i=1,j=1,k=0,l=1;
    FILE *file = fopen(path, "w");
    
    if(file == NULL)
        return 2;
        
    //Nodes  
    fprintf(file,"%d 2 0 0\n",maxGroup->size + minGroup->size + voronoiGroup->size);
    
    aux=maxGroup->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }
        
    j = i;
    aux=minGroup->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }

    k = i;
    aux=voronoiGroup->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }
        
    
    //Edges
    fprintf(file,"%d 0\n",maxGroup->size + minGroup->size + voronoiGroup->size);
    
    i=1;
    aux=maxGroup->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i, l, l+1);
      aux=aux->next;
      i++;l++;
    }
    fprintf(file,"%d %d %d\n",i, l, 1);    
    i++;
    
    aux=minGroup->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i,j,j+1);
      aux=aux->next;
      i++;j++;
    }
    fprintf(file,"%d %d %d\n",i, j, maxGroup->size + 1);
    i++;
    
    if(voronoiGroup->start->next!=NULL)
    {
        aux=voronoiGroup->start;
        while((aux->next->next)!=NULL)
        {
          fprintf(file,"%d %d %d\n",i,k,k+1);
          aux=aux->next;
          i++;k++;
        }
        fprintf(file,"%d %d %d\n",i, k, maxGroup->size + minGroup->size + 1);
    }
    
    //No holes
    fprintf(file,"0\n");
    fclose(file);

    return EXIT_SUCCESS;
}

int ExternalPointsBoundary(char *pathEle, char *pathNode, int idStart, int idEnd, Group *boundaryGroup){
    
    Lpoint point;
    FILE *file;
    int triangles = 0, nodes = 0, numPoints, tempID, tempEdge1, tempEdge2, tempEdge3, edge1Repeated, edge2Repeated, edge3Repeated;
    int *idPoints, i=0,j=0,k=0,l=0;
    double tempX,tempY,tempZ;
    int type;
    
    file = fopen(pathEle, "r");
    
    if(file == NULL)
        return 1;
        
   
    
    //ID of boundary points
   fscanf(file,"%d %*d %*d\n",&triangles);
           
   idPoints = (int*)malloc(triangles*sizeof(int));
   
   //Add valid not-repeated points
   for(i=0;i<triangles;i++)
   {
        fscanf(file,"%d%d%d%d\n",&tempID,&tempEdge1,&tempEdge2,&tempEdge3);
       
        edge1Repeated=0;
        edge2Repeated=0;
        edge3Repeated=0;
        
        if(idStart <= tempEdge1 && idEnd >= tempEdge1)
        {
            for(l = 0; l < k;l++)
            {
                if(idPoints[l]==tempEdge2)
                {
                    edge2Repeated = 1;
                }
                if(idPoints[l]==tempEdge3)
                {
                    edge3Repeated = 1;
                }
            }
            if(edge2Repeated!=1)
            {
                if(!(idStart <= tempEdge2 && idEnd >= tempEdge2))
                {
                    idPoints[k]=tempEdge2;
                    k++;
                }
            }
            if(edge3Repeated!=1)
            {
                if(!(idStart <= tempEdge3 && idEnd >= tempEdge3))
                {
                    idPoints[k]=tempEdge3;
                    k++;
                }
            }
        }
        else if(idStart <= tempEdge2 && idEnd >= tempEdge1)
        {
            for(l = 0; l < k;l++)
            {
                if(idPoints[l]==tempEdge1)
                {
                    edge1Repeated = 1;
                }
                if(idPoints[l]==tempEdge3)
                {
                    edge3Repeated = 1;
                }
            }
            if(edge1Repeated!=1)
            {
                if(!(idStart <= tempEdge1 && idEnd >= tempEdge1))
                {
                    idPoints[k]=tempEdge1;
                    k++;
                }
            }
            if(edge3Repeated!=1)
            {
                if(!(idStart <= tempEdge3 && idEnd >= tempEdge3))
                {
                    idPoints[k]=tempEdge3;
                    k++;
                }
            }
        }
        else if(idStart <= tempEdge3 && idEnd >= tempEdge1)
        {
            for(l = 0; l < k;l++)
            {
                if(idPoints[l]==tempEdge1)
                {
                    edge1Repeated = 1;
                }
                if(idPoints[l]==tempEdge2)
                {
                    edge2Repeated = 1;
                }
            }
            if(edge1Repeated!=1)
            {
                if(!(idStart <= tempEdge1 && idEnd >= tempEdge1))
                {
                    idPoints[k]=tempEdge1;
                    k++;
                }
            }
            if(edge2Repeated!=1)
            {
                if(!(idStart <= tempEdge2 && idEnd >= tempEdge2))
                {
                    idPoints[k]=tempEdge2;
                    k++;
                }
            }
        } 
   }  
   numPoints = k;
   k=0;
   fclose(file);
      
   
   
   //Coordinates of boundary points
   file=fopen(pathNode,"r");
    
   
   
   fscanf(file,"%d %*d %*d %*d\n",&nodes);
   

   for(i=0;i<nodes;i++)
   {
       fscanf(file,"%d%lf%lf%lf%d%*d\n",&tempID,&tempX,&tempY,&tempZ,&type);
       
       for(j = 0 ; j< numPoints-1; j++)
       {
           if(idPoints[j] == tempID)
           {
              point.x = tempX;
              point.y = tempY;
              point.z = tempZ;
              point.planar = type;
              point.id = k;
              newNode(boundaryGroup, point);
              k++;
              break;
           }

       }
   }  

   fclose(file);
        
   return EXIT_SUCCESS;
    
}


int WriteGroupAndBoundary(Group group, Group boundaryPoints, char *path){
    
    Node aux;
    int i=1,j=1,k=0;
    FILE *file = fopen(path, "w");
    
    if(group == NULL)
        return 1;
    if(file == NULL)
        return 2;
        
    //Nodes  
    fprintf(file,"%d 2 0 0\n",group->size + boundaryPoints->size);
    aux=group->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }

    j = i;
    k = i;
    
    aux=boundaryPoints->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }

    
    //Edges
    fprintf(file,"%d 0\n",boundaryPoints->size);
    i=1;
    aux=boundaryPoints->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i, j, j+1);
      aux=aux->next;
      i++;j++;
    }
    fprintf(file,"%d %d %d\n",i, j, k);    
    i++;

    
    //No holes
    fprintf(file,"0\n");
    fclose(file);

    return EXIT_SUCCESS;
}

int WriteGroupAndDoubleBoundary(Group group, Group externalBoundaryPoints, Group internalBoundaryPoints,  char *path, int *idStart, int *idEnd ){
    
    Node aux;
    int i=1,j=1,k=0;
    FILE *file = fopen(path, "w");
    double maxX,minX,maxY,minY;
    
    if(group == NULL)
        return 1;
    if(file == NULL)
        return 2;
        
    //Nodes  
    fprintf(file,"%d 2 2 0\n",group->size + externalBoundaryPoints->size + internalBoundaryPoints->size);
    aux=group->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf %lf %d\n",i, aux->elem.x, aux->elem.y,aux->elem.z, aux->elem.planar);
      aux=aux->next;
      i++;
    }
    
    j = i;
    aux=externalBoundaryPoints->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf %lf %d\n",i, aux->elem.x, aux->elem.y,aux->elem.z, aux->elem.planar);
      aux=aux->next;
      i++;
    }
    
    k = i;
    aux=internalBoundaryPoints->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf %lf 6\n",i, aux->elem.x, aux->elem.y,aux->elem.z);
      aux=aux->next;
      i++;
    }
    
    //Edges
    fprintf(file,"%d 0\n",externalBoundaryPoints->size + internalBoundaryPoints->size);
    i=1;
    aux=externalBoundaryPoints->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i, j, j+1);
      aux=aux->next;
      i++;j++;
    }
    fprintf(file,"%d %d %d\n",i, j, group->size+1);    
    i++;

    *idStart = k;
    aux=internalBoundaryPoints->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i, k, k+1);
      aux=aux->next;
      i++;k++;
    }
    fprintf(file,"%d %d %d\n",i, k, group->size + externalBoundaryPoints->size + 1);    
    i++;
    *idEnd = k;
   
    
    //No holes
    fprintf(file,"1\n");
    calculateMaxMinCoordinates(internalBoundaryPoints, &maxX, &maxY, &minX, &minY);
    fprintf(file,"1 %lf %lf",(maxX + minX)/2, (maxY + minY)/2);
    fclose(file);

    return EXIT_SUCCESS;
}

int WriteDoubleBoundary(Group externalBoundaryPoints, Group internalBoundaryPoints,  char *path){
    
    Node aux;
    int i=1,j=1,k=0;
    FILE *file = fopen(path, "w");
    
    if(file == NULL)
        return 2;
        
    //Nodes  
    fprintf(file,"%d 2 0 0\n",externalBoundaryPoints->size + internalBoundaryPoints->size);
    aux=externalBoundaryPoints->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }
    
    k = i;
    aux=internalBoundaryPoints->start;
    while((aux->next)!=NULL)
    {
      fprintf(file,"%d %lf %lf\n",i, aux->elem.x, aux->elem.y);
      aux=aux->next;
      i++;
    }
    
    //Edges
    fprintf(file,"%d 0\n",externalBoundaryPoints->size + internalBoundaryPoints->size);
    i=1;
    aux=externalBoundaryPoints->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i, j, j+1);
      aux=aux->next;
      i++;j++;
    }
    fprintf(file,"%d %d %d\n",i, j, 1);    
    i++;

    aux=internalBoundaryPoints->start;
    while((aux->next->next)!=NULL)
    {
      fprintf(file,"%d %d %d\n",i, k, k+1);
      aux=aux->next;
      i++;k++;
    }
    fprintf(file,"%d %d %d\n",i, k, externalBoundaryPoints->size + 1);    
    i++;
    
    //No holes
    fprintf(file,"0\n");
    fclose(file);

    return EXIT_SUCCESS;
}

int ccwVoronoi(Lpoint a, Lpoint b, Lpoint c) {
    double area = (round((b.x)*10000) - round((a.x)*10000)) * (round((c.y)*10000) - round((a.y)*10000)) - (round((b.y)*10000) - round((a.y)*10000)) * (round((c.x)*10000) - round((a.x)*10000));
    if (area > 0)
        return -1;
    else if (area < 0)
        return 1;
    return 0;
}

int ReadVoronoi(char *pathNode, char* pathEdge, Group *boundaryPoints){
    
    Node aux, auxBoundaryPoints, aux2;
    FILE *file;
    Lpoint *nodes, p;
    Group *validPoints;
    int *edges1, *edges2, i, j, nodesNumber=0, edgesNumber =0, idRemove =0;
    
    //Read nodes file
    file = fopen(pathNode, "r");
    if(file == NULL)
        return 1;
    fscanf(file,"%d %*d %*d %*d\n",&nodesNumber);
    nodes = (Lpoint*)malloc((nodesNumber+1)*sizeof(Lpoint));
    for(i=1;i<nodesNumber+1;i++)
        fscanf(file, "%u %lf %lf\n",&(nodes[i].id),&(nodes[i].x),&(nodes[i].y));
    fclose(file);
    
    
    //Read edges file
    file = fopen(pathEdge, "r");
    if(file == NULL)
        return 1;
    fscanf(file,"%d %*d\n",&edgesNumber);
    edges1 = (int*)malloc((edgesNumber+1)*sizeof(int));
    edges2 = (int*)malloc((edgesNumber+1)*sizeof(int));
    for(i=1;i<edgesNumber+1;i++)
    {
        fscanf(file, "%*u %d %d",&(edges1[i]),&(edges2[i]));
        if(edges2[i] == -1)
            fscanf(file,"%*f %*f\n");
        else
            fscanf(file,"\n");
    }
    fclose(file);
    
    
    //Id of first point of the boundary
    i=1;
    while(edges2[i] != -1)
    {
        i++;
    }
    i=edges1[i];
    
    p.id = i;
    p.x = nodes[i].x;
    p.y = nodes[i].y;
    
    auxBoundaryPoints = (*boundaryPoints)->start;
    
    //Points with a common edge with boundary Point
    validPoints = (Group*) malloc(sizeof (Group));
    i=0;
    do{
        aux = (*boundaryPoints)->start;
        while(aux->next!=NULL)
        {
            if(aux->elem.id == p.id)
            {
                idRemove = aux->next->elem.id; 
                aux2 = (*boundaryPoints)->end->prev;
                while(aux2->elem.id != aux->elem.id)
                {
                    removeNode(boundaryPoints,aux2);
                    aux2 = aux2->prev;
                }
                removeNode(boundaryPoints,aux2);
                        
            }
            aux = aux -> next;
        }
                
        newNode(boundaryPoints,p);
        i++;
        createGroup(validPoints, 0); 
        for(j=1;j<edgesNumber;j++)
        {
            if(edges1[j] == auxBoundaryPoints->elem.id  && edges2[j]!=-1)
            {
                p.id = edges2[j];
                p.x = nodes[edges2[j]].x;
                p.y = nodes[edges2[j]].y;
                newNode(validPoints,p);
            }
            else if(edges2[j] == auxBoundaryPoints->elem.id)
            {
                p.id = edges1[j];
                p.x = nodes[edges1[j]].x;
                p.y = nodes[edges1[j]].y;
                newNode(validPoints,p);
            }
        }
            
        if((*validPoints)->size > 1)
        {
            if((*boundaryPoints)->size > 1)
            {
                aux = (*validPoints)->start;
                while(aux->next!=NULL)
                {
                    if(aux->elem.id == (*boundaryPoints)->end->prev->prev->elem.id || aux->elem.id == idRemove)
                        removeNode(validPoints,aux);
                    aux = aux->next;
                }
            }
            idRemove = 0;
            
            aux = (*validPoints)->start;
            p = (*validPoints)->start->elem;
            while(aux->next!=NULL)
            {
                if(ccwVoronoi(auxBoundaryPoints->elem, p, aux->elem) == -1)
                        p = aux->elem;
                aux = aux->next;
            }
            auxBoundaryPoints = auxBoundaryPoints->next;
            
        }
        else if((*validPoints)->size == 1)
        {
            p = (*validPoints)->start->elem;
            auxBoundaryPoints = auxBoundaryPoints->next;
        }
        if(i==10000)
            return 1;
    }while(p.id != (*boundaryPoints)->start->elem.id);
 
    return EXIT_SUCCESS;
}