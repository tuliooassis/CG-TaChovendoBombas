//Situação do Jogo
enum Jogo_Estado { Iniciando, Menu, ContagemRegressiva, SelecaodoPersonagem, IniciarGame, Game, Venceu,
    Perdeu, Creditos, Configuracao, Pause, Reiniciar, Reiniciar_Confirmada, SairJogo, SairMenu, Sair_Confirmada };

struct Jogo {
    float x, y;
    float altura, largura;
    float VariacaoMenuSprite;
    float ContagemRegressivaSprite;
    bool Jogador_left, Jogador_right, Jogador_up;
    bool Som;
    Jogo_Estado StatusGame;
    GLint Fundo;
    sf::Music MusicGameOver, MusicExplosao, MusicPulo, MusicPowerUP, MusicCarregando, MusicGame, MusicMenu;
};
