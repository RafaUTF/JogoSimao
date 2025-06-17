#include "Fase2.h"
#include <fstream>
#include "json.hpp"
#include "BandeiraChegada.h"

using json = nlohmann::json;

Fase2::Fase2(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers)
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

Fase2::~Fase2() {
    cout << "destrutora fase2" << endl;
}

void Fase2::executar() {
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

void Fase2::criarEntidades() {
}


void Fase2::criarChefe(Vector2f pos) {
    Inimigo* chefe = new Chefao(pJog1, pJog2, pos);
    LE.incluir(chefe);
    pGC->incluirInimigo(chefe);
}

void Fase2::criarInimigos()
{
}

void Fase2::criarObstaculos()
{
}


void Fase2::criarMapa(const std::string& caminhoJson) {
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

        //Espinho aleatório
        if (id == 4) {
            int chance = rand() % 2;
            if (chance == 0) {
                Espinho* espinho = new Espinho({ x, y });
                LE.incluir(espinho);
                pGC->incluirObstaculo(espinho);
            }
        }

        //Boss aleatório
        if (id == 21) {
            int chance = rand() % 2;
            if (chance == 0) {
				criarChefe({ x, y });
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

        if (id == 20) {
            Espinho* espinho = new Espinho({ x, y });
            LE.incluir(espinho);
            pGC->incluirObstaculo(espinho);
        }

        if (id == 18) {
            InimigoPequeno* inimigoPequeno = new InimigoPequeno({ x, y });
            LE.incluir(inimigoPequeno);
            pGC->incluirInimigo(inimigoPequeno);
        }


        if (id == 17) {
            std::cout << "Criando bandeira em: " << x << ", " << y << std::endl;
            BandeiraChegada* bandeiraChegada = new BandeiraChegada({ x, y });
            LE.incluir(bandeiraChegada); // Garante que será desenhada
            pGC->incluirObstaculo(bandeiraChegada); // Para colisão, se necessário
        }

    }

}

void Fase2::salvarJogo(const std::string& caminho) {
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

void Fase2::carregarJogo(const std::string& caminho) {
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

    for (auto& je : estado["entities"]) {
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

void Fase2::desenharProjeteis()//mostra os projeteis na tela
{
    pJog1->getTiros()->desenhar();
    if (pJog2)
        pJog2->getTiros()->desenhar();
    for (int i = 0; i < LIs.size(); i++) {
        if (LIs[i]) {
            LIs[i]->getTiros()->desenhar();
        }
        else {
            cout << "ponteiro inimigo nulo em criar projeteis fase2" << endl;
        }
    }
}
void Fase2::incluirProjeteisGC()
{
    ListaEntidades* l = pJog1->getTiros();
    for (l->primeiro(); !l->fim(); l->operator++()) {
        pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
    }
    if (pJog2) {
        l = pJog2->getTiros();
        for (l->primeiro(); !l->fim(); l->operator++()) {
            pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
        }
    }

    for (int i = 0; i < LIs.size(); i++) {
        if (LIs[i]) {
            l = LIs[i]->getTiros();
            if (l) {
                for (l->primeiro(); !l->fim(); l->operator++()) {
                    pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
                }
            }
        }
    }
}

void Fase2::destruirProjeteis()//pega os desativados e tira da ListaEntidades e do Gerenciador_Colisoes e deleta
{
    pGC->retirarProjeteis();

    ListaEntidades* l = pJog1->getTiros();

    for (l->primeiro(); !l->fim(); l->operator++()) {
        Projetil* pj = static_cast<Projetil*>(l->getAtual());
        if (pj->getAtivo() == false) {
            l->retirar(pj);
            delete pj;
            pj = nullptr;
        }
    }
    if (pJog2) {
        l = pJog2->getTiros();
        for (l->primeiro(); !l->fim(); l->operator++()) {
            Projetil* pj = static_cast<Projetil*>(l->getAtual());
            if (pj->getAtivo() == false) {
                l->retirar(pj);
                delete pj;
                pj = nullptr;
            }
        }
    }

    for (int i = 0; i < LIs.size(); i++) {
        if (LIs[i]) {
            l = LIs[i]->getTiros();
            for (l->primeiro(); !l->fim(); l->operator++()) {
                Projetil* pj = static_cast<Projetil*>(l->getAtual());
                if (pj->getAtivo() == false) {
                    l->retirar(pj);
                    delete pj;
                    pj = nullptr;
                }
            }
        }
        else
            cout << "chefao nulo em destruirProjeteis na Fase2" << endl;
    }
}