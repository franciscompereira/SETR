# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c11

# Nome do programa final
TARGET = myprogram

# Ficheiros objeto (.o) a compilar
OBJS = main.o mylib.o

# Regra principal (gera o programa final)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar main.c -> main.o
main.o: main.c mylib.h
	$(CC) $(CFLAGS) -c main.c

# Regra para compilar mylib.c -> mylib.o
mylib.o: mylib.c mylib.h
	$(CC) $(CFLAGS) -c mylib.c

# Limpeza dos ficheiros gerados
clean:
	rm -f $(OBJS) $(TARGET)
