////////////////////////////////////////////
//// TRABALHO PŔATICO 01 - CG CEFET/MG /////
////   DESENVOLVIDO POR TULIO ASSIS    /////
////        SEGUE ARQUIVO README        ////
////////////////////////////////////////////
    // Alterar no "bibliotecas.h" //
#include "bibliotecas.h"
#include "iniciar.h"
#include "personagem.h"
#include "jogo.h"
#include "barra_tempo_progresso.h"
#include "cenarios.h"
#include "inimigos.h"
#include "powerup.h"

const int Quantidade_de_Objetos = 10;
const int Quantidade_de_Monstrao = 1;
const int Quantidade_de_PowerUP = 1;

struct Personagem Personagem;
struct Texturas Textura;
struct Jogo Jogo;
struct Tempo Tempo;
struct objetos Objeto;
struct objetos Fogueiras;
struct objetos Objetos[Quantidade_de_Objetos];
struct objetos Monstrao[Quantidade_de_Monstrao];
struct objetos PowerUp[Quantidade_de_PowerUP];

void MoverSpecial (int key, int x, int y){
    switch (Jogo.StatusGame){
        case Game:
            if (Personagem.StatusPerson != Dead){ // só poderar mover se não estiver morto
                if (key == GLUT_KEY_RIGHT)
                    Jogo.Jogador_right = true;
                if (key == GLUT_KEY_LEFT)
                    Jogo.Jogador_left = true;
                if (key == GLUT_KEY_UP)
                    Jogo.Jogador_up = true;
            }
            break;
        case Menu:
            if (key == GLUT_KEY_UP){
                if (Jogo.VariacaoMenuSprite <= 0)
        	       Jogo.VariacaoMenuSprite = 1;
                Jogo.VariacaoMenuSprite-=0.25;
            }
            if (key == GLUT_KEY_DOWN){
                Jogo.VariacaoMenuSprite+=0.25;
                if (Jogo.VariacaoMenuSprite >= 1)
                    Jogo.VariacaoMenuSprite = 0;
            }
            break;
        case SelecaodoPersonagem:
            if (key == GLUT_KEY_LEFT){
                if (Personagem.VariacaoSpriteSelecionarPersonagem <= 0)
                    Personagem.VariacaoSpriteSelecionarPersonagem = 1;
                Personagem.VariacaoSpriteSelecionarPersonagem-=0.5;
            }
            if (key == GLUT_KEY_RIGHT){
                Personagem.VariacaoSpriteSelecionarPersonagem+=0.5;
                if (Personagem.VariacaoSpriteSelecionarPersonagem >= 1)
                    Personagem.VariacaoSpriteSelecionarPersonagem = 0;
            }
            break;
        default:
            break;
    }
}

void MoverSpecialOcioso (int key, int x, int y){
    if (Jogo.StatusGame == Game){
        if (key == GLUT_KEY_RIGHT)
            Jogo.Jogador_right = false;
        if (key == GLUT_KEY_LEFT)
            Jogo.Jogador_left = false;
        if (key == GLUT_KEY_UP){
            Jogo.Jogador_up = false;
            if (Jogo.Som)
                Jogo.MusicPulo.play();
        }
    }
}

