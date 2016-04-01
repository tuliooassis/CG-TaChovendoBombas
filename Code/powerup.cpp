#include "bibliotecas.h"
#include "powerup.h"
#include "inimigos.h"
#include "barra_tempo_progresso.h"
#include "iniciar.h"
#include "jogo.h"
#include "personagem.h"

void DesenharPowerUp (struct Tempo *Tempo, struct objetos *Objeto, struct Texturas *Textura, struct objetos PowerUp[], int Quantidade_de_PowerUP){
    int i;
    if ((*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.2f && (*Objeto).PowerUpSIM){ // O Jogador terá a capacidade de receber powerup's após 20% do tempo percorrido
        (*Objeto).Objetos_Desviados = 0;
        glColor4f(1, 1, 1, 1);
        for (i=0; i<Quantidade_de_PowerUP; i++){
            glPushMatrix();
            glEnable(GL_BLEND);
            glEnable(GL_TEXTURE_2D);
            glTranslatef(PowerUp[i].x, PowerUp[i].y, 2);
            glBindTexture(GL_TEXTURE_2D, (*Textura).PowerUp);
            glBegin(GL_POLYGON);
                glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
                glTexCoord2f(1, 0); glVertex3f(PowerUp[i].largura, 0, 0);
                glTexCoord2f(1, 1); glVertex3f(PowerUp[i].largura, PowerUp[i].altura, 0);
                glTexCoord2f(0, 1); glVertex3f(0, PowerUp[i].altura, 0);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            glPopMatrix();
        }
    }
}

void MoverPowerUp (struct Tempo *Tempo, struct objetos *Objeto, struct objetos PowerUp[], struct Personagem *Personagem, struct Jogo *Jogo, int Quantidade_de_PowerUP){
    srand(time(0));
    if ((*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.2f && (*Objeto).PowerUpSIM){
        for (int i=0; i<Quantidade_de_PowerUP; i++){ // O PowerUp tem um movimento diferente, por se tratar de um "raio", ele se movimenta
            if (PowerUp[i].x >= (*Jogo).largura/2-20)   // na diagonal.
                PowerUp[i].AndarPraDireitaouEsquerda *= -1;
            else if (PowerUp[i].x <= -(*Jogo).largura/2+20)
                PowerUp[i].AndarPraDireitaouEsquerda *= -1;

                PowerUp[i].y -= PowerUp[i].movimento;
                PowerUp[i].x += PowerUp[i].movimento*PowerUp[i].AndarPraDireitaouEsquerda;

            if (PowerUp[i].y < (*Jogo).x+(*Tempo).AlturaBarraTempo){
                (*Objeto).PowerUpSIM = false; // Ele fica "desabilitado" até ser atingido o numero de objetos desviados necessários;
                do {
                    PowerUp[i].x = (*Jogo).x + rand()%600 - i*10; // valores aleatórios
                } while (PowerUp[i].x <= -200 && PowerUp[i].x+PowerUp[i].altura <= 200);
                PowerUp[i].y = 300 + rand()%1000 + i*10;
            }
            if ((*Personagem).StatusPerson == Normal && (*Personagem).y <= PowerUp[i].y+PowerUp[i].altura && (*Personagem).y+(*Personagem).altura  >= PowerUp[i].y && (((*Personagem).x >= PowerUp[i].x && (*Personagem).x <= PowerUp[i].x+PowerUp[i].largura) || ((*Personagem).x+(*Personagem).largura  >= PowerUp[i].x && (*Personagem).x+(*Personagem).largura  <= PowerUp[i].x+PowerUp[i].largura))){
                (*Objeto).PowerUpSIM = false; // caso houver a colisão
                do {
                    PowerUp[i].x = (*Jogo).x + rand()%600 - i*10;
                } while (PowerUp[i].x <= -200 && PowerUp[i].x+PowerUp[i].altura <= 200);
                PowerUp[i].y = 300 + rand()%1000 + i*10;
                if ((*Jogo).Som)
                    (*Jogo).MusicPowerUP.play(); // Play som do PowerUp

                if (rand()%2) // aleatóriamente se esse valor for maior que 0, aumenta no movimento, se não aumenta na vida.
                    (*Personagem).movimento = 10;  // entretanto ele sempre ficará "invencivel" como brinde haha
                else if ((*Personagem).QuantidadeVidas <= 5){
                    (*Personagem).QuantidadeVidas++;
                }
                (*Personagem).StatusPerson = Invencivel;
            }
        }
    }
}
