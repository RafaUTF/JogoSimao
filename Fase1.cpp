#include "Fase1.h"
#include <fstream>
#include "json.hpp"
#include "BandeiraChegada.h"

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
                salvarJogo("save.json");
                std::cout << "Jogo salvo!" << std::endl;
            }
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

void Fase1::criarInimigos()
{
}

void Fase1::criarObstaculos()
{
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

void Fase1::salvarJogo(const std::string& caminho) {
    json estado;
    estado["numPlayers"] = (pJog2 ? 2 : 1);
    estado["jogador1"] = { {"x", pJog1->getCorpo().getPosition().x}, {"y", pJog1->getCorpo().getPosition().y} };
    if (pJog2)
        estado["jogador2"] = { {"x", pJog2->getCorpo().getPosition().x}, {"y", pJog2->getCorpo().getPosition().y} };

    estado["entities"] = json::array();
    for (LE.primeiro(); !LE.fim(); ++LE) {
        Entidade* e = LE.getAtual();
        if (e == pJog1 || e == pJog2) continue;
        json je;
        je["type"] = e->getTipo();
        auto p = e->getcm();
        je["x"] = p.x;
        je["y"] = p.y;
        estado["entities"].push_back(je);
    }

    std::ofstream out(caminho);
    if (out.is_open()) out << estado.dump(4);
}

void Fase1::carregarJogo(const std::string& caminho) {
    std::ifstream in(caminho);
    if (!in.is_open()) return;

    json estado;
    in >> estado;

    pJog1->getCorpo().setPosition(estado["jogador1"]["x"], estado["jogador1"]["y"]);
    if (estado["numPlayers"] == 2 && pJog2)
        pJog2->getCorpo().setPosition(estado["jogador2"]["x"], estado["jogador2"]["y"]);

    std::vector<Entidade*> remover;
    for (LE.primeiro(); !LE.fim(); ++LE) {
        Entidade* e = LE.getAtual();
        if (e != pJog1 && e != pJog2) remover.push_back(e);
    }
    for (auto* e : remover) {
        LE.retirar(e);
        Gerenciador_Colisoes::getInstancia()->removerEntidade(e);
        delete e;
    }

    for(auto& je : estado["entities"]) {
        Entidade* ne = nullptr;
        Obstaculo* no = nullptr;
        sf::Vector2f pos(je["x"], je["y"]);
        std::string tipo = je["type"];


        if (tipo == "TeiaAranha") no = new TeiaAranha(pos);
        else if (tipo == "Plataforma") no = new Plataforma(pos);
        else if (tipo == "InimigoPequeno") ne = new InimigoPequeno(pos);
        else if (tipo == "InimigoAlto") ne = new InimigoAlto(pos);
        else if (tipo == "Espinho") no = new Espinho(pos);
        else if (tipo == "Chefao") ne = new Chefao(pJog1, pJog2, pos);
        else if (tipo == "BandeiraChegada") ne = new BandeiraChegada(pos);

        if (ne) {
            LE.incluir(ne);
            pGC->incluirInimigo(static_cast<Inimigo*>(ne));
            
        }

        if (no) {
            LE.incluir(no);
            pGC->incluirObstaculo(no);
        }

    }

}

