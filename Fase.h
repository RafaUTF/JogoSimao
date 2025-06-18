
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
#include "BandeiraChegada.h"

class Fase : public Ente {
protected:
    int pontos1;
	int pontos2;



    Jogador* pJog1;
    Jogador* pJog2;

    ListaEntidades LE;
    Gerenciador_Colisoes* pGC;
    Gerenciador_Grafico* pGG;

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    void criarCenario();//tem q fazer

    
    virtual void criarEntidades() = 0;
    virtual void criarChefe(Vector2f pos) = 0;


    virtual void incluirProjeteisGC();

    virtual void desenharProjeteis();

    virtual void destruirProjeteis();

    virtual void destruirNeutralizados();

public:
    virtual void criarMapa(const std::string& caminhoJson) = 0;
    Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers);
    virtual ~Fase();
    virtual void executar();
    ListaEntidades* getListaEntidades();

    virtual void carregarJogo(const std::string& caminho) = 0;
    virtual void salvarJogo(const std::string& caminho)=0;
};