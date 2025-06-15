#pragma once
#include "Fase.h"

class Fase2 : public Fase {

private:
    
    vector<Inimigo*> LIs;//lista de chefes

    const int maxChefoes;

    void criarInimigos();
    void criarObstaculos();

    void incluirProjeteisGC();

    void desenharProjeteis();

    void destruirProjeteis();



protected:
    void criarChefoes();
    void criarObstMedios();

public:
    Fase2(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers);
    ~Fase2();

    void executar();
    void criarMapa(const std::string& caminhoJson);
    void criarEntidades();

    void criarChefe(Vector2f pos);
};

