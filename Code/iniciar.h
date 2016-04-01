struct Texturas {
    // Texturas Cenario e Telas
    GLint Fundo_Cenario;
    GLint Fundo_Cenario2;
    GLint Menu;
    GLint Configuracao;
    GLint Creditos;
    GLint Selecionar_Personagem;
    GLint Pause;
    GLint Win;
    GLint Gameover;
    GLint Coracao_vida;
    GLint Confirmacao_Saida;
    GLint Confirmacao_Reiniciar;
    GLint Contagem_Regressiva;
    GLint Iniciando;
    // Texturas Personagens
    GLint Personagem_Move_Direita;
    GLint Personagem_Move_Esquerda;
    GLint Personagem2_Move_Direita;
    GLint Personagem2_Move_Esquerda;
    GLint Person1Dead;
    GLint Person2Dead;
    GLint Person1Parado;
    GLint Person2Parado;
    GLint Person1PuloRight;
    GLint Person1PuloLeft;
    GLint Person2PuloRight;
    GLint Person2PuloLeft;
    //Texturas Objetos
    GLint Explosao;
    GLint Monstrao;
    GLint Bomb;
    GLint PowerUp;
    GLint Fogueira;
};

void Instanciar(struct Jogo *Jogo, struct Personagem *Personagem, struct Tempo *Tempo, struct objetos *Objeto,
                    struct objetos *Fogueiras, struct objetos Objetos[], struct objetos Monstrao[], struct objetos PowerUp[],
                    struct Texturas *Textura, int Quantidade_de_Monstrao, int Quantidade_de_Objetos, int Quantidade_de_PowerUP);
void Iniciar_Texturas_Sound (struct Texturas *Textura, struct Jogo *Jogo);
