#include "bibliotecas.h"
#include "inimigos.h"
#include "iniciar.h"
#include "jogo.h"
//#include "inimigos.h"
#include "barra_tempo_progresso.h"
#include "personagem.h"

void DesenharObjeto (struct Texturas *Textura, struct objetos Objetos[], int Quantidade_de_Objetos){
                        // DESENHA O OBJETO BOMBA PADRAO EM SITUAÇÃO NORMAL E SITUAÇÃO EXPLOSAO
                        // NO CASO, ESTOU TRATANDO OS OBJETOS COMO INFINITOS, OU SEJA, SÃO CRIADOS UMA QUANTIDADE ESPECÍFICA DE OBJETOS
                        // E COM A EXPLOSAO DELES, ELES RESSURGEM NOVAMENTE, ISTO ATÉ O FINAL DO TEMPO.
    glColor4f(1, 1, 1, 1);
    for (int i=0; i<Quantidade_de_Objetos; i++){
        glPushMatrix();
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        if (Objetos[i].StatusObjeto == Explodido){
            glBindTexture(GL_TEXTURE_2D, (*Textura).Explosao);
            glTranslatef(Objetos[i].x, Objetos[i].y, 1);
            glBegin(GL_POLYGON);
                glTexCoord2f(Objetos[i].SpriteExplosao, 0); glVertex3f(0, 0, 0);
                glTexCoord2f(Objetos[i].SpriteExplosao+0.1, 0); glVertex3f(Objetos[i].largura, 0, 0);
                glTexCoord2f(Objetos[i].SpriteExplosao+0.1, 1); glVertex3f(Objetos[i].largura, Objetos[i].altura, 0);
                glTexCoord2f(Objetos[i].SpriteExplosao, 1); glVertex3f(0, Objetos[i].altura, 0);
        }
        else{
            glBindTexture(GL_TEXTURE_2D, (*Textura).Bomb);
            glTranslatef(Objetos[i].x, Objetos[i].y, 1);
            glBegin(GL_POLYGON);
                glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
                glTexCoord2f(1, 0); glVertex3f(Objetos[i].largura, 0, 0);
                glTexCoord2f(1, 1); glVertex3f(Objetos[i].largura, Objetos[i].altura, 0);
                glTexCoord2f(0, 1); glVertex3f(0, Objetos[i].altura, 0);
        }
        glEnd();
        glPopMatrix();
        if (Objetos[i].StatusObjeto == Explodido){ // CASO FOR EXPLODIDO, VARIA A SPRITE DE EXPLOSAO E VOLTA A SER "VIVO"
            Objetos[i].SpriteExplosao += 0.1; // 1 (tamanho da sprite) dividido por 10 (qtde de imagens na sprite)
            if (Objetos[i].SpriteExplosao > 1){
                Objetos[i].SpriteExplosao = 0;
                Objetos[i].StatusObjeto = Vivo;
            }
        }
    }
}

