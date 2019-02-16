# All the targets in this makefile are phony
.PHONY: all name hellothere greet

# Default target
all: greet

# The targets johnpaul, georgeringo, and hellobeatles represent
# directories; the command script invokes make in each directory
name hellothere greet:
	$(MAKE) --directory=$@ $(TARGET)

# This rule indicates that the default target of the makefile
# in directory hellobeatles depends on the default targets of
# the makefiles in the directories johnpaul and georgeringo
.PHONY: greet
greet: name hellothere