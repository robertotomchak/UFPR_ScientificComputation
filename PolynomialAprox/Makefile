# PROGRAMA
    PROG = ajustePolV2 ajustePolV1 gera

# Compilador
    LIKWID_HOME = /home/soft/likwid
    CC     = gcc
    CFLAGS = -O3 -mavx -march=native -DLIKWID_PERFMON -I${LIKWID_HOME}/include
    LFLAGS = -lm -L${LIKWID_HOME}/lib -llikwid

# Lista de arquivos para distribuição.
# LEMBRE-SE DE ACRESCENTAR OS ARQUIVOS ADICIONAIS SOLICITADOS NO ENUNCIADO DO TRABALHO
DISTFILES = *.c *.h LEIAME* Makefile 
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $< -g $(LFLAGS)

all: $(PROG)

ajustePolV1: ajustePolV1.c utils.c
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS)


ajustePolV2: ajustePolV2.c utils.c
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS)

gera: gera_entrada.c utils.c
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS)

clean:

purge:  clean
	rm ajustePolV1
	rm ajustePolV2
	rm gera

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
