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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=
CXX=
FC=

# Macros
PLATFORM=MinGW-Windows

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/foom_objects.o \
	${OBJECTDIR}/src/foom_classes/foom_func.o \
	${OBJECTDIR}/src/foom_lex.o \
	${OBJECTDIR}/src/foom_globals.o \
	${OBJECTDIR}/src/foom_util.o \
	${OBJECTDIR}/src/foom_classes/foom_bool.o \
	${OBJECTDIR}/src/foom_classes/foom_str.o \
	${OBJECTDIR}/src/foom_hash.o \
	${OBJECTDIR}/src/foom_classes/foom_int.o \
	${OBJECTDIR}/src/foom_classes/foom_list.o \
	${OBJECTDIR}/src/foom_parser.o \
	${OBJECTDIR}/src/foom.o \
	${OBJECTDIR}/src/foom_test.o \
	${OBJECTDIR}/src/foom_classes/foom_map.o \
	${OBJECTDIR}/src/foom_classes/foom_obj.o \
	${OBJECTDIR}/src/foom_ast.o \
	${OBJECTDIR}/src/foom_ops.o \
	${OBJECTDIR}/src/foom_feval.o \
	${OBJECTDIR}/src/foom_classes/foom_dec.o \
	${OBJECTDIR}/src/foom_gram.o \
	${OBJECTDIR}/src/foom_class.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/foom.exe

dist/Release/${PLATFORM}/foom.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.c} -o dist/Release/${PLATFORM}/foom ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/foom_objects.o: src/foom_objects.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_objects.o src/foom_objects.c

${OBJECTDIR}/src/foom_classes/foom_func.o: src/foom_classes/foom_func.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_func.o src/foom_classes/foom_func.c

${OBJECTDIR}/src/foom_lex.o: src/foom_lex.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_lex.o src/foom_lex.c

${OBJECTDIR}/src/foom_globals.o: src/foom_globals.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_globals.o src/foom_globals.c

${OBJECTDIR}/src/foom_util.o: src/foom_util.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_util.o src/foom_util.c

${OBJECTDIR}/src/foom_classes/foom_bool.o: src/foom_classes/foom_bool.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_bool.o src/foom_classes/foom_bool.c

${OBJECTDIR}/src/foom_classes/foom_str.o: src/foom_classes/foom_str.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_str.o src/foom_classes/foom_str.c

${OBJECTDIR}/src/foom_hash.o: src/foom_hash.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_hash.o src/foom_hash.c

${OBJECTDIR}/src/foom_classes/foom_int.o: src/foom_classes/foom_int.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_int.o src/foom_classes/foom_int.c

${OBJECTDIR}/src/foom_classes/foom_list.o: src/foom_classes/foom_list.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_list.o src/foom_classes/foom_list.c

${OBJECTDIR}/src/foom_parser.o: src/foom_parser.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_parser.o src/foom_parser.c

${OBJECTDIR}/src/foom.o: src/foom.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom.o src/foom.c

${OBJECTDIR}/src/foom_test.o: src/foom_test.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_test.o src/foom_test.c

${OBJECTDIR}/src/foom_classes/foom_map.o: src/foom_classes/foom_map.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_map.o src/foom_classes/foom_map.c

${OBJECTDIR}/src/foom_classes/foom_obj.o: src/foom_classes/foom_obj.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_obj.o src/foom_classes/foom_obj.c

${OBJECTDIR}/src/foom_ast.o: src/foom_ast.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_ast.o src/foom_ast.c

${OBJECTDIR}/src/foom_ops.o: src/foom_ops.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_ops.o src/foom_ops.c

${OBJECTDIR}/src/foom_feval.o: src/foom_feval.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_feval.o src/foom_feval.c

${OBJECTDIR}/src/foom_classes/foom_dec.o: src/foom_classes/foom_dec.c 
	${MKDIR} -p ${OBJECTDIR}/src/foom_classes
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_classes/foom_dec.o src/foom_classes/foom_dec.c

${OBJECTDIR}/src/foom_gram.o: src/foom_gram.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_gram.o src/foom_gram.c

${OBJECTDIR}/src/foom_class.o: src/foom_class.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/foom_class.o src/foom_class.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/foom.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
