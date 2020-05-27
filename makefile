CC = clang
PROG = cnake

include common.mk

CFLAGS += -g -fsanitize=address -std=c99
LDFLAGS += -lncurses

# linking the program.
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
