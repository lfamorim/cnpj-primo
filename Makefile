# Detectar sistema operacional
ifeq ($(shell uname), Darwin)
	# macOS com clang
	CC = clang
	CFLAGS = -Wall -Wextra -O3 -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include
	LDFLAGS = -L/opt/homebrew/opt/libomp/lib
	LIBS = -lomp -lm
else
	# Linux/outros com gcc
	CC = gcc
	CFLAGS = -Wall -Wextra -O3 -fopenmp
	LDFLAGS =
	LIBS = -lm
endif

TARGETS = cnpj_primo cpf_primo

all: $(TARGETS)

cnpj_primo: primo.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

cpf_primo: cpf_primo.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGETS)

.PHONY: all clean
