# PROGRAMA
    PROG = inversa
    OBJS = inversa.o array.o lu_decomposition.o utils.o

# Compilador
    CC     = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
    LIKWID_HOME = /home/soft/likwid
    CFLAGS = -DLIKWID_PERFMON -I${LIKWID_HOME}/include -O0
    LFLAGS = -L${LIKWID_HOME}/lib -llikwid -lm

# Lista de arquivos para distribuição. Acrescentar mais arquivos se necessário.
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $< -g

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) $(OBJS) core a.out $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
