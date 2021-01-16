CC=gcc
ADIR1=/home/jui/mProject/library_jui
TDIR=$(ADIR1)/XMLLibrary
IDIR=$(TDIR)/src
LDIR=$(TDIR)/lib
ODIR=$(TDIR)/obj

FTDIR=$(ADIR1)/FileNameHandle
FIDIR=$(FTDIR)/src
FLDIR=$(FTDIR)/lib
FODIR=$(FTDIR)/obj

XUIDIR=$(ADIR1)/XMLAppLib
XUIIDIR=$(XUIDIR)/src
XUIODIR=$(XUIDIR)/obj
XUILDIR=$(XUIDIR)/lib

STRDIR=$(ADIR1)/strLibrary
STRIDIR=$(STRDIR)/src
STRODIR=$(STRDIR)/obj
STRLDIR=$(STRDIR)/lib
TARGET=test
PREF1= $(LDIR)/lib
STRPREF1=$(STRLDIR)/lib
XUIPREF1=$(XUILDIR)/lib
FPREF1=$(FLDIR)/lib
PREF2= -l

_DEP1=XmlUi
_DEP2=listChar
_DEP3=listMatChar
_DEP4=simMatChar
_DEP5=convertStr2Digi
_DEP6=simStringList
_DEP7=simString
_DEP8=simWriteXML
_DEP9=simReadXML
_DEP10=FileNameHandle
_DEP11=eleXMLNodeList

DEP1=$(addsuffix .so,$(addprefix $(XUIPREF1),$(_DEP1)))
DEP2=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP2)))
DEP3=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP3)))
DEP4=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP4)))
DEP5=$(addsuffix .so,$(addprefix $(STRPREF1),$(_DEP5)))
DEP6=$(addsuffix .so,$(addprefix $(STRPREF1),$(_DEP6)))
DEP7=$(addsuffix .so,$(addprefix $(STRPREF1),$(_DEP7)))
DEP8=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP8)))
DEP9=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP9)))
DEP10=$(addsuffix .so,$(addprefix $(FPREF1),$(_DEP10)))
DEP11=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP11)))
O1=$(addsuffix .o,$(addprefix $(XUIODIR)/,$(_DEP1)))
O2=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP2)))
O3=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP3)))
O4=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP4)))
O5=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP5)))
O6=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP6)))
O7=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_DEP7)))
O8=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP8)))
O9=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP9)))
O10=$(addsuffix .o,$(addprefix $(FODIR)/,$(_DEP10)))
O11=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP11)))
SRC1=$(addprefix $(XUIIDIR)/,$(_DEP1))
SRC2=$(addprefix $(IDIR)/,$(_DEP2))
SRC3=$(addprefix $(IDIR)/,$(_DEP3))
SRC4=$(addprefix $(IDIR)/,$(_DEP4))
SRC5=$(addprefix $(STRIDIR)/,$(_DEP5))
SRC6=$(addprefix $(STRIDIR)/,$(_DEP6))
SRC7=$(addprefix $(STRIDIR)/,$(_DEP7))
SRC8=$(addprefix $(IDIR)/,$(_DEP8))
SRC9=$(addprefix $(IDIR)/,$(_DEP9))
SRC10=$(addprefix $(FIDIR)/,$(_DEP10))
SRC11=$(addprefix $(IDIR)/,$(_DEP11))
OBJ=$(DEP1)
OBJ+=$(DEP9)
OBJ+=$(DEP2)
OBJ+=$(DEP3)
OBJ+=$(DEP4)
OBJ+=$(DEP5)
OBJ+=$(DEP6)
OBJ+=$(DEP7)
OBJ+=$(DEP8)
OBJ+=$(DEP10)
OBJ+=$(DEP11)
_OBJ=$(_DEP1)
_OBJ+=$(_DEP9)
_OBJ+=$(_DEP2)
_OBJ+=$(_DEP3)
_OBJ+=$(_DEP4)
_OBJ+=$(_DEP5)
_OBJ+=$(_DEP6)
_OBJ+=$(_DEP7)
_OBJ+=$(_DEP8)
_OBJ+=$(_DEP10)
_OBJ+=$(_DEP11)

LOPT=$(addprefix $(PREF2),$(_OBJ))

CMD1= $(CC) $(CFLAGS) -L$(LDIR) -L$(STRLDIR) -L$(XUILDIR) -L$(FLDIR) -Wall -o $@ $@.c -I$(FIDIR) -I$(IDIR) -I$(STRIDIR) -I$(XUIIDIR) $(LOPT)
CMD2= $(CC) -shared -o $@ $<
CMD3= $(CC) $(CFLAGS) -c -Wall -Werror -fpic $< -I$(FIDIR) -I$(IDIR) -I$(STRIDIR) -I$(XUIIDIR)  -o $@
$(TARGET):$(OBJ) $(TARGET).c
	$(CMD1)
$(DEP1):$(O1)
	$(CMD2)
$(O1):$(SRC1).c $(SRC1).h
	$(CMD3)
$(DEP2):$(O2)
	$(CMD2)
$(O2):$(SRC2).c $(SRC2).h
	$(CMD3)
$(DEP3):$(O3)
	$(CMD2)
$(O3):$(SRC3).c $(SRC3).h
	$(CMD3)
$(DEP4):$(O4)
	$(CMD2)
$(O4):$(SRC4).c $(SRC4).h
	$(CMD3)
$(DEP5):$(O5)
	$(CMD2)
$(O5):$(SRC5).c $(SRC5).h
	$(CMD3)
$(DEP6):$(O6)
	$(CMD2)
$(O6):$(SRC6).c $(SRC6).h
	$(CMD3)
$(DEP7):$(O7)
	$(CMD2)
$(O7):$(SRC7).c $(SRC7).h
	$(CMD3)
$(DEP8):$(O8)
	$(CMD2)
$(O8):$(SRC8).c $(SRC8).h
	$(CMD3)
$(DEP9):$(O9)
	$(CMD2)
$(O9):$(SRC9).c $(SRC9).h
	$(CMD3)
$(DEP10):$(O10)
	$(CMD2)
$(O10):$(SRC10).c $(SRC10).h
	$(CMD3)
$(DEP11):$(O11)
	$(CMD2)
$(O11):$(SRC11).c $(SRC11).h
	$(CMD3)


clean:
	rm $(LDIR)/* $(ODIR)/* $(STRLDIR)/* $(STRODIR)/* $(FODIR)/* $(FLDIR)/* $(XUILDIR)/* $(XUIODIR)/*  
	rm $(TARGET)