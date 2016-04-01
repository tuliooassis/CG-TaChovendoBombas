//Situações dos Objetos
enum Objeto_Estado { Vivo, Explodido };

struct objetos {
    float x, y;
    float altura, largura;
    float SpriteExplosao;
    float VariacaoSprite;
    int movimento;
    int Objetos_Desviados;
    int AndarPraDireitaouEsquerda; //Utilizado somente para a struct PowerUP
    Objeto_Estado StatusObjeto;
    bool PowerUpSIM; //Utilizado somente para a struct Objeto (Estrutura geral)
    int QuantidadeObjetosDesviarParaGanharPowerUP; //Utilizado somente para a struct Objeto (Estrutura geral)
};

void DesenharObjeto (struct Texturas *Textura, struct objetos Objetos[], int Quantidade_de_Objetos);
void MoverObjetos (struct Personagem *Personagem, struct Tempo *Tempo, struct Jogo *Jogo, struct Texturas *Textura, struct objetos Objetos[], struct objetos *Objeto,  int Quantidade_de_Objetos);
void DesenharFogueira (struct Tempo *Tempo, struct Texturas *Textura, struct objetos *Fogueiras, struct Jogo *Jogo, struct Personagem *Personagem);
void DesenharMonstrao (struct Tempo *Tempo, struct Texturas *Textura, struct objetos Monstrao[], int Quantidade_de_Monstrao);
void MoverMonstrao (struct Tempo *Tempo, struct objetos Monstrao[], struct Jogo *Jogo, struct Personagem *Personagem, int Quantidade_de_Monstrao);
