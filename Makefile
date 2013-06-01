CC=mpicc
WARNOPT=-Wall -Wextra -Werror

COMPILE.c=$(CC) $(CFLAGS) $(WARNOPT) $(TARGET_ARCH) -c

all: mpihello

mpihello: mpihello.o

clean:
	$(RM) mpihello.o mpihello

.PHONY: clean
