#include "Fase2.h"
#include <fstream>
#include "json.hpp"

#include "MenuPause.h"

using json = nlohmann::json;

Fase2::Fase2(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers)
    : Fase(gc, gg,numPlayers)
{
}

Fase2::~Fase2() {
    cout << "destrutora fase2" << endl;
}

void Fase2::executar() {
    while (pGG->aberta()) {
        sf::Event event;
        while (pGG->getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                pGG->fechar();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    // ABRIR MENU DE PAUSE
                    MenuPause menuPause;
                    int escolha = menuPause.mostrar(*pGG->getWindow());

                    if (escolha == 1) { // Salvar Jogo
                        salvarJogo("save.json");
                        std::cout << "Jogo salvo.\n";
                    }
                    else if (escolha == 2) { // Sair para Menu
                        return; // sai da fase e volta ao menu inicial
                    }
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
                    salvarJogo("save.json");
                    std::cout << "Jogo salvo!" << std::endl;
                }
            }
        }
        //cout << "a" << endl;
        LE.percorrer();//executa tudo menos projeteis
        //cout << "b" << endl;
        incluirProjeteisGC();//////////////////////////////////
        //cout << "c" << endl;
        pGC->executar();
        //cout << "d" << endl;
        pGG->moverCamera(pJog1, pJog2);
        //cout << "e" << endl;
        pGG->clear();
        //cout << "f" << endl;
        pGG->desenhaFundo();
        //cout << "g" << endl;
        LE.desenhar();
        //cout << "h" << endl;
        desenharProjeteis();
        //cout << "i" << endl;
        pGG->mostrar();
        //cout << "j" << endl;
        destruirProjeteis();
        //cout << "k" << endl;
        destruirNeutralizados();
        //cout << "l" << endl;


        if (pJog1 == nullptr && pJog2 == nullptr) {
            cout << "todos os jogadores foram neutralizados, fim do programa!" << endl;
            cout << "PONTUACAO1: " << pontos1 << endl;
            cout << "PONTUACAO2: " << pontos2 << endl;
            
            gravarNome(pGG->getWindow());

            
            pGG->fechar();

            return;
            
        }
    }

    if (numPlayers == 1) {
        if (pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) {
            gravarNome(pGG->getWindow());
            pGG->fechar();
        }
    }
    else if (numPlayers == 2) {
        if (pJog1 && pJog2) {
            if ((pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) && (pJog2->getcm().x > FINALFASE - 30 && pJog2->getcm().x < FINALFASE + 30)) {
                gravarNome(pGG->getWindow());
                pGG->fechar();
            }
        }
        else if (pJog1) {
            if (pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) {
                gravarNome(pGG->getWindow());
                pGG->fechar();
            }
        }
        else
            if (pJog2->getcm().x > FINALFASE - 30 && pJog2->getcm().x < FINALFASE + 30) {
                gravarNome(pGG->getWindow());
                pGG->fechar();
            }

    }
}

void Fase2::criarEntidades() {
}


void Fase2::criarChefe(Vector2f pos) {
    Chefao* chefe = new Chefao(pJog1, pJog2, pos);
    LE.incluir(chefe);
    pGC->incluirInimigo(chefe);
	LCs.push_back(chefe);////
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


    }

}

