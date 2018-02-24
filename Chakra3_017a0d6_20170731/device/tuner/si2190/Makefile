
#####################################
CC=g++
AR=ar
CHMOD=chmod
#####################################

#####################################
INC= .
LIB= .
#CFLAGS= -O2 -W -Wall -Wextra -Wcast-align -Wno-unused-parameter -Wshadow -Wwrite-strings -Wcast-qual -fno-strict-aliasing -fsigned-char -O2 -Werror -fshort-wchar -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-common -fno-optimize-sibling-calls -I$(INC)
CFLAGS= -Wall -Wextra -Wcast-align -Wno-unused-parameter -Wshadow -Wwrite-strings -Wcast-qual -fno-strict-aliasing -fstrict-overflow -fsigned-char -O2 -Werror -fshort-wchar -Wnon-virtual-dtor -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wno-ignored-qualifiers -Wno-c++0x-compat -Wno-array-bounds -Wno-empty-body -fno-unroll-loops -Wswitch-default
LFLAGS=-L$(LIB)
#####################################

##################################### 
SRCS= Si2190_L1_API.cpp Si2190_L1_Commands.cpp Si2190_L1_Properties.cpp Si2190_L2_API.cpp Si2190_Properties_Strings.cpp Silabs_L0_Connection.cpp
OBJS= Si2190_L1_API.o   Si2190_L1_Commands.o   Si2190_L1_Properties.o   Si2190_L2_API.o   Si2190_Properties_Strings.o   Silabs_L0_Connection.o
EXES= $(LIB)/Si2190.a
ALL= $(EXES)
#####################################

#####################################
all: $(ALL)
$(OBJS):
	$(CC) -c $(CFLAGS) $(SRCS)
$(ALL): $(OBJS) $(INCS)
	$(AR) vru $@ $(OBJS)
#####################################

#####################################
clean:
	rm -f core $(OBJS) $(ALL)
#####################################


