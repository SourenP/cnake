PROG = cnake
CC = clang

include common.mk

CXXFLAGS += -g -fsanitize=address -std=c99
LDFLAGS += -lncurses

# linking the program.
$(PROG): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)