void Fase2::salvarJogo(const std::string& caminho) {
    json estado;
    estado["fase"] = 2;
    estado["numPlayers"] = getNumPlayers();
    if (pJog1)
        estado["jogador1"] = { {"x", pJog1->getCorpo().getPosition().x}, {"y", pJog1->getCorpo().getPosition().y}, {"numvidas", pJog1->getVidas() }, {"pontos1", pJog1->getPontos()} };
    else
        estado["jogador1"] = { {"x", 0}, {"y", 0}, {"numvidas", 0}, { "pontos1",getPontos1() } };
    if (getNumPlayers() == 2)
    {
        if (pJog2) {
            estado["jogador2"] = { {"x", pJog2->getCorpo().getPosition().x}, {"y", pJog2->getCorpo().getPosition().y}, {"numvidas", pJog2->getVidas()}, {"pontos2", pJog2->getPontos()} };
        }
        else
            estado["jogador2"] = { {"x", 0}, {"y", 0}, {"numvidas", 0}, { "pontos2", getPontos2() } };
    }

    estado["projeteis"] = json::array();
    set<Projetil*>::iterator it = pGC->getProjeteis().begin();
    while (it != pGC->getProjeteis().end()) {
        estado["projeteis"].push_back({
             {"x", (*it)->getCorpo().getPosition().x},
             {"y", (*it)->getCorpo().getPosition().y},
             {"vx", (*it)->getVelocidade().x},
             {"vy", (*it)->getVelocidade().y},

            });
        ++it;
    }

    estado["entities"] = json::array();
    for (LE.primeiro(); !LE.fim(); ++LE) {
        Entidade* e = LE.getAtual();
        if (e == pJog1 || e == pJog2) continue;
        json je;
        je["type"] = e->getTipo();
        auto p = e->getcm();
        je["x"] = p.x;
        je["y"] = p.y;

        if (e->getTipo() == "InimigoPequeno") {
            auto* ip = dynamic_cast<InimigoPequeno*>(e);
            if (ip) {
                sf::Vector2f ini = ip->getPosicaoInicial();
                je["xi"] = ini.x;
                je["yi"] = ini.y;
            }
        }

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

    if (estado["jogador1"]["numvidas"] > 0) {

        pJog1->getCorpo().setPosition(estado["jogador1"]["x"], estado["jogador1"]["y"]);
        pJog1->setVida(estado["jogador1"]["numvidas"]);
        pontos1 = estado["jogador1"]["pontos1"];
    }
    else {
        pontos1 = estado["jogador1"]["pontos1"];
        pJog1->setVida(0);
    }
    destruirNeutralizados();
    if (estado["numPlayers"] == 2) {
        if (estado["jogador2"]["numvidas"] > 0) {
            pJog2->getCorpo().setPosition(estado["jogador2"]["x"], estado["jogador2"]["y"]);
            pJog2->setVida(estado["jogador2"]["numvidas"]);
            pontos2 = estado["jogador2"]["pontos2"];
        }
        else
        {
            pontos2 = estado["jogador2"]["pontos2"];
            pJog2->setVida(0);
        }
    }

    destruirNeutralizados();


    for (auto& je : estado["entities"]) {
        Entidade* ne = nullptr;
        Obstaculo* no = nullptr;
        sf::Vector2f pos(je["x"], je["y"]);
        std::string tipo = je["type"];


        if (tipo == "Plataforma") no = new Plataforma(pos);
        else if (tipo == "Espinho") no = new Espinho(pos);
        else if (tipo == "Chefao") ne = new Chefao(pJog1, pJog2, pos);

        sf::Vector2f posAtual(je["x"], je["y"]);
        sf::Vector2f posIni = posAtual;
        if (je.contains("xi") && je.contains("yi"))
            posIni = sf::Vector2f(je["xi"], je["yi"]);

        if (tipo == "InimigoPequeno") {
            InimigoPequeno* ip = new InimigoPequeno(posIni); // posição inicial de patrulha
            ip->getCorpo().setPosition(posAtual);            // posição atual real
            ne = ip;
        }

        std::cout << "Tipo encontrado: [" << tipo << "]" << std::endl;

        if (ne) {
            LE.incluir(ne);
            pGC->incluirInimigo(static_cast<Inimigo*>(ne));

        }

        if (no) {
            LE.incluir(no);
            pGC->incluirObstaculo(no);
            if(no->getTipo() == "Espinho"){
				cout << "Espinho criado em: " << pos.x << ", " << pos.y << endl;
			}
        }

    }
    for (auto& jp : estado["projeteis"]) {
        Projetil* proj = new Projetil(sf::Vector2f(jp["x"], jp["y"]));
        proj->getCorpo().setPosition(jp["x"], jp["y"]);
        proj->setVelocidade(sf::Vector2f(jp["vx"], jp["vy"]));

        if (pJog1) {
            proj->setDono(pJog1);
            pJog1->incluirTiros(proj);
        }
        else {
            proj->setDono(pJog2);
            pJog2->incluirTiros(proj);
        }

        pGC->incluirProjetil(proj);
    }


}

void Fase2::desenharProjeteis()//mostra os projeteis na tela
{
    if (pJog1 && pJog1->getTiros())
        pJog1->getTiros()->desenhar();
    if (pJog2 && pJog2->getTiros())
        pJog2->getTiros()->desenhar();
    for (int i = 0;i < LCs.size();i++) {
        if (LCs[i] && LCs[i]->getTiros()) {
            LCs[i]->getTiros()->desenhar();
        }
        else {
            cout << "ponteiro inimigo nulo em criar projeteis fase2" << endl;
        }
    }
}
void Fase2::incluirProjeteisGC()
{
    int j;
    ListaEntidades* l = nullptr;
    if (pJog1 && pJog1->getTiros()) {
        //cout << "1" << endl;
        l = pJog1->getTiros();
        j = 0;
        for (l->primeiro();!l->fim();l->operator++()) {
            //cout << "a " << j++ << endl;
            pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
        }
    }
    j = 0;
    if (pJog2 && pJog2->getTiros()) {
        //cout << "2" << endl;
        l = pJog2->getTiros();
        for (l->primeiro();!l->fim();l->operator++()) {
            //cout << "b " << j++ << endl;
            pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
        }
    }

    for (int i = 0;i < LCs.size();i++) {
        if (LCs[i] && LCs[i]->getTiros()) {
            //cout << "3" << endl;
            l = LCs[i]->getTiros();
            j = 0;
            for (l->primeiro();!l->fim();l->operator++()) {
                //cout << "c " << j++ << endl;
                pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
            }
        }
    }
}

void Fase2::destruirProjeteis()//pega os desativados e tira da ListaEntidades e do Gerenciador_Colisoes e deleta
{
    pGC->retirarProjeteis();

    ListaEntidades* l = nullptr;

    if (pJog1 && pJog1->getTiros()) {
        l = pJog1->getTiros();
        for (l->primeiro();!l->fim();l->operator++()) {
            Projetil* pj = static_cast<Projetil*>(l->getAtual());
            if (pj->getAtivo() == false) {
                l->retirar(pj);
                delete pj;
                pj = nullptr;
            }
        }
    }

    if (pJog2 && pJog2->getTiros()) {
        l = pJog2->getTiros();
        for (l->primeiro();!l->fim();l->operator++()) {
            Projetil* pj = static_cast<Projetil*>(l->getAtual());
            if (pj->getAtivo() == false) {
                l->retirar(pj);
                delete pj;
                pj = nullptr;
            }
        }
    }

    for (int i = 0;i < LCs.size();i++) {
        if (LCs[i] && LCs[i]->getTiros()) {
            l = LCs[i]->getTiros();
            for (l->primeiro();!l->fim();l->operator++()) {
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

void Fase2::destruirNeutralizados()
{
    pGC->retirarPersonagens();

    Entidade* pe = nullptr;
    for (LE.primeiro();!LE.fim();LE.operator++()) {
        pe = LE.getAtual();
        if (pe && pe->getVidas() == 0) {
            Jogador* pjog = static_cast<Jogador*>(pe);
            if (pJog1 && pjog == pJog1) {
                pontos1 = pJog1->getPontos();
                cout << "j1 morreu" << endl;
                pJog1 = nullptr;
            }
            else if (pJog2 && pjog == pJog2) {
                pontos2 = pJog2->getPontos();
                cout << "j2 morreu" << endl;
                pJog2 = nullptr;
            }
            else {
                Chefao* pc = dynamic_cast<Chefao*>(pe);
                bool eliminou = false;
                for (vector<Chefao*>::iterator it= LCs.begin();!eliminou && it != LCs.end();it++) {
                    if (pc && pc == *it) {
                        cout << "chefe morreu" << endl;
                        it=LCs.erase(it);
                        eliminou = true;
                    }
                }
            }
            LE.retirar(pe);
            delete pe;
            pe = nullptr;
        }
    }
}