include ../Make.defines

PROGS =	cli_simple byteorder connect test_listen

all:	${PROGS}

$(PROGS): %: %.c
	${CC} ${CFLAGS} -o $@ $< ${LIBS}
		
clean:
	rm -f ${PROGS} ${CLEANFILES}
