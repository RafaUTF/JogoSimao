#include "Fase1.h"
#include <fstream>
#include "json.hpp"
 
using json = nlohmann::json;

void Fase1::criarInimMedios()
{
}

void Fase1::criarObstMedios()
{
}

void Fase1::criarInimigos()
{
}

void Fase1::criarObstaculos()
{
}

Fase1::Fase1(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers)
    : Fase(gc, gg),maxInimMedios(15)
{
    pJog1 = new Jogador();
    LE.incluir(pJog1);
    pGC->incluirJogador(pJog1);
    if (numPlayers == 2) {
        pJog2 = new Jogador();
        LE.incluir(pJog2);
        pGC->incluirJogador(pJog2);
    }

    criarMapa("mapa1.json");
    

}

Fase1::~Fase1() {
    cout << "destrutora fase1" << endl;
}

void Fase1::executar() {
    while (pGG->aberta()) {
        sf::Event event;
        while (pGG->getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                pGG->fechar();
        }

        LE.percorrer();
        pGC->executar();


        pGG->moverCamera(pJog1, pJog2); 

        pGG->clear();
        pGG->desenhaFundo();
        LE.desenhar();
        pGG->mostrar();
    }
}

void Fase1::criarEntidades() {
}


void Fase1::criarChefe(Vector2f pos) {
    Inimigo* chefe = new Chefao(pJog1, pJog2, pos);
    LE.incluir(chefe);
    pGC->incluirInimigo(chefe);
}


void Fase1::criarMapa(const std::string& caminhoJson) {
    std::ifstream arquivo(caminhoJson);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo JSON: " << caminhoJson << std::endl;
        return;
    }

    json mapaJson;
    arquivo >> mapaJson;

    const int larguraTiles = mapaJson["tilewidth"];
    const int alturaTiles = mapaJson["tileheight"];
    const int larguraMapa = mapaJson["width"];
    const int alturaMapa = mapaJson["height"];

    const auto& camada = mapaJson["layers"][0];  // Usando primeira camada ("Camada de Blocos 1")
    const auto& data = camada["data"];

    for (int i = 0; i < data.size(); ++i) {
        int id = data[i];
        if (id == 0)
            continue; // sem tile

        int coluna = i % larguraMapa;
        int linha = i / larguraMapa;

        float x = coluna * larguraTiles;
        float y = linha * alturaTiles;

        if (id == 19) {
			pJog1->getCorpo().setPosition({x, y});
        }
        if (id == 23) {
            if (pJog2)
                pJog2->getCorpo().setPosition({ x, y });
        }

        // Ex: id 2 = chão, id 781 = plataforma, etc.
        if (id == 2 || id == 781 || id == 34 || id == 28) {
            auto* plataforma = new Plataforma({ x, y });
            LE.incluir(plataforma);
            pGC->incluirObstaculo(plataforma);
        }

        if (id == 10) {
            criarChefe({ x, y });
        }
        
        if (id == 14) {
            Espinho* espinho = new Espinho({ x, y });
            LE.incluir(espinho);
            pGC->incluirObstaculo(espinho);
        }

        if (id == 13) {
            TeiaAranha* teiaaranha = new TeiaAranha({ x, y });
            LE.incluir(teiaaranha);
            pGC->incluirObstaculo(teiaaranha);
        }

        if (id == 18) {
			InimigoPequeno* inimigoPequeno = new InimigoPequeno({ x, y });
            LE.incluir(inimigoPequeno);
			pGC->incluirInimigo(inimigoPequeno);
        }

        if (id == 11) {
            InimigoAlto* inimigoalto = new InimigoAlto({ x, y });
            LE.incluir(inimigoalto);
            pGC->incluirInimigo(inimigoalto);
        }

    }
}
