CC = g++
OPCOES_COMPILADOR= -lglut -lGLU -lGLEW -lGL -lSOIL -lsfml-audio -lGL
TODOS_ARQUIVOS_PONTOH = barra_tempo_progresso.h bibliotecas.h bibliotecas_linux.h bibliotecas_windows.h cenarios.h iniciar.h inimigos.h jogo.h personagem.h powerup.h
TODOS_ARQUIVOS_OBJ = main.o barra_tempo_progresso.o cenarios.o iniciar.o inimigos.o personagem.o powerup.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run:  all
	./main

install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsoil-dev
	sudo apt-get install libsfml-dev

clean:
	# Arquivos Apagados!
	rm *.o main
