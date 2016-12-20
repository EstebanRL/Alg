/* 
 * File:   ReadData.h
 * Author: esteban
 *
 * Created on 25 de marzo de 2016, 20:48
 */


#include "DataFunctions/group.h"
#include "DataFunctions/util.h"
#include "DataFunctions/file.h"
#include "DataFunctions/point.h"



// LAS 1.4 Specification http://www.asprs.org/a/society/committees/standards/LAS_1_4_r13.pdf
#define UNCLASSIFIED 0
#define UNKNOWN 1
#define GROUND 2
#define NO_GROUND 6
#define LOW_VEGETATION 3
#define TREE 5
#define SMALL_BUILDING 8    // Reserved field
#define ROAD 11
#define PARKING 12          // Reserved field
#define ROAD_CANDIDATE 19   // Reserved field

