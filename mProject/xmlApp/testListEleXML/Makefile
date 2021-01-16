CC=gcc
ADIR1=/home/jui/mProject
TDIR=$(ADIR1)/library_jui/XMLLibrary
IDIR=$(TDIR)/src
LDIR=$(TDIR)/lib
ODIR=$(TDIR)/obj

STRDIR=$(ADIR1)/library_jui/strLibrary
STRIDIR=$(STRDIR)/src
STRODIR=$(STRDIR)/obj
STRLDIR=$(STRDIR)/lib
TARGET=test
PREF1= $(LDIR)/lib
STRPREF1=$(STRLDIR)/lib
PREF2= -l

_DEP1=simReadXML
_DEP2=listChar
_DEP3=listMatChar
_DEP4=simMatChar
_DEP5=eleXMLNodeList
_DEP6=convertStr2Digi
_DEP7=simStringList
_DEP8=simString


DEP1=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP1)))
DEP2=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP2)))
DEP3=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP3)))
DEP4=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP4)))
DEP5=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP5)))
DEP6=$(addsuffix .so,$(addprefix $(STRPREF1),$(_DEP6)))
DEP7=$(addsuffix .so,$(addprefix $(STRPREF1),$(_DEP7)))
DEP8=$(addsuffix .so,$(addprefix $(STRPREF1),$(_DEP8)))
O1=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP1)))
O2=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP2)))
O3=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP3)))
O4=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP4)))
O5=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP5)))
O6=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP6)))
O7=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP7)))
O8=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP8)))
SRC1=$(addprefix $(IDIR)/,$(_DEP1))
SRC2=$(addprefix $(IDIR)/,$(_DEP2))
SRC3=$(addprefix $(IDIR)/,$(_DEP3))
SRC4=$(addprefix $(IDIR)/,$(_DEP4))
SRC5=$(addprefix $(IDIR)/,$(_DEP5))
SRC6=$(addprefix $(STRIDIR)/,$(_DEP6))
SRC7=$(addprefix $(STRIDIR)/,$(_DEP7))
SRC8=$(addprefix $(STRIDIR)/,$(_DEP8))
OBJ=$(DEP1)
OBJ+=$(DEP2)
OBJ+=$(DEP3)
OBJ+=$(DEP4)
OBJ+=$(DEP5)
OBJ+=$(DEP6)
OBJ+=$(DEP7)
OBJ+=$(DEP8)
_OBJ=$(_DEP1)
_OBJ+=$(_DEP2)
_OBJ+=$(_DEP3)
_OBJ+=$(_DEP4)
_OBJ+=$(_DEP5)
_OBJ+=$(_DEP6)
_OBJ+=$(_DEP7)
_OBJ+=$(_DEP8)

LOPT=$(addprefix $(PREF2),$(_OBJ))

CMD1= $(CC) $(CFLAGS) -L$(LDIR) -L$(STRLDIR) -Wall -o $@ $@.c -I$(IDIR) -I$(STRIDIR) $(LOPT)
CMD2= $(CC) -shared -o $@ $<
CMD3= $(CC) $(CFLAGS) -c -Wall -Werror -fpic $< -I$(IDIR) -I$(STRIDIR) -o $@
$(TARGET):$(OBJ) $(TARGET).c
	$(CMD1)
$(DEP5):$(O5)
	$(CMD2)
$(O5):$(SRC5).c $(SRC5).h
	$(CMD3)
$(DEP1):$(O1)
	$(CMD2)
$(O1):$(SRC1).c $(SRC1).h
	$(CMD3)
$(DEP2):$(O2)
	$(CMD2)
$(O2):$(SRC2).c $(SRC2).h
	$(CMD3)
$(DEP7):$(O7)
	$(CMD2)
$(O7):$(SRC7).c $(SRC7).h
	$(CMD3)
$(DEP8):$(O8)
	$(CMD2)
$(O8):$(SRC8).c $(SRC8).h
	$(CMD3)
$(DEP3):$(O3)
	$(CMD2)
$(O3):$(SRC3).c $(SRC3).h
	$(CMD3)
$(DEP6):$(O6)
	$(CMD2)
$(O6):$(SRC6).c $(SRC6).h
	$(CMD3)
$(DEP4):$(O4)
	$(CMD2)
$(O4):$(SRC4).c $(SRC4).h
	$(CMD3)
clean:
	rm $(LDIR)/* $(ODIR)/* $(STRLDIR)/* $(STRODIR)/*
	rm $(TARGET)
