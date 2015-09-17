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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main/Array.o \
	${OBJECTDIR}/src/main/List.o \
	${OBJECTDIR}/src/main/Map.o \
	${OBJECTDIR}/src/main/Queue.o \
	${OBJECTDIR}/src/main/Stack.o \
	${OBJECTDIR}/src/main/String.o \
	${OBJECTDIR}/src/main/Timer.o \
	${OBJECTDIR}/src/main/Tree.o \
	${OBJECTDIR}/src/main/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/klib.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/klib.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/klib ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/main/Array.o: src/main/Array.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/Array.o src/main/Array.c

${OBJECTDIR}/src/main/List.o: src/main/List.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/List.o src/main/List.c

${OBJECTDIR}/src/main/Map.o: src/main/Map.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/Map.o src/main/Map.c

${OBJECTDIR}/src/main/Queue.o: src/main/Queue.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/Queue.o src/main/Queue.c

${OBJECTDIR}/src/main/Stack.o: src/main/Stack.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/Stack.o src/main/Stack.c

${OBJECTDIR}/src/main/String.o: src/main/String.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/String.o src/main/String.c

${OBJECTDIR}/src/main/Timer.o: src/main/Timer.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/Timer.o src/main/Timer.c

${OBJECTDIR}/src/main/Tree.o: src/main/Tree.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/Tree.o src/main/Tree.c

${OBJECTDIR}/src/main/main.o: src/main/main.c 
	${MKDIR} -p ${OBJECTDIR}/src/main
	${RM} "$@.d"
	$(COMPILE.c) -g -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main/main.o src/main/main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/klib.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
