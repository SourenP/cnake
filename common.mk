OUT = bin

SEARCHPATH += src
SEARCHPATH += include/hisho/src
vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += defs.h structs.h hisho_ff.h

_OBJS += hisho_ff.o
_OBJS += util.o
_OBJS += food.o
_OBJS += curses_util.o
_OBJS += snake.o
_OBJS += grid.o
_OBJS += collision.o
_OBJS += game.o
_OBJS += main.o

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
$(OUT)/%.o: %.c %.h $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) -c -o $@ $<

# cleaning everything that can be automatically recreated with "make".
clean:
	$(RM) -rf $(OUT) $(PROG)
