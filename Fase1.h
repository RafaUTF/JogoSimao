#pragma once
#include "Fase.h"

namespace Fases {
    
    class Fase1 : public Fase {

    private:
        bool proximaFase;

    public:
        void destruirNeutralizados();

        Fase1(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers);
        ~Fase1();

        void executar();
        void criarMapa(const std::string& caminhoJson);
        void criarEntidades();
        void criarChefe(Vector2f pos);

        void criarInimigos();
        void criarObstaculos();

        void carregarJogo(const std::string& caminho);
        void salvarJogo(const std::string& caminho);

        bool deveTrocarFase();
        void setTrocarFase(bool t);
    };

}