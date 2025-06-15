
#pragma once
#include "Ente.h"
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Gerenciador_Grafico.h"
#include "Plataforma.h"
#include "TeiaAranha.h"
#include "Inimigo.h"
#include "Chefao.h"
#include "InimigoPequeno.h"
#include "InimigoAlto.h"

class Fase : public Ente {
protected:

    Jogador* pJog1;
    Jogador* pJog2;

    ListaEntidades LE;
    Gerenciador_Colisoes* pGC;
    Gerenciador_Grafico* pGG;

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    void criarCenario();//tem q fazer

    virtual void criarMapa(const std::string& caminhoJson) = 0;
    virtual void criarEntidades() = 0;
    virtual void criarChefe(Vector2f pos) = 0;


    virtual void incluirProjeteisGC();

    virtual void desenharProjeteis();

    virtual void destruirProjeteis();

    void destruirNeutralizados();

public:
    Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg);
    virtual ~Fase();
    virtual void executar();
    ListaEntidades* getListaEntidades();
};