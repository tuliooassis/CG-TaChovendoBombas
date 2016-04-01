#include "bibliotecas.h"
#include "cenarios.h"
#include "jogo.h"
void DesenharCenarioComSprite (struct Jogo *Jogo, GLint *Textura, float Variacao_Textura, float *Valor_Textura_Atual){
    glColor3f(1, 1, 1); // Função que desenha cenários que tenham sprite.
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, *Textura);
    glEnable(GL_TEXTURE_2D);
    glTranslatef((*Jogo).x, (*Jogo).y, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(*Valor_Textura_Atual, 0);     glVertex3f(0, 0, 0);
        glTexCoord2f(*Valor_Textura_Atual+Variacao_Textura, 0); glVertex3f((*Jogo).largura, 0, 0);
        glTexCoord2f(*Valor_Textura_Atual+Variacao_Textura, 1); glVertex3f((*Jogo).largura, (*Jogo).altura, 0);
        glTexCoord2f(*Valor_Textura_Atual, 1);     glVertex3f(0, (*Jogo).altura, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void DesenharCenario(struct Jogo *Jogo, GLint *ImagemTextura){
    glColor4f(1, 1, 1, 1);  // função que desenha cenários que não tenham sprite.
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, *ImagemTextura); //e.g. Textura.Pause
    glEnable(GL_TEXTURE_2D);
    glTranslatef((*Jogo).x, (*Jogo).y, 1);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0); glVertex3f((*Jogo).largura, 0, 0);
        glTexCoord2f(1, 1); glVertex3f((*Jogo).largura, (*Jogo).altura, 0);
        glTexCoord2f(0, 1); glVertex3f(0, (*Jogo).altura, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


