struct Tempo {
    float x, y;
    int contador;
    int Tempo_Decorrido;
    int Tempo_Total;
    float AlturaBarraTempo;
    bool ControleAumentodeMovimentoLvl2;
};

void DesenharTempo (struct Jogo *Jogo, struct Tempo *Tempo, struct objetos *Objeto);
void DesenharBarraProgressoPowerUp (struct Tempo *Tempo, struct objetos *Objeto);
