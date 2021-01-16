CC=gcc
TARGET=main
ADIR=/home/jui/mProject
TDIR=$(ADIR)/library_jui/XMLLibrary
IDIR=$(TDIR)/src
ODIR=$(TDIR)/obj
LDIR=$(TDIR)/lib
STRDIR=$(ADIR)/library_jui/strLibrary
STRIDIR=$(STRDIR)/src
STRODIR=$(STRDIR)/obj
STRLDIR=$(STRDIR)/lib

DEP1=simReadXML
DEP2=listChar
DEP3=listMatChar
DEP4=simMatChar
DEP5=convertStr2Digi
DEP6=simStringList
DEP7=simString

OBJ= $(LDIR)/libsimReadXML.so
OBJ+=$(LDIR)/liblistChar.so
OBJ+=$(LDIR)/liblistMatChar.so
OBJ+=$(LDIR)/libsimMatChar.so
OBJ+=$(STRLDIR)/libconvertStr2Digi.so
OBJ+=$(STRLDIR)/libsimStringList.so
OBJ+=$(STRLDIR)/libsimString.so

BO=$(CC) $(CFLAGS) -c -Wall -Werror -fpic $< -I$(IDIR) -I$(STRIDIR) -o $@
BSO=$(CC) -shared -o $@ $<

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -L$(LDIR) -L$(STRLDIR) -Wall -o $@ $@.c -lsimReadXML -llistChar -llistMatChar -lsimStringList -lsimString -lsimMatChar -lconvertStr2Digi -I$(IDIR) -I$(STRIDIR)
$(LDIR)/libsimReadXML.so: $(ODIR)/$(DEP1).o 
	$(BSO)
$(ODIR)/%.o: $(IDIR)/%.c $(IDIR)/$(DEP1).h
	$(BO)
$(LDIR)/liblistChar.so: $(ODIR)/$(DEP2).o
	$(BSO)
$(ODIR)/%.o: $(IDIR)/%.c $(IDIR)/$(DEP2).h
	$(BO)
$(LDIR)/liblistMatChar.so: $(ODIR)/$(DEP3).o
	$(BSO)
$(ODIR)/%.o: $(IDIR)/%.c $(IDIR)/$(DEP3).h
	$(BO)
$(STRLDIR)/libsimStringList.so: $(STRODIR)/$(DEP6).o
	$(BSO)
$(STRODIR)/%.o: $(STRIDIR)/%.c $(STRIDIR)/$(DEP6).h
	$(BO)
$(STRLDIR)/libsimString.so: $(STRODIR)/$(DEP7).o
	$(BSO)
$(STRODIR)/%.o: $(STRIDIR)/%.c $(STRIDIR)/$(DEP7).h
	$(BO)
$(LDIR)/libsimMatChar.so: $(ODIR)/$(DEP4).o
	$(BSO)
$(ODIR)/%.o: $(IDIR)/%.c $(IDIR)/$(DEP4).h
	$(BO)
$(STRLDIR)/libconvertStr2Digi.so: $(STRODIR)/$(DEP5).o
	$(BSO)
$(STRODIR)/%.o: $(STRIDIR)/%.c $(STRIDIR)/$(DEP5).h
	$(BO)
clean:
	rm main
	rm -f $(ODIR)/*.o $(LDIR)/*.so $(STRODIR)/*.o $(STRLDIR)/*.so
