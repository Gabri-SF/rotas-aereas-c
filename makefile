CC = gcc
# Mantive as tuas flags originais
CFLAGS = -Wall -Wextra -std=c99 -ansi
LDFLAGS = -lm

# Todos os cabeçalhos (.h) do projeto
DEPS = tipos.h matematica.h ficheiros.h aeroportos_rotas.h escalas.h memoria.h

# Todos os ficheiros de código fonte (.c) do projeto
SRCS = rotas2024.c \
       matematica.c \
       ficheiros.c \
       aeroportos_rotas.c \
       voos_diretos.c \
       voos_1_escala.c \
       voos_2_escalas.c \
       memoria.c

# Converte a lista de .c para .o (object files)
OBJS = $(SRCS:.c=.o)
TARGET = rotas2024

.PHONY: all clean

all: $(TARGET)

# O executável final depende de todos os .o
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Cada ficheiro .o depende do seu respetivo .c e de TODOS os headers (DEPS)
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)