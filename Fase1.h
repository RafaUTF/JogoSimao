#pragma once
#include "Fase.h"

class Fase1 : public Fase {

private: 
    Jogador* pJog1;
    Jogador* pJog2;

    const int maxInimMedios;
protected:
    void criarInimMedios();
    void criarObstMedios();
    virtual void criarInimigos();
    virtual void criarObstaculos();
public:
    Fase1(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers);
    ~Fase1();

    void executar();
    void criarMapa(const std::string& caminhoJson);
    void criarEntidades();
    void criarChefe(Vector2f pos);


};
