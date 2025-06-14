#pragma once
#include "Fase.h"

class Fase2 : public Fase {

private:
    Jogador* pJog1;
    Jogador* pJog2;
    
    vector<Inimigo*> LIs;

    const int maxChefoes;

    void criarInimigos();
    void criarObstaculos();

    void destruirProjeteis();

    void incluirProjeteisGC();

protected:
    void criarChefoes();
    void criarObstMedios();
    void desenharProjeteis();

public:
    Fase2(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers);
    ~Fase2();

    void executar();
    void criarMapa(const std::string& caminhoJson);
    void criarEntidades();

    void criarChefe(Vector2f pos);
};

