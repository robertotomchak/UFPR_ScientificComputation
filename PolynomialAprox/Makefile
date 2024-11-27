# PROGRAMA
    PROG = ajustePolV2 ajustePolV1

# Compilador
    CC     = gcc
    CFLAGS = -O3 -mavx -march=native
    LFLAGS = -lm

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

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak core 

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
