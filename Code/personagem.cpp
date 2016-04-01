#include "bibliotecas.h"
#include "personagem.h"
#include "jogo.h"
#include "barra_tempo_progresso.h"
#include "iniciar.h"

void DesenharPersonagem (struct Personagem *Personagem, struct Jogo *Jogo, struct Tempo *Tempo, struct Texturas *Textura){
    glColor4f(1, 1, 1, 1);

    // JOGADOR SE MOVIMENTANDO DIREITA/ESQUERDA
    if ((*Jogo).Jogador_left){
        if ((*Personagem).x > -(*Jogo).largura/2){
            (*Personagem).x -= (*Personagem).movimento;
            (*Personagem).VariacaoSpritePersonagem+=0.1;
            if ((*Personagem).VariacaoSpritePersonagem >= 1)
                (*Personagem).VariacaoSpritePersonagem = 0;
        }
    }
    else if ((*Jogo).Jogador_right){
        if ((*Personagem).x+(*Personagem).largura < (*Jogo).largura/2){
            (*Personagem).x += (*Personagem).movimento;
            (*Personagem).VariacaoSpritePersonagem+=0.1;
            if ((*Personagem).VariacaoSpritePersonagem >= 1)
                (*Personagem).VariacaoSpritePersonagem = 0;
        }
    }

    // PULO DO PERSONAGEM ** IDEIA DESENVOLVIDA EM PARCERIA HUAHAU
    if ((*Personagem).y > (*Jogo).x+(*Tempo).AlturaBarraTempo && (*Personagem).y <= (*Jogo).x+(*Tempo).AlturaBarraTempo+80){
        (*Personagem).y += 6 - (*Personagem).Gravidade_Pulo;
        (*Personagem).Gravidade_Pulo += 0.18;
    }
    if ((*Personagem).y < (*Jogo).x+(*Tempo).AlturaBarraTempo){
        (*Personagem).Gravidade_Pulo = 0;
        (*Personagem).y = (*Jogo).x+(*Tempo).AlturaBarraTempo;
    }
    if ((*Personagem).y >= (*Jogo).x+(*Tempo).AlturaBarraTempo+80){ // CASO ELE CHEGUE NO LIM ESTABELECIDO, CAI.
        (*Personagem).y -= 1;
        (*Jogo).Jogador_up = false;
    }
    // SELECIONA O PERSONAGEM
    switch ((*Personagem).Personagem_Select) {
        case Person1: // CASO PERSONAGEM 1
            if ((*Personagem).StatusPerson == Dead){ // SE ELE MORRER
                (*Personagem).GraudeVariacao = 0.1;
                glBindTexture(GL_TEXTURE_2D, (*Textura).Person1Dead);
                if ((*Tempo).contador%4==0)
                    (*Personagem).VariacaoSpritePersonagem+=0.1;
                if ((*Personagem).VariacaoSpritePersonagem >= 1){
                    (*Personagem).VariacaoSpritePersonagem = 0.9;
                }
            }
            else if ((*Personagem).y > (*Jogo).x + (*Tempo).AlturaBarraTempo){ // SE ELE PULAR
                if ((*Jogo).Jogador_left)
                    glBindTexture(GL_TEXTURE_2D, (*Textura).Person1PuloLeft);
                else
                    glBindTexture(GL_TEXTURE_2D, (*Textura).Person1PuloRight);

                (*Personagem).VariacaoSpritePersonagem = 0;
                (*Personagem).GraudeVariacao = 1;
            }
            else if ((*Jogo).Jogador_left && !(*Jogo).Jogador_up){ // SE ELE FOR PARA O LADO SEM PULAR
                glBindTexture(GL_TEXTURE_2D, (*Textura).Personagem_Move_Esquerda);
                (*Personagem).GraudeVariacao = 0.1;
            }
            else if ((*Jogo).Jogador_right && !(*Jogo).Jogador_up){
                glBindTexture(GL_TEXTURE_2D, (*Textura).Personagem_Move_Direita);
                (*Personagem).GraudeVariacao = 0.1;
            }
            else {
                glBindTexture(GL_TEXTURE_2D, (*Textura).Person1Parado); // SE ESTIVER PARADO
                (*Personagem).VariacaoSpritePersonagem = 0;
                (*Personagem).GraudeVariacao = 1;
            }
            break;

        case Person2:
            if ((*Personagem).StatusPerson == Dead){
                (*Personagem).GraudeVariacao = 0.1;
                glBindTexture(GL_TEXTURE_2D, (*Textura).Person2Dead);
                if ((*Tempo).contador%4==0)
                    (*Personagem).VariacaoSpritePersonagem+=0.1;
                if ((*Personagem).VariacaoSpritePersonagem >= 1){
                    (*Personagem).VariacaoSpritePersonagem = 0.9;
                }
            }
            else if ((*Personagem).y > (*Jogo).x + (*Tempo).AlturaBarraTempo){
                if ((*Jogo).Jogador_left)
                    glBindTexture(GL_TEXTURE_2D, (*Textura).Person2PuloLeft);
                else
                    glBindTexture(GL_TEXTURE_2D, (*Textura).Person2PuloRight);

                (*Personagem).VariacaoSpritePersonagem = 0;
                (*Personagem).GraudeVariacao = 1;
            }
            else if ((*Jogo).Jogador_left){
                glBindTexture(GL_TEXTURE_2D, (*Textura).Personagem2_Move_Esquerda);
                (*Personagem).GraudeVariacao = 0.1;
            }
            else if ((*Jogo).Jogador_right){
                glBindTexture(GL_TEXTURE_2D, (*Textura).Personagem2_Move_Direita);
                (*Personagem).GraudeVariacao = 0.1;
            }
            else {
                glBindTexture(GL_TEXTURE_2D, (*Textura).Person2Parado);
                (*Personagem).VariacaoSpritePersonagem = 0;
                (*Personagem).GraudeVariacao = 1;
            }
            break;
    }

    glPushMatrix();
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glTranslatef((*Personagem).x, (*Personagem).y, (*Personagem).z);
    glBegin(GL_POLYGON);
        glTexCoord2f((*Personagem).VariacaoSpritePersonagem, 0); glVertex3f(0, 0, 0);
        glTexCoord2f((*Personagem).VariacaoSpritePersonagem+(*Personagem).GraudeVariacao, 0); glVertex3f((*Personagem).largura, 0, 0);
        glTexCoord2f((*Personagem).VariacaoSpritePersonagem+(*Personagem).GraudeVariacao, 1); glVertex3f((*Personagem).largura, (*Personagem).altura, 0);
        glTexCoord2f((*Personagem).VariacaoSpritePersonagem, 1); glVertex3f(0, (*Personagem).altura, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();
}

void DesenharVida (int x, struct Texturas *Textura){
    glColor4f(1, 1, 1, 1); // desenha os coracões respectivos das vidas
    glPushMatrix();
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, (*Textura).Coracao_vida);
    glEnable(GL_TEXTURE_2D);
    glTranslatef(x, 250, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0); glVertex3f(30, 0, 0);
        glTexCoord2f(1, 1); glVertex3f(30, 30, 0);
        glTexCoord2f(0, 1); glVertex3f(0, 30, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();
}

