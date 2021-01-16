CC=gcc
TARGET=main
ADIR=/dirI/MyCode/mProject
TDIR=$(ADIR)/library_jui/TreeLib
IDIR=$(TDIR)/src
ODIR=$(TDIR)/obj
LDIR=$(TDIR)/lib

XMLTDIR=$(ADIR)/library_jui/XMLLibrary
XMLIDIR=$(XMLTDIR)/src
XMLODIR=$(XMLTDIR)/obj
XMLLDIR=$(XMLTDIR)/lib

DTSTDIR=$(ADIR)/library_jui/dataStruct
DTSIDIR=$(DTSTDIR)/src
DTSODIR=$(DTSTDIR)/obj
DTSLDIR=$(DTSTDIR)/lib

STRDIR=$(ADIR)/library_jui/strLibrary
STRIDIR=$(STRDIR)/src
STRODIR=$(STRDIR)/obj
STRLDIR=$(STRDIR)/lib

PREF1= $(LDIR)/lib
PREF3= $(STRLDIR)/lib
PREF4= $(DTSLDIR)/lib
PREF5= $(XMLLDIR)/lib
PREF2= -l

_DEP1=dataTypeAndRoutineDefine
_DEP2=binaryTree
_DEP3=simString
_DEP4=avlTree
_DEP5=simStringTree
_DEP6=simMatDouble
_DEP7=simMatChar
_DEP8=listPvoid

DEP1=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP1)))
DEP2=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP2)))
DEP3=$(addsuffix .so,$(addprefix $(PREF3),$(_DEP3)))
DEP4=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP4)))
DEP5=$(addsuffix .so,$(addprefix $(PREF3),$(_DEP5)))
DEP6=$(addsuffix .so,$(addprefix $(PREF4),$(_DEP6)))
DEP7=$(addsuffix .so,$(addprefix $(PREF5),$(_DEP7)))
DEP8=$(addsuffix .so,$(addprefix $(PREF4),$(_DEP8)))
O1=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP1)))
O2=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP2)))
O3=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP3)))
O4=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP4)))
O5=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP5)))
O6=$(addsuffix .o,$(addprefix $(DTSODIR)/,$(_DEP6)))
O7=$(addsuffix .o,$(addprefix $(XMLODIR)/,$(_DEP7)))
O8=$(addsuffix .o,$(addprefix $(DTSODIR)/,$(_DEP8)))
SRC1=$(addprefix $(IDIR)/,$(_DEP1))
SRC2=$(addprefix $(IDIR)/,$(_DEP2))
SRC3=$(addprefix $(STRIDIR)/,$(_DEP3))
SRC4=$(addprefix $(IDIR)/,$(_DEP4))
SRC5=$(addprefix $(STRIDIR)/,$(_DEP5))
SRC6=$(addprefix $(DTSIDIR)/,$(_DEP6))
SRC7=$(addprefix $(XMLIDIR)/,$(_DEP7))
SRC8=$(addprefix $(DTSIDIR)/,$(_DEP8))
OBJ =$(DEP6)
OBJ+=$(DEP8)
OBJ+=$(DEP3)
OBJ+=$(DEP5)
OBJ+=$(DEP1)
OBJ+=$(DEP2)
OBJ+=$(DEP4)
_OBJ=$(_DEP5)
LOPT=$(addprefix $(PREF2),$(_OBJ))
CMD1= $(CC) $(CFLAGS) -L$(DTSLDIR) -L$(XMLLDIR) -L$(STRLDIR) -L$(LDIR)  -Wall -o $@ $@.c -I$(XMLIDIR) -I$(DTSIDIR) -I$(STRIDIR) -I$(IDIR) $(LOPT)
CMD2= $(CC) -shared -o $@ $<
CMD3= $(CC) $(CFLAGS) -c -Wall -Werror -fpic $< -I$(IDIR) -I$(STRIDIR) -I$(DTSIDIR) -I$(XMLIDIR) -o $@
$(TARGET):$(OBJ) $(TARGET).c
	$(CMD1)
$(DEP5):$(O5) $(O4) $(O1) $(O2) $(O3) $(O7) $(O6)
	$(CMD2) $(O4) $(O1) $(O2) $(O3) $(O7) $(O6)
$(O5):$(SRC5).c $(SRC5).h
	$(CMD3)
$(DEP4):$(O4) 
	$(CMD2)
$(O4):$(SRC4).c $(SRC4).h
	$(CMD3)
$(DEP2):$(O2) $(O3)
	$(CMD2) $(O3)
$(O2):$(SRC2).c $(SRC2).h
	$(CMD3)
$(DEP1):$(O1)
	$(CMD2) $(O5)
$(O1):$(SRC1).c $(SRC1).h
	$(CMD3)
$(DEP3):$(O3)
	$(CMD2) 
$(O3):$(SRC3).c $(SRC3).h 
	$(CMD3) 
$(DEP7):$(O7)
	$(CMD2)
$(O7):$(SRC7).c $(SRC7).h
	$(CMD3)
$(DEP8):$(O8)
	$(CMD2)
$(O8):$(SRC8).c $(SRC8).h
	$(CMD3)
$(DEP6):$(O6)
	$(CMD2)
$(O6):$(SRC6).c $(SRC6).h
	$(CMD3)
clean: 
	rm $(LDIR)/* $(ODIR)/*  $(STRODIR)/* $(STRLDIR)/*  $(XMLODIR)/* $(DTSODIR)/* $(DTSLDIR)/* $(XMLLDIR)/*
	rm $(TARGET)
