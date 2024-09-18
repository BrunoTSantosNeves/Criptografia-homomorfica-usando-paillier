# Nome do executável
TARGET = homomorfic

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror

# Bibliotecas necessárias
LIBS = -lgmp -lpaillier

# Arquivo fonte
SRC = homomorfic.c

# Objetos gerados
OBJ = $(SRC:.c=.o)

# Regra padrão: compilar o programa
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

# Regra para compilar os arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)
