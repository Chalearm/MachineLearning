#local = LO
CC=gcc
TARGET=main
ADIR=/Users/chalearm/Documents/mProject
PATHLIB=$(ADIR)/library_jui
FADIR=$(PATHLIB)/replaceFileLib
LODIR=$(ADIR)/svmApp
TDIR=$(PATHLIB)/XMLLibrary

#fileApp lib
FAIDIR=$(FADIR)/src
FAODIR=$(FADIR)/obj
FALDIR=$(FADIR)/lib

#strLibrary
STRDIR=$(PATHLIB)/strLibrary
STRIDIR=$(STRDIR)/src
STRODIR=$(STRDIR)/obj
STRLDIR=$(STRDIR)/lib
#XML library
IDIR=$(TDIR)/src
ODIR=$(TDIR)/obj
LDIR=$(TDIR)/lib

# data structure library
DATSDIR=$(PATHLIB)/dataStruct
DATSIDIR=$(DATSDIR)/src
DATSODIR=$(DATSDIR)/obj
DATSLDIR=$(DATSDIR)/lib

# tree library
TREDIR=$(PATHLIB)/TreeLib
TREIDIR=$(TREDIR)/src
TREODIR=$(TREDIR)/obj
TRELDIR=$(TREDIR)/lib

PREF1=$(LDIR)/lib
PREF2= -l
STRPREF1=$(STRLDIR)/lib
TREPREF1=$(TRELDIR)/lib
DATSPREF1=$(DATSLDIR)/lib
FAPREF1=$(FALDIR)/lib
_DEP1=simReadXML
_DEP2=listChar
_DEP3=listMatChar
_DEP4=simMatChar
_DEP5=eleXMLNodeList
_FADEP1=symHandle
_FADEP2=file_replace
_FADEP3=replacingApp
_DATSDEP2=simMatDouble
_DATSDEP3=simMat2
_STRDEP1=simString
_STRDEP2=convertStr2Digi
_STRDEP3=simStringList
_STRDEP4=convertDataType
_STRDEP5=replaceWord
_TREDEP1=dataTypeAndRoutineDefine
_TREDEP2=binaryTree
_TREDEP3=avlTree
_DATSDEP1=listPvoid
DEP1=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP1)))
DEP2=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP2)))
DEP3=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP3)))
DEP4=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP4)))
DEP5=$(addsuffix .so,$(addprefix $(PREF1),$(_DEP5)))
FADEP1=$(addsuffix .so,$(addprefix $(FAPREF1),$(_FADEP1)))
FADEP2=$(addsuffix .so,$(addprefix $(FAPREF1),$(_FADEP2)))
FADEP3=$(addsuffix .so,$(addprefix $(FAPREF1),$(_FADEP3)))
DATSDEP2=$(addsuffix .so,$(addprefix $(DATSPREF1),$(_DATSDEP2)))
DATSDEP3=$(addsuffix .so,$(addprefix $(DATSPREF1),$(_DATSDEP3)))
STRDEP1=$(addsuffix .so,$(addprefix $(STRPREF1),$(_STRDEP1)))
STRDEP2=$(addsuffix .so,$(addprefix $(STRPREF1),$(_STRDEP2)))
STRDEP3=$(addsuffix .so,$(addprefix $(STRPREF1),$(_STRDEP3)))
STRDEP4=$(addsuffix .so,$(addprefix $(STRPREF1),$(_STRDEP4)))
STRDEP5=$(addsuffix .so,$(addprefix $(STRPREF1),$(_STRDEP5)))
DATSDEP1=$(addsuffix .so,$(addprefix $(DATSPREF1),$(_DATSDEP1)))
TREDEP1=$(addsuffix .so,$(addprefix $(TREPREF1),$(_TREDEP1)))
TREDEP2=$(addsuffix .so,$(addprefix $(TREPREF1),$(_TREDEP2)))
TREDEP3=$(addsuffix .so,$(addprefix $(TREPREF1),$(_TREDEP3)))
O1=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP1)))
O2=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP2)))
O3=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP3)))
O4=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP4)))
O5=$(addsuffix .o,$(addprefix $(ODIR)/,$(_DEP5)))
FAO1=$(addsuffix .o,$(addprefix $(FAODIR)/,$(_FADEP1)))
FAO2=$(addsuffix .o,$(addprefix $(FAODIR)/,$(_FADEP2)))
FAO3=$(addsuffix .o,$(addprefix $(FAODIR)/,$(_FADEP3)))
DATSO2=$(addsuffix .o,$(addprefix $(DATSODIR)/,$(_DATSDEP2)))
DATSO3=$(addsuffix .o,$(addprefix $(DATSODIR)/,$(_DATSDEP3)))
TREO1=$(addsuffix .o,$(addprefix $(TREODIR)/,$(_TREDEP1)))
TREO2=$(addsuffix .o,$(addprefix $(TREODIR)/,$(_TREDEP2)))
TREO3=$(addsuffix .o,$(addprefix $(TREODIR)/,$(_TREDEP3)))
DATSO1=$(addsuffix .o,$(addprefix $(DATSODIR)/,$(_DATSDEP1)))
STRO1=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_STRDEP1)))
STRO2=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_STRDEP2)))
STRO3=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_STRDEP3)))
STRO4=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_STRDEP4)))
STRO5=$(addsuffix .o,$(addprefix $(STRODIR)/,$(_STRDEP5)))
SRC1=$(addprefix $(IDIR)/,$(_DEP1))
SRC2=$(addprefix $(IDIR)/,$(_DEP2))
SRC3=$(addprefix $(IDIR)/,$(_DEP3))
SRC4=$(addprefix $(IDIR)/,$(_DEP4))
SRC5=$(addprefix $(IDIR)/,$(_DEP5))
FASRC1=$(addprefix $(FAIDIR)/,$(_FADEP1))
FASRC2=$(addprefix $(FAIDIR)/,$(_FADEP2))
FASRC3=$(addprefix $(FAIDIR)/,$(_FADEP3))
DATSSRC2=$(addprefix $(DATSIDIR)/,$(_DATSDEP2))
DATSSRC3=$(addprefix $(DATSIDIR)/,$(_DATSDEP3))
STRSRC1=$(addprefix $(STRIDIR)/,$(_STRDEP1))
STRSRC2=$(addprefix $(STRIDIR)/,$(_STRDEP2))
STRSRC3=$(addprefix $(STRIDIR)/,$(_STRDEP3))
STRSRC4=$(addprefix $(STRIDIR)/,$(_STRDEP4))
STRSRC5=$(addprefix $(STRIDIR)/,$(_STRDEP5))
TRESRC1=$(addprefix $(TREIDIR)/,$(_TREDEP1))
TRESRC2=$(addprefix $(TREIDIR)/,$(_TREDEP2))
TRESRC3=$(addprefix $(TREIDIR)/,$(_TREDEP3))
DATSSRC1=$(addprefix $(DATSIDIR)/,$(_DATSDEP1))

