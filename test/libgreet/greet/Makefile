# Specify the source files, target files, the build directories,
# and the install directory
SOURCES = greet.cpp
OUTPUTFILE = greet
LIBNAME = libname.a
LIBHELLOTHERE = libhellothere.a
HELLOTHEREDIR = ../hellothere
NAMEDIR = ../name
INSTALLDIR = ../binaries

#
# Add the parent directory as an include path
#
CPPFLAGS += -I..

# default target
.PHONY: all
all: $(OUTPUTFILE)

# build executable
$(OUTPUTFILE): $(subst .cpp,.o,$(SOURCES)) \
$(HELLOTHEREDIR)/$(LIBHELLOTHERE) \
$(NAMEDIR)/$(LIBNAME)
	$(CXX) $(LDFLAGS) -o $@ $^

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(OUTPUTFILE)

# Generate dependencies of .ccp files on .hpp files
include $(subst .cpp,.d,$(SOURCES))
%.d: %.cpp
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$