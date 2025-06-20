#pragma once
#include "Fase.h"


namespace Fases {

    class Fase2 : public Fase {

    private:

        vector<Entidades::Personagens::Chefao*> LCs;//lista de chefes


        void criarInimigos();
        void criarObstaculos();


    public:

        void destruirNeutralizados();

        Fase2(Gerenciadores::Gerenciador_Colisoes* gc, Gerenciadores::Gerenciador_Grafico* gg, int numPlayers);
        ~Fase2();

        void executar();
        void criarMapa(const std::string& caminhoJson);
        void criarEntidades();

        void criarChefe(Vector2f pos);

        void carregarJogo(const std::string& caminho);
        void salvarJogo(const std::string& caminho);


    };

}