
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

#include "MenuPause.h"
namespace Fases {

    class Fase : public Ente {
    protected:
        MenuPause* menuPause;

		sf::Font fonteHUD;
        sf::Text HUD;

        int pontos;

        int numPlayers;

        Entidades::Personagens::Jogador* pJog1;
        Entidades::Personagens::Jogador* pJog2;

        Listas::ListaEntidades LE;
        Listas::ListaEntidades* tiros;

        Gerenciadores::Gerenciador_Colisoes* pGC;
        Gerenciadores::Gerenciador_Grafico* pGG;

        virtual void criarInimigos() = 0;
        virtual void criarObstaculos() = 0;

        virtual void criarEntidades() = 0;
        virtual void criarChefe(Vector2f pos) = 0;

        virtual void incluirProjeteisGC();

        virtual void desenharProjeteis();

        virtual void destruirProjeteis();

        //virtual void finalizarFase()=0;
    public:

        virtual void destruirNeutralizados() = 0;

        virtual void criarMapa(const std::string& caminhoJson) = 0;
        Fase(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers_);
        virtual ~Fase();
        virtual void executar();
        Listas::ListaEntidades* getListaEntidades();

        virtual void carregarJogo(const std::string& caminho) = 0;
        virtual void salvarJogo(const std::string& caminho) = 0;

        //int getPontos1() const { return pontos1; }
        //void setPontos1(int pontos) { pontos1 = pontos; }
        //int getPontos2() const { return pontos2; }
        //void setPontos2(int pontos) { pontos2 = pontos; }
        int getNumPlayers() const { return numPlayers; }

        Entidades::Personagens::Jogador* getJogador1() const { return pJog1; }
        Entidades::Personagens::Jogador* getJogador2() const { return pJog2; }

        void gravarNome(sf::RenderWindow* window);
        bool fimFase();

		void criarHUD();
        void mostrarVidaPontos();
    };

}