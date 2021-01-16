CC=gcc
TARGET=main
ADIR=/dirI/MyCode/mProject
TDIR=$(ADIR)/library_jui/TreeLib
IDIR=$(TDIR)/src
ODIR=$(TDIR)/obj
LDIR=$(TDIR)/lib


DTSTDIR=$(ADIR)/library_jui/dataStruct
DTSIDIR=$(DTSTDIR)/src
DTSODIR=$(DTSTDIR)/obj
DTSLDIR=$(DTSTDIR)/lib

PREF1= $(LDIR)/lib
PREF3= $(DTSLDIR)/lib
PREF2= -l

_DEP1=dataTypeAndRoutineDefine
_DEP2=binaryTree
_DEP3=simMatDouble
_DEP4=avlTree

DEP1=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP1)))
DEP2=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP2)))
DEP3=$(addsuffix .so,$(addprefix $(PREF3),$(_DEP3)))
DEP4=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP4)))
O1=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP1)))
O2=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP2)))
O3=$(addsuffix .o,$(addprefix $(DTSODIR)/,$(_DEP3)))
O4=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP4)))
SRC1=$(addprefix $(IDIR)/,$(_DEP1))
SRC2=$(addprefix $(IDIR)/,$(_DEP2))
SRC3=$(addprefix $(DTSIDIR)/,$(_DEP3))
SRC4=$(addprefix $(IDIR)/,$(_DEP4))
OBJ=$(DEP3)
OBJ+=$(DEP1)
OBJ+=$(DEP2)
OBJ+=$(DEP4)
_OBJ=$(_DEP4)
LOPT=$(addprefix $(PREF2),$(_OBJ))
CMD1= $(CC) $(CFLAGS) -L$(DTSLDIR) -L$(LDIR)  -Wall -o $@ $@.c -I$(DTSIDIR) -I$(IDIR) $(LOPT)
CMD2= $(CC) -shared -o $@ $<
CMD3= $(CC) $(CFLAGS) -c -Wall -Werror -fpic $< -I$(IDIR) -I$(DTSIDIR) -o $@
$(TARGET):$(OBJ) $(TARGET).c
	$(CMD1)
$(DEP3):$(O3)
	$(CMD2)
$(O3):$(SRC3).c $(SRC3).h
	$(CMD3)
$(DEP4):$(O4) $(O2)
	$(CMD2) $(O1) $(O2) $(O3)
$(O4):$(SRC4).c $(SRC4).h
	$(CMD3)
$(DEP2):$(O2) 
	$(CMD2) 
$(O2):$(SRC2).c $(SRC2).h
	$(CMD3)
$(DEP1):$(O1)
	$(CMD2)
$(O1):$(SRC1).c $(SRC1).h
	$(CMD3)
clean: 
	rm $(LDIR)/* $(ODIR)/*  $(DTSODIR)/* $(DTSLDIR)/*
	rm $(TARGET)
