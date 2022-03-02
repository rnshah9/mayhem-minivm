OPT ?= -Os

default: all

all: minivm dis asmin

minivm: .dummy
	$(CC) $(OPT) vm/minivm.c -o minivm $(CFLAGS)

dis: .dummy
	$(CC) $(OPT) vm/dis.c -o dis $(CFLAGS)

asmin: .dummy
	$(CC) $(OPT) vm/asmin.c -o asmin $(CFLAGS)

.dummy:

clean: .dummy
	rm -f $(OBJS) minivm dis
