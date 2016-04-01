//Situações do Personagem
enum Personagem_Selecionado { Person1, Person2 };
enum Personagem_Estado { Normal, Invencivel, Dead };
enum Personagem_Anda { Direita, Esquerda };

struct Personagem {
    float x, y, z;
    float largura, altura;
    float movimento;
    float Gravidade_Pulo;
    float GraudeVariacao;
    float VariacaoSpriteSelecionarPersonagem;
    float VariacaoSpritePersonagem;
    int QuantidadeVidas;
    int TimeInvencivel;
    int Tempo_de_Morte;
    Personagem_Estado StatusPerson;
    Personagem_Anda QualLadoPersonagemAnda;
    Personagem_Selecionado Personagem_Select;
};

void DesenharPersonagem(struct Personagem *Personagem, struct Jogo *Jogo, struct Tempo *Tempo, struct Texturas *Textura);
void DesenharVida (int x, struct Texturas *Textura);