OBJ=$(DEP1)
OBJ+=$(DEP2)
OBJ+=$(DEP3)
OBJ+=$(DEP4)
OBJ+=$(DEP5)
OBJ+=$(FADEP1)
OBJ+=$(FADEP2)
OBJ+=$(FADEP3)
OBJ+=$(STRDEP1)
OBJ+=$(STRDEP2)
OBJ+=$(STRDEP3)
OBJ+=$(STRDEP4)
OBJ+=$(STRDEP5)
OBJ+=$(DATSDEP2)
OBJ+=$(DATSDEP3)
OBJ+=$(DATSDEP1)
OBJ+=$(TREDEP1)
OBJ+=$(TREDEP2)
OBJ+=$(TREDEP3)
TOO=$(O1)
TOO+=$(O2)
TOO+=$(O3)
TOO+=$(O4)
TOO+=$(O5)
TOO+=$(FAO1)
TOO+=$(FAO2)
TOO+=$(FAO3)
TOO+=$(STRO1)
TOO+=$(STRO2)
TOO+=$(STRO3)
TOO+=$(STRO4)
TOO+=$(STRO5)
TOO+=$(DATSO2)
TOO+=$(DATSO3)
TOO+=$(DATSO1)
TOO+=$(TREO1)
TOO+=$(TREO2)
TOO+=$(TREO3)
_OBJ=$(_DEP1)
_OBJ+=$(_DEP2)
_OBJ+=$(_DEP3)
_OBJ+=$(_DEP4)
_OBJ+=$(_DEP5)
_OBJ+=$(_FADEP1)
_OBJ+=$(_FADEP2)
_OBJ+=$(_FADEP3)
_OBJ+=$(_STRDEP1)
_OBJ+=$(_STRDEP2)
_OBJ+=$(_STRDEP3)
_OBJ+=$(_STRDEP4)
_OBJ+=$(_STRDEP5)
_OBJ+=$(_DATSDEP2)
_OBJ+=$(_DATSDEP3)
_OBJ+=$(_DATSDEP1)
_OBJ+=$(_TREDEP1)
_OBJ+=$(_TREDEP2)
_OBJ+=$(_TREDEP3)
LOPT=$(addprefix $(PREF2),$(_OBJ))
TOLDIR=-L$(LDIR)
TOLDIR+=-L$(STRLDIR)
TOLDIR+=-L$(TRELDIR)
TOLDIR+=-L$(DATSLDIR)
TOLDIR+=-L$(FALDIR)
TOIDIR=-I$(IDIR)
TOIDIR+=-I$(STRIDIR)
TOIDIR+=-I$(TREIDIR)
TOIDIR+=-I$(DATSIDIR)
TOIDIR+=-I$(FAIDIR)
CMD1= $(CC) $(CFLAGS) $(TOLDIR) -Wall -o $@ $@.c $(TOIDIR) $(LOPT)
CMD2= $(CC) -shared -o $@ $<
CMD3= $(CC) $(CFLAGS) -c -Wall -Werror -fpic $< -o $@ $(TOIDIR)
CMD4= $(CC) -shared -o $@ $(TOO) 
$(TARGET):$(OBJ) $(TARGET).c
	$(CMD1)