void Tecla (unsigned char key, int x, int y){
    switch(Jogo.StatusGame){
        case SairJogo:
            if (key == 13) // Pede confirmação do usuario, se "enter", sai, caso contrario, volta ao jogo.
                Jogo.StatusGame = Sair_Confirmada;
            else if (key == 27)
                Jogo.StatusGame = Game;
            break;
        case Reiniciar: // Pede confirmação do usuário, caso sim, reinicia.
            if (key == 13)
                Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
            else if (key == 27)
                Jogo.StatusGame = Game;
            Jogo.StatusGame = Game;
            break;
        case Menu:
            if (key == 13 && Jogo.VariacaoMenuSprite == 0) // 0, 0.25, 0.5, e 0.75 são as variaçoes da sprite menu;
			    Jogo.StatusGame = SelecaodoPersonagem;
            else if (key == 13 && Jogo.VariacaoMenuSprite == 0.25)
                Jogo.StatusGame = Configuracao;
            else if (key == 13 && Jogo.VariacaoMenuSprite == 0.5)
                Jogo.StatusGame = Creditos;
            else if (key == 13 && Jogo.VariacaoMenuSprite == 0.75)
                Jogo.StatusGame = SairMenu;
            break;
        case SelecaodoPersonagem:
            if (key == 13 && Personagem.VariacaoSpriteSelecionarPersonagem == 0){
                Personagem.Personagem_Select = Person1;
  				Jogo.StatusGame = IniciarGame;
            }
  			else if (key == 13 && Personagem.VariacaoSpriteSelecionarPersonagem == 0.5){
                Personagem.Personagem_Select = Person2;
                Jogo.StatusGame = IniciarGame;
            }
            break;
        case Game:
            if (key == 'p' || key == 'P')
                Jogo.StatusGame = Pause;
            if (key == 'r' || key == 'R')
                Jogo.StatusGame = Reiniciar;
            if (key == 27)
                Jogo.StatusGame = SairJogo;
            if (key == '-')
            	Personagem.QuantidadeVidas --;
           if (key == '+')
           	Tempo.Tempo_Decorrido++;
            break;
        case Pause:
            if (key == 'p' || key == 'P')
                Jogo.StatusGame = Game;
            break;
        case Creditos:
            if (key == 27)
                Jogo.StatusGame = Menu;
            break;
        case Configuracao:
            if (key == 27)
                Jogo.StatusGame = Menu;
            if (key == 'f' || key == 'F')
                glutFullScreen();
            if (key == 's' || key == 's'){
                if (Jogo.Som){
                    Jogo.MusicMenu.stop();
                    Jogo.Som = false;
                }
                else{
                    Jogo.MusicMenu.play();
                    Jogo.Som = true;
                }
            }
            break;
        case SairMenu:
            if (key == 13)
                Jogo.StatusGame = Sair_Confirmada;
            else if (key == 27)
                Jogo.StatusGame = Menu;
            break;
        case Venceu:
            if (key == 13){
                Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
                Jogo.StatusGame = Menu;
            }
            else if (key == 27){
                Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
                Jogo.StatusGame = SairMenu;
            }
            break;
        case Perdeu:
            if (key == 13){
                Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
                Jogo.StatusGame = Menu;
            }
            else if (key == 27){
                Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
                Jogo.StatusGame = SairMenu;
            }
            break;
        default:
            break;
    }
}

