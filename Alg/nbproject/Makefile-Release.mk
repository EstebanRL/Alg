#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Alg.o \
	${OBJECTDIR}/AlgFunctions/GrahamScan.o \
	${OBJECTDIR}/AlgFunctions/Exterior.o \
	${OBJECTDIR}/DataFunctions/group.o \
	${OBJECTDIR}/DataFunctions/util.o \
	${OBJECTDIR}/DataFunctions/file.o \
	${OBJECTDIR}/DataFunctions/point.o \
	${OBJECTDIR}/AlgFunctions/Statistically.o \
	${OBJECTDIR}/AlgFunctions/GaussArea.o \
	${OBJECTDIR}/AlgFunctions/Concave.o \
	${OBJECTDIR}/AlgFunctions/Voronoi.o \
	${OBJECTDIR}/AlgFunctions/JarvisMarch.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alg

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alg: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alg ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Alg.o: Alg.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Alg.o Alg.c

${OBJECTDIR}/AlgFunctions/GrahamScan.o: AlgFunctions/GrahamScan.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/GrahamScan.o AlgFunctions/GrahamScan.c

${OBJECTDIR}/AlgFunctions/Exterior.o: AlgFunctions/Exterior.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/Exterior.o AlgFunctions/Exterior.c

${OBJECTDIR}/DataFunctions/group.o: DataFunctions/group.c 
	${MKDIR} -p ${OBJECTDIR}/DataFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataFunctions/group.o DataFunctions/group.c

${OBJECTDIR}/DataFunctions/util.o: DataFunctions/util.c 
	${MKDIR} -p ${OBJECTDIR}/DataFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataFunctions/util.o DataFunctions/util.c

${OBJECTDIR}/DataFunctions/file.o: DataFunctions/file.c 
	${MKDIR} -p ${OBJECTDIR}/DataFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataFunctions/file.o DataFunctions/file.c

${OBJECTDIR}/DataFunctions/point.o: DataFunctions/point.c 
	${MKDIR} -p ${OBJECTDIR}/DataFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataFunctions/point.o DataFunctions/point.c

${OBJECTDIR}/AlgFunctions/Statistically.o: AlgFunctions/Statistically.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/Statistically.o AlgFunctions/Statistically.c

${OBJECTDIR}/AlgFunctions/GaussArea.o: AlgFunctions/GaussArea.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/GaussArea.o AlgFunctions/GaussArea.c

${OBJECTDIR}/AlgFunctions/Concave.o: AlgFunctions/Concave.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/Concave.o AlgFunctions/Concave.c

${OBJECTDIR}/AlgFunctions/Voronoi.o: AlgFunctions/Voronoi.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/Voronoi.o AlgFunctions/Voronoi.c

${OBJECTDIR}/AlgFunctions/JarvisMarch.o: AlgFunctions/JarvisMarch.c 
	${MKDIR} -p ${OBJECTDIR}/AlgFunctions
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AlgFunctions/JarvisMarch.o AlgFunctions/JarvisMarch.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alg

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