$(DATSDEP3):$(DATSO3)
	$(CMD2)
$(DATSO3):$(DATSSRC3).c $(DATSSRC3).h
	$(CMD3)
$(DATSDEP2):$(DATSO2)
	$(CMD2)
$(DATSO2):$(DATSSRC2).c $(DATSSRC2).h
	$(CMD3)
$(DATSDEP1):$(DATSO1)
	$(CMD2)
$(DATSO1):$(DATSSRC1).c $(DATSSRC1).h
	$(CMD3)
$(TREDEP1):$(TREO1)
	$(CMD2)
$(TREO1):$(TRESRC1).c $(TRESRC1).h
	$(CMD3)
$(TREDEP2):$(TREO2)
	$(CMD2)
$(TREO2):$(TRESRC2).c $(TRESRC2).h
	$(CMD3)
$(TREDEP3):$(TREO3) $(DATS03)
	$(CMD2) $(DATS03)
$(TREO3):$(TRESRC3).c $(TRESRC3).h
	$(CMD3)
$(STRDEP1):$(STRO1)
	$(CMD2)
$(STRO1):$(STRSRC1).c $(STRSRC1).h
	$(CMD3)
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
$(STRDEP3):$(STRO3)
	$(CMD2)
$(STRO3):$(STRSRC3).c $(STRSRC3).h
	$(CMD3)
$(STRDEP4):$(STRO4)
	$(CMD2)
$(STRO4):$(STRSRC4).c $(STRSRC4).h
	$(CMD3)
$(STRDEP5):$(STRO5)
	$(CMD2)
$(STRO5):$(STRSRC5).c $(STRSRC5).h
	$(CMD3)
$(STRDEP2):$(STRO2)
	$(CMD2)
$(STRO2):$(STRSRC2).c $(STRSRC2).h
	$(CMD3)
$(FADEP3):$(FAO3)
	$(CMD2)
$(FAO3):$(FASRC3).c $(FASRC3).h
	$(CMD3)
$(FADEP2):$(FAO2)
	$(CMD2)
$(FAO2):$(FASRC2).c $(FASRC2).h
	$(CMD3)
$(FADEP1):$(FAO1)
	$(CMD2)
$(FAO1):$(FASRC1).c $(FASRC1).h
	$(CMD3)
clean:
	rm $(FALDIR)/* $(FAODIR)/* $(TRELDIR)/* $(DATSLDIR)/* $(TREODIR)/* $(DATSODIR)/* $(LDIR)/* $(ODIR)/* $(STRODIR)/* $(STRLDIR)/*
	rm $(TARGET)
