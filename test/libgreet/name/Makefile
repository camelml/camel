# source files
SOURCES = first.cpp last.cpp name.cpp

# list of extesntion whose files are to be deleted after install
CLEAN_EXTS = o a

# output library name
OUTPUT_FILE = libname.a

# directory to store binaries
INSTALL_DIR = ../binaries

# default target
.PHONY: all
all: $(OUTPUT_FILE)

# create library and prereq are all object files
$(OUTPUT_FILE): $(subst .cpp,.o,$(SOURCES))
	ar ru $@ $^
	ranlib $@

# store library in folder
.PHONY: install
install:
	mkdir -p $(INSTALL_DIR)
	cp -p $(OUTPUT_FILE) $(INSTALL_DIR)

# clean all obj and a files
.PHONY: clean
clean:
	for file in $(CLEAN_EXTS); do rm -f *.$$file; done

# create object files for library
# john.o: john.hpp

# paul.o: paul.hpp

# johnpaul.o: john.hpp paul.hpp johnpaul.hpp
# these can be replaced by

# Generate dependencies of .cpp files on .hpp files
include $(subst .cpp,.d,$(SOURCES))
%.d: %.cpp
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$