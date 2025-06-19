#include "Fase1.h"
#include <fstream>
#include "json.hpp"
#include "MenuPause.h"

using json = nlohmann::json;

Fase1::Fase1(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers)
    : Fase(gc, gg,numPlayers)
{
    proximaFase = false;
}

Fase1::~Fase1() {
    cout << "destrutora fase1" << endl;
}

void Fase1::executar() {
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

		tiros->percorrer(); // percorre os projeteis

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

        if (numPlayers == 1) {
            if(pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) {
				salvarJogo("save.json");
				pGG->clear();
                pGC->limpaLista();
				setTrocarFase(true);
                return;
			}
        }
        else if (numPlayers == 2) {
            if (pJog1 && pJog2) {
                if ((pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) && (pJog2->getcm().x > FINALFASE - 30 && pJog2->getcm().x < FINALFASE + 30)) {
                    salvarJogo("save.json");
                    pGG->clear();
                    pGC->limpaLista();
                    setTrocarFase(true);
                    return;
                }
            }
            else if (pJog1) {
                if (pJog1->getcm().x > FINALFASE - 30 && pJog1->getcm().x < FINALFASE + 30) {
                    salvarJogo("save.json");
                    pGG->clear();
                    pGC->limpaLista();
                    setTrocarFase(true);
                    return;
                }
            }
            else 
                if (pJog2->getcm().x > FINALFASE - 30 && pJog2->getcm().x < FINALFASE + 30) {
                    salvarJogo("save.json");
                    pGG->clear();
                    pGC->limpaLista();
                    setTrocarFase(true);
                   return;
                }
			
        }

    }   

}

void Fase1::criarEntidades() {
}


void Fase1::criarChefe(Vector2f pos) {
    Inimigo* chefe = new Chefao(tiros, pJog1, pJog2, pos);
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




    }

}

void Fase1::salvarJogo(const std::string& caminho) {
    
    json estado;

    estado["fase"] = 1;
    estado["numPlayers"] = getNumPlayers();
    if(pJog1)
        estado["jogador1"] = { {"x", pJog1->getCorpo().getPosition().x}, {"y", pJog1->getCorpo().getPosition().y}, {"numvidas", pJog1->getVidas() }, {"pontos1", pJog1->getPontos()}};
    else
        estado["jogador1"] = { {"x", 0}, {"y", 0}, {"numvidas", 0}, { "pontos1",getPontos1() }};
    if (getNumPlayers() == 2)
    {
        if (pJog2) {
            estado["jogador2"] = { {"x", pJog2->getCorpo().getPosition().x}, {"y", pJog2->getCorpo().getPosition().y}, {"numvidas", pJog2->getVidas()}, {"pontos2", pJog2->getPontos()}};
        }
        else
			estado["jogador2"] = { {"x", 0}, {"y", 0}, {"numvidas", 0}, { "pontos2", getPontos2() }};
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
        
        sf::Vector2f atual = e->getcm();
        je["x"] = atual.x;
        je["y"] = atual.y;

        if (e->getTipo() == "InimigoPequeno") {
            auto* ip = dynamic_cast<InimigoPequeno*>(e);
            if (ip) {
                sf::Vector2f ini = ip->getPosicaoInicial();
                je["xi"] = ini.x;
                je["yi"] = ini.y;
            }
        }
        else if (e->getTipo() == "InimigoAlto") {
            auto* ia = dynamic_cast<InimigoAlto*>(e);
            if (ia) {
                sf::Vector2f ini = ia->getPosicaoInicial();
                je["xi"] = ini.x;
                je["yi"] = ini.y;
            }
        }

        estado["entities"].push_back(je);
    }

    std::ofstream out(caminho);
    if (out.is_open()) out << estado.dump(4);
}

bool Fase1::deveTrocarFase()
{
    return proximaFase;
}

void Fase1::setTrocarFase(bool t)
{
	proximaFase = t;
}

void Fase1::carregarJogo(const std::string& caminho) {
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

        sf::Vector2f posAtual(je["x"], je["y"]);
        sf::Vector2f posIni = posAtual;
        if (je.contains("xi") && je.contains("yi"))
            posIni = sf::Vector2f(je["xi"], je["yi"]);

        if (tipo == "InimigoPequeno") {
            InimigoPequeno* ip = new InimigoPequeno(posIni); // posição inicial de patrulha
            ip->getCorpo().setPosition(posAtual);            // posição atual real
            ne = ip;
        }
        else if (tipo == "InimigoAlto") {
            InimigoAlto* ia = new InimigoAlto(posIni);
            ia->getCorpo().setPosition(posAtual);
            ne = ia;
        }

        if (ne) {
            LE.incluir(ne);
            pGC->incluirInimigo(static_cast<Inimigo*>(ne));
            
        }

        if (no) {
            LE.incluir(no);
            pGC->incluirObstaculo(no);
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

