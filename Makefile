CC = mpicc
CFLAGS = -pipe -march=native -std=c99 -Wall -Wextra --pedantic -O3
LDLIBS =
LDFLAGS = -pipe

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

EXE = prog

.PHONY:	clean mrproper

all:	depend $(EXE)

$(EXE): depend $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# makedepend: le package xutils-dev doit être installé
#EDIT personnel : (sous Ubuntu/Debian c'est valide)
depend:
	@makedepend -- $(CFLAGS) -- -Y $(SRCS) 2> /dev/null

clean:
	rm -f *.o

mrproper:	clean
	rm -f $(EXE)

# DO NOT DELETE THIS LINE