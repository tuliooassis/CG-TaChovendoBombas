#include "bibliotecas.h"
#include "barra_tempo_progresso.h"
#include "jogo.h"
#include "inimigos.h"
void DesenharTempo (struct Jogo *Jogo, struct Tempo *Tempo, struct objetos *Objeto){
    glColor4f(1, 1, 1, 0.5);
    glPushMatrix();
    glEnable(GL_BLEND);
    glTranslatef((*Jogo).x, (*Jogo).y, 1);
    glBegin(GL_POLYGON);
        glVertex3f(0, 0, 0);
        glVertex3f((*Jogo).largura, 0, 0);
        glVertex3f((*Jogo).largura, (*Tempo).AlturaBarraTempo, 0);
        glVertex3f(0, (*Tempo).AlturaBarraTempo, 0);
    glEnd();
    glDisable(GL_BLEND);
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glTranslatef((*Jogo).x, (*Jogo).y, 2);
    glBegin(GL_POLYGON);
        glVertex3f(0, 0, 0);
        glVertex3f(((*Jogo).largura/(*Tempo).Tempo_Total*(*Tempo).Tempo_Decorrido), 0, 0);
        glVertex3f(((*Jogo).largura/(*Tempo).Tempo_Total*(*Tempo).Tempo_Decorrido), (*Tempo).AlturaBarraTempo, 0);
        glVertex3f(0, (*Tempo).AlturaBarraTempo, 0);
    glEnd();
    glPopMatrix();
}

void DesenharBarraProgressoPowerUp (struct Tempo *Tempo, struct objetos *Objeto){
    if ((*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.2f){
        glColor4f(1, 1, 1, 0.5);
        glPushMatrix();
        glEnable(GL_BLEND);
        glTranslatef(250, 50, 2);
        glBegin(GL_POLYGON); // Desenha a barra no fundo
            glVertex3f(0, 0, 0);
            glVertex3f(30, 0, 0);
            glVertex3f(30, 200, 0);
            glVertex3f(0, 200, 0);
        glEnd();
        glDisable(GL_BLEND);
        glPopMatrix();

        glColor3f(0, 0, 1);
        glPushMatrix();
        glTranslatef(250, 50, 2);
        glBegin(GL_POLYGON); // Desenha o progresso
            glVertex3f(0, 0, 0);
            glVertex3f(30, 0, 0);
            glVertex3f(30, (200/(*Objeto).QuantidadeObjetosDesviarParaGanharPowerUP*(*Objeto).Objetos_Desviados), 0);
            glVertex3f(0, (200/(*Objeto).QuantidadeObjetosDesviarParaGanharPowerUP*(*Objeto).Objetos_Desviados), 0);
        glEnd();
        glPopMatrix();
    }
}
