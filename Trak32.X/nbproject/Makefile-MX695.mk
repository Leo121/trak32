#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-MX695.mk)" "nbproject/Makefile-local-MX695.mk"
include nbproject/Makefile-local-MX695.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=MX695
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Trak32.c trakhardware.c trakserial.c trakcommands.c trakLEDs.c trakbarometer.c trakeep.c trakaccel.c trakADC.c p32_i2c2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Trak32.o ${OBJECTDIR}/trakhardware.o ${OBJECTDIR}/trakserial.o ${OBJECTDIR}/trakcommands.o ${OBJECTDIR}/trakLEDs.o ${OBJECTDIR}/trakbarometer.o ${OBJECTDIR}/trakeep.o ${OBJECTDIR}/trakaccel.o ${OBJECTDIR}/trakADC.o ${OBJECTDIR}/p32_i2c2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Trak32.o.d ${OBJECTDIR}/trakhardware.o.d ${OBJECTDIR}/trakserial.o.d ${OBJECTDIR}/trakcommands.o.d ${OBJECTDIR}/trakLEDs.o.d ${OBJECTDIR}/trakbarometer.o.d ${OBJECTDIR}/trakeep.o.d ${OBJECTDIR}/trakaccel.o.d ${OBJECTDIR}/trakADC.o.d ${OBJECTDIR}/p32_i2c2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Trak32.o ${OBJECTDIR}/trakhardware.o ${OBJECTDIR}/trakserial.o ${OBJECTDIR}/trakcommands.o ${OBJECTDIR}/trakLEDs.o ${OBJECTDIR}/trakbarometer.o ${OBJECTDIR}/trakeep.o ${OBJECTDIR}/trakaccel.o ${OBJECTDIR}/trakADC.o ${OBJECTDIR}/p32_i2c2.o

# Source Files
SOURCEFILES=Trak32.c trakhardware.c trakserial.c trakcommands.c trakLEDs.c trakbarometer.c trakeep.c trakaccel.c trakADC.c p32_i2c2.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-MX695.mk dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX695F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Trak32.o: Trak32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Trak32.o.d 
	@${RM} ${OBJECTDIR}/Trak32.o 
	@${FIXDEPS} "${OBJECTDIR}/Trak32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Trak32.o.d" -o ${OBJECTDIR}/Trak32.o Trak32.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakhardware.o: trakhardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakhardware.o.d 
	@${RM} ${OBJECTDIR}/trakhardware.o 
	@${FIXDEPS} "${OBJECTDIR}/trakhardware.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakhardware.o.d" -o ${OBJECTDIR}/trakhardware.o trakhardware.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakserial.o: trakserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakserial.o.d 
	@${RM} ${OBJECTDIR}/trakserial.o 
	@${FIXDEPS} "${OBJECTDIR}/trakserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakserial.o.d" -o ${OBJECTDIR}/trakserial.o trakserial.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakcommands.o: trakcommands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakcommands.o.d 
	@${RM} ${OBJECTDIR}/trakcommands.o 
	@${FIXDEPS} "${OBJECTDIR}/trakcommands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakcommands.o.d" -o ${OBJECTDIR}/trakcommands.o trakcommands.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakLEDs.o: trakLEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakLEDs.o.d 
	@${RM} ${OBJECTDIR}/trakLEDs.o 
	@${FIXDEPS} "${OBJECTDIR}/trakLEDs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakLEDs.o.d" -o ${OBJECTDIR}/trakLEDs.o trakLEDs.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakbarometer.o: trakbarometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakbarometer.o.d 
	@${RM} ${OBJECTDIR}/trakbarometer.o 
	@${FIXDEPS} "${OBJECTDIR}/trakbarometer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakbarometer.o.d" -o ${OBJECTDIR}/trakbarometer.o trakbarometer.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakeep.o: trakeep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakeep.o.d 
	@${RM} ${OBJECTDIR}/trakeep.o 
	@${FIXDEPS} "${OBJECTDIR}/trakeep.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakeep.o.d" -o ${OBJECTDIR}/trakeep.o trakeep.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakaccel.o: trakaccel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakaccel.o.d 
	@${RM} ${OBJECTDIR}/trakaccel.o 
	@${FIXDEPS} "${OBJECTDIR}/trakaccel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakaccel.o.d" -o ${OBJECTDIR}/trakaccel.o trakaccel.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakADC.o: trakADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakADC.o.d 
	@${RM} ${OBJECTDIR}/trakADC.o 
	@${FIXDEPS} "${OBJECTDIR}/trakADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakADC.o.d" -o ${OBJECTDIR}/trakADC.o trakADC.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/p32_i2c2.o: p32_i2c2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/p32_i2c2.o.d 
	@${RM} ${OBJECTDIR}/p32_i2c2.o 
	@${FIXDEPS} "${OBJECTDIR}/p32_i2c2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/p32_i2c2.o.d" -o ${OBJECTDIR}/p32_i2c2.o p32_i2c2.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
