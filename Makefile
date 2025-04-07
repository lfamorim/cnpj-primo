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

TARGET = cnpj_primo
SRC = primo.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
