CC=gcc
CFLAGS=-Wall -Wextra -g3
OBJ=main.o cliente.o quartos.o reserva.o hospedagem.o tempo.o  
EXE=main.exe
SRC_DIR=c:\Users\aliss\Documents\sistemahotel
BIN_DIR=c:\Users\aliss\Documents\sistemahotel

# Linkar os objetos para criar o executável
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

# Compilar main.c para criar main.o
main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Compilar cliente.c para criar cliente.o
cliente.o: $(SRC_DIR)/cliente.c $(SRC_DIR)/cliente.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilar quartos.c para criar quartos.o
quartos.o: $(SRC_DIR)/quartos.c $(SRC_DIR)/quartos.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilar reserva.c para criar reserva.o
reserva.o: $(SRC_DIR)/reserva.c $(SRC_DIR)/reserva.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilar hospedagem.c para criar hospedagem.o
hospedagem.o: $(SRC_DIR)/hospedagem.c $(SRC_DIR)/hospedagem.h
	$(CC) $(CFLAGS) -c -o $@ $<

# Compilar tempo.c para criar tempo.o  
tempo.o: $(SRC_DIR)/tempo.c $(SRC_DIR)/tempo.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

# Comando para limpar os arquivos criados durante a compilação
clean:
	del $(BIN_DIR)\$(EXE) $(OBJ)