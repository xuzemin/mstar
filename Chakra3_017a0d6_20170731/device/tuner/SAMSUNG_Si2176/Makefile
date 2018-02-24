#####################################
# Semco Si2176 Library Makefile
# by Yoo Heeyong 2011.05.25
#####################################

#####################################
CC=gcc
AR=ar
CHMOD=chmod
#####################################

#####################################
INC= .
LIB= .
CFLAGS= -O2 -W -Wall -Wextra -Wcast-align -Wno-unused-parameter -Wshadow -Wwrite-strings -Wcast-qual -fno-strict-aliasing -fsigned-char -O2 -Werror -fshort-wchar -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-common -fno-optimize-sibling-calls -I$(INC)
LFLAGS=-L$(LIB)
#####################################

#####################################
SRCS= UserDefinedIIC.c Si2176_L1_API_TV_Chassis.c Si2176_L0_TV_Chassis.c Si2176_L1_Commands.c Si2176_L1_Properties.c Si2176_L2_TV_Chassis.c Si2176_Generic_DTV_Demod.c Si2176_Generic_Sound_Processor.c SemcoSi2176.c
OBJS= UserDefinedIIC.o Si2176_L1_API_TV_Chassis.o Si2176_L0_TV_Chassis.o Si2176_L1_Commands.o Si2176_L1_Properties.o Si2176_L2_TV_Chassis.o Si2176_Generic_DTV_Demod.o Si2176_Generic_Sound_Processor.o SemcoSi2176.o
EXES= $(LIB)/semcolib.a
ALL= $(EXES)
#####################################

#####################################
all: $(ALL)
$(OBJS):
	$(CC) -c $(CFLAGS) $*.c
$(ALL): $(OBJS) $(INCS)
	$(AR) vru $@ $(OBJS)
#####################################

#####################################
clean:
	rm -f core $(OBJS) $(ALL)
#####################################


