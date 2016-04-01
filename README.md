# CG - Trabalho Prático 01
#### Tá Chovendo ~~{PARADAS}~~ Bombas

 Desenvolvido por: **Túlio Assis** :+1:
## Itens Necessários
 - Freeglut **sudo apt-get install freeglut3-dev**

 - Glew **sudo apt-get install libglew1.6-dev**

 - Soil **sudo apt-get install libsoil-dev**

 - [SFML (áudio)](http://www.sfml-dev.org/)  **sudo apt-get install libsfml-dev**


## Instruções para compilação e execução
 - Codeblocks
> Ao abrir o projeto, selecione o sistema operacional.
> Logo após vá em bibliotecas.h e selecione a biblioteca.

 - Linux **(Terminal)**
> Abra o terminal e vá na pasta raiz do TP
> Faça uso dos seguintes comandos:
> - make install: instalar bibliotecas listadas acimas
> - make all: compilar
> - make run: rodar
> - make clean: limpar os arquivos criados

## The Game
- Mova o personagem com as setas  (Pulo ↑) (Andar ← → )
- ESC sai do jogo
- R reinicia
- O personagem começa com 3 vidas e se continuar vivo até o final do tempo vence!

## Screenshot
> Segue mais na pasta [Screenshot](./Screenshot).

![alt tag](https://github.com/tuliooassis/CG-TaChovendoBombas/blob/master/Screenshot/1%20Tela%20inicial.png)
![alt tag](https://github.com/tuliooassis/CG-TaChovendoBombas/blob/master/Screenshot/3%20Selecionar%20Personagem.png)
![alt tag](https://github.com/tuliooassis/CG-TaChovendoBombas/blob/master/Screenshot/5%20Pulo.png)
![alt tag](https://github.com/tuliooassis/CG-TaChovendoBombas/blob/master/Screenshot/7%20Fase%202.png)

## Itens Implementados
### Adicionais
> - Texturas animadas

>> - Personagem andando
>> - Personagem morrendo
>> - Objetos explodindo

> - Tipos de Objetos / Objetos espertos / Power-ups

>> - Bomba (comum): cai em velocidade constante
>> - TNT (chefão): persegue o jogador
>> - Fogueira (comum): anda no chão (fogueira anda?)
>> - Flash (power-up): o jogador pode ganhar vida ou velocidade e ele desce na diagonal

> - Salto do personagem (↑)
> - Manter razão de aspecto (créditos prof =D)
> - Fases: existem duas fases, uma somente com bombas, e outra com fogueira e TNT
> - Telas: Loading, Menu, Configurações, Créditos, Gameover, Pause, Contagem Regressiva, Win, outras
> - Sons

## Bibliografia
Sons: [SoundBible](http://soundbible.com/tags-game.html)

Algumas sprites: [GameArt2D](http://www.gameart2d.com)

E outras imagens aleatórias na internet.