void MoverObjetos (struct Personagem *Personagem, struct Tempo *Tempo, struct Jogo *Jogo, struct Texturas *Textura, struct objetos Objetos[], struct objetos *Objeto, int Quantidade_de_Objetos){
    srand(time(0));
    int i;
    for (i=0; i<Quantidade_de_Objetos; i++){
        Objetos[i].y -= Objetos[i].movimento;
        if (Objetos[i].y < (*Jogo).x+(*Tempo).AlturaBarraTempo+20) // CASO O OBJETO ESTEJA UM POUCO ACIMA DA BARRA, JÁ É EXPLODIDO
            Objetos[i].StatusObjeto = Explodido;


        if (Objetos[i].y < (*Jogo).x+(*Tempo).AlturaBarraTempo){ // Caso o Objeto colida com a terra
            if ((*Jogo).Som)
                (*Jogo).MusicExplosao.play(); // Play som da explosao
            if ((*Jogo).StatusGame == Game && !(*Objeto).PowerUpSIM && (*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.2) //Só irá contar como objeto desviado na barra de progresso caso não tenha sido criado nenhum powerup ainda.
                (*Objeto).Objetos_Desviados++;
            if ((*Objeto).Objetos_Desviados == (*Objeto).QuantidadeObjetosDesviarParaGanharPowerUP){ // caso o num de objeto seja igual ao específicado para criar powerup's
                (*Objeto).PowerUpSIM = true;
                (*Objeto).Objetos_Desviados = 0;
            }
            do { // se entrou aqui é porque colidiu, então gera um novo x e y para o respectivo objeto
                Objetos[i].x = (*Jogo).x + rand()%600 - i*10; // valores bom aleatórios
            } while (Objetos[i].x <= -300 && Objetos[i].x+100 <= 200);
            Objetos[i].y = 300 + rand()%1000 + i*10;
        }
        if ((*Personagem).StatusPerson == Normal && (*Personagem).y <= Objetos[i].y+Objetos[i].altura &&
            (*Personagem).y+(*Personagem).altura  >= Objetos[i].y &&
            (((*Personagem).x >= Objetos[i].x && (*Personagem).x <= Objetos[i].x+Objetos[i].largura) ||
            ((*Personagem).x+(*Personagem).largura  >= Objetos[i].x && (*Personagem).x+(*Personagem).largura  <= Objetos[i].x+Objetos[i].largura))){
            Objetos[i].StatusObjeto = Explodido; // if de colisao com o personagem
            (*Personagem).QuantidadeVidas--;
            (*Personagem).StatusPerson = Invencivel;
            if ((*Jogo).Som)
                (*Jogo).MusicExplosao.play(); // Play som da explosao
        }
    }
}

void DesenharFogueira (struct Tempo *Tempo, struct Texturas *Textura, struct objetos *Fogueiras, struct Jogo *Jogo, struct Personagem *Personagem){
    glColor4f(1, 1, 1, 1);
    if ((*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.5f){ // Objeto do Fase2, que corresponde a metade do tempo específicado
        glPushMatrix();
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (*Textura).Fogueira);
        glTranslatef((*Fogueiras).x, (*Fogueiras).y, 1);
        glBegin(GL_POLYGON);
            glTexCoord2f((*Fogueiras).VariacaoSprite, 0); glVertex3f(0, 0, 0);
            glTexCoord2f((*Fogueiras).VariacaoSprite+0.125, 0); glVertex3f((*Fogueiras).largura, 0, 0);
            glTexCoord2f((*Fogueiras).VariacaoSprite+0.125, 1); glVertex3f((*Fogueiras).largura, (*Fogueiras).altura, 0);
            glTexCoord2f((*Fogueiras).VariacaoSprite, 1); glVertex3f(0, (*Fogueiras).altura, 0);
        glEnd();
        glPopMatrix();
        (*Fogueiras).x++;

        if ((*Tempo).contador%4 == 0){ // o %4 foi aleatório.
            (*Fogueiras).VariacaoSprite += 0.125;
            if ((*Fogueiras).VariacaoSprite >= 1)
                (*Fogueiras).VariacaoSprite = 0;
        }

        if ((*Fogueiras).x + (*Fogueiras).largura >= (*Jogo).largura/2) // largura/2 significa 300, extremo lado direito da tela.
                (*Fogueiras).x = (*Jogo).x;

        if ((*Personagem).StatusPerson == Normal && (*Personagem).y <= (*Fogueiras).y+(*Fogueiras).altura &&
        (((*Personagem).x >= (*Fogueiras).x && (*Personagem).x <= (*Fogueiras).x+(*Fogueiras).largura) ||
        ((*Personagem).x+(*Personagem).largura  >= (*Fogueiras).x && (*Personagem).x+(*Personagem).largura  <= (*Fogueiras).x+(*Fogueiras).largura))){
            (*Personagem).QuantidadeVidas--; // Colisao da fogueira com personagem
            (*Personagem).StatusPerson = Invencivel;
            (*Fogueiras).x = (*Jogo).x;
        }
    }
}

void DesenharMonstrao (struct Tempo *Tempo, struct Texturas *Textura, struct objetos Monstrao[], int Quantidade_de_Monstrao){
    int i;
    if ((*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.5f){ // Se Fase2, comentários parecidos com o DesenharObjetos..
        glColor4f(1, 1 , 1, 1);
        for (i=0; i<Quantidade_de_Monstrao; i++){
            glPushMatrix();
            glEnable(GL_BLEND);
            glEnable(GL_TEXTURE_2D);
            if (Monstrao[i].StatusObjeto == Explodido){
                glBindTexture(GL_TEXTURE_2D, (*Textura).Explosao);
                glTranslatef(Monstrao[i].x, Monstrao[i].y, 1);
                glBegin(GL_POLYGON);
                    glTexCoord2f(Monstrao[i].SpriteExplosao, 0); glVertex3f(0, 0, 0);
                    glTexCoord2f(Monstrao[i].SpriteExplosao+0.1, 0); glVertex3f(Monstrao[i].largura, 0, 0);
                    glTexCoord2f(Monstrao[i].SpriteExplosao+0.1, 1); glVertex3f(Monstrao[i].largura, Monstrao[i].altura, 0);
                    glTexCoord2f(Monstrao[i].SpriteExplosao, 1); glVertex3f(0, Monstrao[i].altura, 0);
                glEnd();
                glPopMatrix();
            }
            else {
                glTranslatef(Monstrao[i].x, Monstrao[i].y, 1);
                glBindTexture(GL_TEXTURE_2D, (*Textura).Monstrao);
                glBegin(GL_POLYGON);
                    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
                    glTexCoord2f(1, 0); glVertex3f(Monstrao[i].largura, 0, 0);
                    glTexCoord2f(1, 1); glVertex3f(Monstrao[i].largura, Monstrao[i].altura, 0);
                    glTexCoord2f(0, 1); glVertex3f(0, Monstrao[i].altura, 0);
                glEnd();
                glPopMatrix();
            }
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);

            if (Monstrao[i].StatusObjeto == Explodido){
                Monstrao[i].SpriteExplosao += 0.1;
                if (Monstrao[i].SpriteExplosao > 1)
                    Monstrao[i].SpriteExplosao = 0;
            }
        }
    }
}

void MoverMonstrao (struct Tempo *Tempo, struct objetos Monstrao[], struct Jogo *Jogo, struct Personagem *Personagem, int Quantidade_de_Monstrao){
    srand(time(0));
    if ((*Tempo).Tempo_Decorrido >= (*Tempo).Tempo_Total*0.5){
        for (int i=0; i<Quantidade_de_Monstrao; i++){ // O movimento do "Monstrao" é diferente, ele persegue o jogador.
            Monstrao[i].y -= Monstrao[i].movimento;
            Monstrao[i].x -= (Monstrao[i].x - (*Personagem).x) / 20.0f;

            if (Monstrao[i].y < (*Jogo).x+(*Tempo).AlturaBarraTempo + 20){ // Explode pouco acima do chão
                if ((*Jogo).Som)
                    (*Jogo).MusicExplosao.play(); // Play som da explosao
                Monstrao[i].StatusObjeto = Explodido;
            }

            if ((*Personagem).StatusPerson == Normal && (*Personagem).y <= Monstrao[i].y+Monstrao[i].altura && (*Personagem).y+(*Personagem).altura  >= Monstrao[i].y && (((*Personagem).x >= Monstrao[i].x && (*Personagem).x <= Monstrao[i].x+Monstrao[i].largura) || ((*Personagem).x+(*Personagem).largura  >= Monstrao[i].x && (*Personagem).x+(*Personagem).largura  <= Monstrao[i].x+Monstrao[i].largura))){
                if ((*Jogo).Som)
                    (*Jogo).MusicExplosao.play(); // Play som da explosao
                Monstrao[i].StatusObjeto = Explodido; // Colisão monstrão com personagem somente se não estiver invencível
                (*Personagem).QuantidadeVidas--;
                (*Personagem).StatusPerson = Invencivel;
            }

            if (Monstrao[i].y < (*Jogo).x+(*Tempo).AlturaBarraTempo){ // Ressurge aletório
                do {
                    Monstrao[i].x = (*Jogo).x + rand()%600 - i*10; // valores bem alatórios
                } while (Monstrao[i].x <= -300 && Monstrao[i].x+100 <= 200);
                Monstrao[i].y = 300 + rand()%1000 + i*10;
                Monstrao[i].StatusObjeto = Vivo;
            }

            if (Monstrao[i].y >= 0) // Poderá mudar a velocidade enquanto estiver até a metade da tela.
                Monstrao[i].movimento = 1+rand()%4;
        }
    }
}
