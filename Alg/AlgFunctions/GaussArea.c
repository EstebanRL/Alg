/* 
 * File:   GaussArea.c
 * Author: esteban
 *
 */

#include <stdio.h>
#include "math.h"
#include "GaussArea.h"

int GaussArea(Group *group){
    
    if(*group==NULL)
        return 1;
        
    if((*group)->size < 2)
        return 2;
    
    double xySum=0.0, yxSum=0.0;
    Node n = (*group)->start;
    
    while(n->next->next!=NULL)
    {
        xySum += n->elem.x * n->next->elem.y;
        yxSum += n->elem.y * n->next->elem.x;
        n=n->next;
    }
    
    xySum += n->elem.x * (*group)->start->elem.y;   
    yxSum += n->elem.y * (*group)->start->elem.x;
    
     
    (*group)->area = fabs((xySum - yxSum)) * 0.5;
   
    return 0;
}