void DesenharCena (){
    int Vidas_Cordx = 100; // Coordenada para iniciar os desenhos dos coracoes
    glClear(GL_COLOR_BUFFER_BIT);
    switch (Jogo.StatusGame){
        case Iniciando:
            DesenharCenario(&Jogo, &Textura.Iniciando);
            break;
        case IniciarGame: // Desenha contagem regressiva
            DesenharCenarioComSprite(&Jogo, &Textura.Contagem_Regressiva, 0.25, &Jogo.ContagemRegressivaSprite);
            break;
        case Menu: // desenha menu
            DesenharCenarioComSprite(&Jogo, &Textura.Menu, 0.25, &Jogo.VariacaoMenuSprite);
                break;
        case SelecaodoPersonagem: //desenha selecao do personagem
            DesenharCenarioComSprite(&Jogo, &Textura.Selecionar_Personagem, 0.5, &Personagem.VariacaoSpriteSelecionarPersonagem);
            break;
        case Pause:
            DesenharCenario(&Jogo, &Textura.Pause);
            break;
        case Game:
            DesenharCenario(&Jogo, &Jogo.Fundo);
            DesenharPersonagem(&Personagem, &Jogo, &Tempo, & Textura);
            DesenharTempo (&Jogo, &Tempo, &Objeto);
            DesenharBarraProgressoPowerUp(&Tempo, &Objeto);
            DesenharObjeto(&Textura, Objetos, Quantidade_de_Objetos);
            DesenharMonstrao(&Tempo, &Textura, Monstrao, Quantidade_de_Monstrao);
            DesenharPowerUp(&Tempo, &Objeto, &Textura, PowerUp, Quantidade_de_PowerUP);
            DesenharFogueira(&Tempo, &Textura, &Fogueiras, &Jogo, &Personagem);

            for (int i=0; i<Personagem.QuantidadeVidas; i++, Vidas_Cordx+=40)
                DesenharVida(Vidas_Cordx, &Textura);
            break;
        case Creditos:
            DesenharCenario(&Jogo, &Textura.Creditos);
            break;
        case Configuracao:
            DesenharCenario(&Jogo, &Textura.Configuracao);
            break;
        case Venceu:
            DesenharCenario(&Jogo, &Textura.Win);
            break;
        case Perdeu:
            DesenharCenario(&Jogo, &Textura.Gameover);
            break;
        case SairJogo:
            DesenharCenario(&Jogo, &Textura.Confirmacao_Saida);
            break;
        case SairMenu:
            DesenharCenario(&Jogo, &Textura.Confirmacao_Saida);
            break;
        case Reiniciar:
            DesenharCenario(&Jogo, &Textura.Confirmacao_Reiniciar);
            break;
        case Reiniciar_Confirmada:
            Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
            Jogo.StatusGame =  Game;
            break;
    	case Sair_Confirmada:
            exit(0);
    	    break;
        default:
            break;
    }
    glutSwapBuffers();
}

void Iniciar(){
    glClearColor(0, 0, 0, 0.0);
    Jogo.Som = true;
    Iniciar_Texturas_Sound(&Textura, &Jogo);
    Instanciar(&Jogo, &Personagem, &Tempo, &Objeto, &Fogueiras, Objetos, Monstrao, PowerUp, &Textura, Quantidade_de_Monstrao, Quantidade_de_Objetos, Quantidade_de_PowerUP);
}

