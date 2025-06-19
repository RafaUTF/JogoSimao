#pragma once
#include "Fase.h"

class Fase2 : public Fase {

private:

    vector<Chefao*> LCs;//lista de chefes


    void criarInimigos();
    void criarObstaculos();

    void incluirProjeteisGC();

    void desenharProjeteis();
    void destruirProjeteis();

    

public:
    void destruirNeutralizados();
    Fase2(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers);
    ~Fase2();

    void executar();
    void criarMapa(const std::string& caminhoJson);
    void criarEntidades();

    void criarChefe(Vector2f pos);

    void carregarJogo(const std::string& caminho);
    void salvarJogo(const std::string& caminho);


};
