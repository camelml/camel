# make variables
OUTPUTFILE=hello
# we can also use make install INSTALL_DIR=kashish in bash
INSTALL_DIR=binaries

# default target
.PHONY: all
all: $(OUTPUTFILE)

# $@ gives the target or file name
# $< gives first prereq
# $^ gives all prereq with spaces gives hello.cpp
# here $@ gives hello and $<
# below command is not needed only target and prereq will suffice
# $(OUTPUTFILE): hello.cpp
# g++ -o $@ $<
# the simple below command will check if files are changed
# and will compile ony changed files
$(OUTPUTFILE): hello.cpp

# PHONY tells make that this target is not a file but an action and must always be executed
.PHONY: install
install: 
	mkdir -p $(INSTALL_DIR)
	cp -p hello $(INSTALL_DIR)

.PHONY: clean
clean: 
	rm -f hello