void AtualizaCena (int idx){
    if (Jogo.StatusGame == Game){
        if (!Tempo.Tempo_Decorrido && Jogo.Som){
            Jogo.MusicGame.play();
            Jogo.MusicCarregando.stop();
        }

        MoverObjetos(&Personagem, &Tempo, &Jogo, &Textura, Objetos, &Objeto, Quantidade_de_Objetos);
        MoverMonstrao(&Tempo, Monstrao, &Jogo, &Personagem, Quantidade_de_Monstrao);
        MoverPowerUp(&Tempo, &Objeto, PowerUp, &Personagem, &Jogo, Quantidade_de_PowerUP);

        Tempo.contador++; //Soma +1 a cada milisegundo
        if (Tempo.contador >= 100){ // 100 vezes que passar por aqui terá 1 segundo decorrido
            Tempo.Tempo_Decorrido++; // Soma +1 a cada segundo
            Tempo.contador = 0;
            if (Personagem.StatusPerson == Invencivel) //Conta o tempo de invencibilidade caso o personagem seja atingido por um objeto
                Personagem.TimeInvencivel++;
        }

        if (Personagem.StatusPerson == Invencivel){
            if (Personagem.z == 2)
                Personagem.z = 4; //Some da Tela, sendo que z está definido -3 <= z <=3 e fica alternando (piscando)
            else
                Personagem.z = 2;

            if (Personagem.TimeInvencivel == 3){ //Ao completar o tempo de 3 segundos invencivel, volta ao normal
                Personagem.movimento = 5;
                Personagem.StatusPerson = Normal;
                Personagem.TimeInvencivel = 0;
                Personagem.z = 2;
            }
        }
    }

    else if (Jogo.StatusGame == IniciarGame || Jogo.StatusGame == Iniciando){ //Etapa que mostra na tela a contagem regressiva de inicio do game
        if (!Tempo.contador){
            if (Jogo.Som)
                Jogo.MusicCarregando.play();
            Jogo.MusicMenu.stop();
        }
        Tempo.contador++;
        if (Tempo.contador >= 100){
            Tempo.contador = 0;
            Jogo.ContagemRegressivaSprite += 0.25;
            if (Jogo.ContagemRegressivaSprite == 1){
                Jogo.ContagemRegressivaSprite = 0;
                if (Jogo.StatusGame == IniciarGame)
                    Jogo.StatusGame = Game;
                else
                    Jogo.StatusGame = Menu;
            }
        }
    }
    else if (Jogo.StatusGame == Menu){
        if (!Tempo.contador){
            Jogo.MusicCarregando.stop();
            Tempo.contador++;
            if (Jogo.Som)
               Jogo.MusicMenu.play();
        }
    }

    if (Tempo.Tempo_Decorrido == Tempo.Tempo_Total*0.5 && Tempo.ControleAumentodeMovimentoLvl2){ // Verifica se começou Fase 2
        Jogo.Fundo = Textura.Fundo_Cenario2;
        Jogo.MusicGame.setPitch(1.4); // aumenta velocidade do som
        Tempo.ControleAumentodeMovimentoLvl2 = false;
        for (int i = 0; i < Quantidade_de_Objetos; i++) // Atribui valores aleatórios as Bombas
            Objetos[i].movimento = 1+rand()%6;
    }

    if (Tempo.Tempo_Total == Tempo.Tempo_Decorrido && Personagem.StatusPerson != Dead && Jogo.StatusGame != Perdeu){ //Caso ele não morra até o final, WIN! =D
        Jogo.StatusGame = Venceu;
        Jogo.MusicGame.stop();
    }

    if (Personagem.QuantidadeVidas == 0){ // Caso perca todas as vidas... x|
        if (Jogo.Som)
            Jogo.MusicGameOver.play();
        Jogo.MusicCarregando.stop();
        Jogo.MusicGame.stop();
        Personagem.StatusPerson = Dead;
        Personagem.y = Jogo.y+Tempo.AlturaBarraTempo;
        Personagem.Tempo_de_Morte = Tempo.Tempo_Decorrido; //Guarda-se o tempo de morte para animação "Dead"
        Personagem.VariacaoSpritePersonagem = 0;
        Personagem.z = 3;

        Personagem.QuantidadeVidas = -1;
    }

    if (Personagem.Tempo_de_Morte+3 == Tempo.Tempo_Decorrido && Personagem.Tempo_de_Morte != 0){ //Se passar três segundos mostra tela Gameover
        Jogo.StatusGame = Perdeu;
    }

    if (Jogo.StatusGame == Game && Jogo.Jogador_up){ //Altera o y do personagem (PULO)
        Personagem.y++;
        Personagem.Gravidade_Pulo = 1.5;
    }

  glutPostRedisplay();
  glutTimerFunc(10, AtualizaCena, 0);
}

void Redimensionar(int NewWidth, int NewHeight){
    float RazaoAspecto = (float)NewWidth/NewHeight;

    glViewport(0, 0, NewWidth, NewHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(RazaoAspecto*Jogo.x, RazaoAspecto*-Jogo.x, Jogo.y, -Jogo.y, -3.0, 3.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv){
    srand(time(0));
    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Ta chovendo bombas!");
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Iniciar();
    glutDisplayFunc(DesenharCena);
    glutReshapeFunc(Redimensionar);

    glutKeyboardFunc(Tecla);
    glutSpecialFunc(MoverSpecial);
    glutSpecialUpFunc(MoverSpecialOcioso);

    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR); // Muda desenhinho do mouse

    glutTimerFunc(0, AtualizaCena, 0);
    glutMainLoop();
    return 0;
}
