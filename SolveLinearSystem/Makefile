# PROGRAMA
    PROG = perfEG

# Compilador
	LIKWID_HOME = /home/soft/likwid
    CC     = gcc
  	CFLAGS = "-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
    LFLAGS = "-L${LIKWID_HOME}/lib -llikwid" -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

all: main

main:
	gcc $(CLAGS) eg.c -o main $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
