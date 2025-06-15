#include "Fase1.h"
#include <fstream>
#include "json.hpp"
 
using json = nlohmann::json;

Fase1::Fase1(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers)
    : Fase(gc, gg)
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

Fase1::~Fase1() {}

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

    std::vector<std::pair<float, float>> bloco_teia;
    std::vector<std::pair<float, float>> bloco_plataforma;



    for (int i = 0; i < data.size(); ++i) {
        int id = data[i];
        if (id == 0)
            continue; // sem tile

        int coluna = i % larguraMapa;
        int linha = i / larguraMapa;

        float x = coluna * larguraTiles;
        float y = linha * alturaTiles;

       
		

        //teia de aranha aleatória
        if (id == 16) {
            bloco_teia.emplace_back(x, y);
            if (bloco_teia.size() == 5) {
                int chance = rand() % 2; // 0 = teia, 1 = plataforma
                for (auto& pos : bloco_teia) {
                    if (chance == 0) {
                        TeiaAranha* teiaaranha = new TeiaAranha({ pos.first, pos.second });
                        LE.incluir(teiaaranha);
                        pGC->incluirObstaculo(teiaaranha);
                    }
                    else {
                        Plataforma* plataforma = new Plataforma({ pos.first, pos.second });
                        LE.incluir(plataforma);
                        pGC->incluirObstaculo(plataforma);
                    }
                }
                bloco_teia.clear();
            }
        }
        else {
            // Se encontrar um tile diferente, reseta o bloco
            bloco_teia.clear();
        }


        //plataforma aleatória
        if (id == 12) {
            bloco_plataforma.emplace_back(x, y);
            if (bloco_plataforma.size() == 6) {
                int chance = rand() % 2;
                for (auto& pos : bloco_plataforma) {
                    if (chance == 0) {
                        Plataforma* plataforma = new Plataforma({ pos.first, pos.second });
                        LE.incluir(plataforma);
                        pGC->incluirObstaculo(plataforma);
                    }
                }
                bloco_plataforma.clear();
            }
        }
            else {
                // Se encontrar um tile diferente, reseta o bloco
                bloco_plataforma.clear();
            }
        
        //Inimigo Alto aleatório
        if(id == 11){
            int chance = rand() % 2;
            if (chance == 0) {
                InimigoAlto* inimigoalto = new InimigoAlto({ x, y });
                LE.incluir(inimigoalto);
                pGC->incluirInimigo(inimigoalto);
            }
        }

        if (id == 26) {
            int chance = rand() % 2;
            if (chance == 0) {
                InimigoPequeno* inimigoPequeno = new InimigoPequeno({ x, y });
                LE.incluir(inimigoPequeno);
                pGC->incluirInimigo(inimigoPequeno);
            }
        }



        if (id == 19) {
                pJog1->getCorpo().setPosition({ x, y });
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


        if (id == 17) {
            std::cout << "Criando bandeira em: " << x << ", " << y << std::endl;
            BandeiraChegada* bandeiraChegada = new BandeiraChegada({ x, y });
            LE.incluir(bandeiraChegada); // Garante que será desenhada
            pGC->incluirObstaculo(bandeiraChegada); // Para colisão, se necessário
        }

    }

}