else
${OBJECTDIR}/Trak32.o: Trak32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Trak32.o.d 
	@${RM} ${OBJECTDIR}/Trak32.o 
	@${FIXDEPS} "${OBJECTDIR}/Trak32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Trak32.o.d" -o ${OBJECTDIR}/Trak32.o Trak32.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakhardware.o: trakhardware.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakhardware.o.d 
	@${RM} ${OBJECTDIR}/trakhardware.o 
	@${FIXDEPS} "${OBJECTDIR}/trakhardware.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakhardware.o.d" -o ${OBJECTDIR}/trakhardware.o trakhardware.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakserial.o: trakserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakserial.o.d 
	@${RM} ${OBJECTDIR}/trakserial.o 
	@${FIXDEPS} "${OBJECTDIR}/trakserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakserial.o.d" -o ${OBJECTDIR}/trakserial.o trakserial.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakcommands.o: trakcommands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakcommands.o.d 
	@${RM} ${OBJECTDIR}/trakcommands.o 
	@${FIXDEPS} "${OBJECTDIR}/trakcommands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakcommands.o.d" -o ${OBJECTDIR}/trakcommands.o trakcommands.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakLEDs.o: trakLEDs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakLEDs.o.d 
	@${RM} ${OBJECTDIR}/trakLEDs.o 
	@${FIXDEPS} "${OBJECTDIR}/trakLEDs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakLEDs.o.d" -o ${OBJECTDIR}/trakLEDs.o trakLEDs.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakbarometer.o: trakbarometer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakbarometer.o.d 
	@${RM} ${OBJECTDIR}/trakbarometer.o 
	@${FIXDEPS} "${OBJECTDIR}/trakbarometer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakbarometer.o.d" -o ${OBJECTDIR}/trakbarometer.o trakbarometer.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakeep.o: trakeep.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakeep.o.d 
	@${RM} ${OBJECTDIR}/trakeep.o 
	@${FIXDEPS} "${OBJECTDIR}/trakeep.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakeep.o.d" -o ${OBJECTDIR}/trakeep.o trakeep.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakaccel.o: trakaccel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakaccel.o.d 
	@${RM} ${OBJECTDIR}/trakaccel.o 
	@${FIXDEPS} "${OBJECTDIR}/trakaccel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakaccel.o.d" -o ${OBJECTDIR}/trakaccel.o trakaccel.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/trakADC.o: trakADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/trakADC.o.d 
	@${RM} ${OBJECTDIR}/trakADC.o 
	@${FIXDEPS} "${OBJECTDIR}/trakADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/trakADC.o.d" -o ${OBJECTDIR}/trakADC.o trakADC.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
${OBJECTDIR}/p32_i2c2.o: p32_i2c2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/p32_i2c2.o.d 
	@${RM} ${OBJECTDIR}/p32_i2c2.o 
	@${FIXDEPS} "${OBJECTDIR}/p32_i2c2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/p32_i2c2.o.d" -o ${OBJECTDIR}/p32_i2c2.o p32_i2c2.c    -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -DSYS_CLOCK=24000000
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_MX695=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Trak32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/MX695
	${RM} -r dist/MX695

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
