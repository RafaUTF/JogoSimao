#include "Fase2.h"

#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

Fase2::Fase2(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers)
    : Fase(gc, gg), maxChefoes(1), LIs()
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

    criarChefoes();
    criarObstMedios();
    //criarProjeteis();
    criarInimigos();
    criarObstaculos();

    criarCenario();
}



void Fase2::criarInimigos()
{
}

void Fase2::criarObstaculos()
{
}




void Fase2::criarChefoes()
{
    int nChefes = 1+(rand() % maxChefoes);//1 a maxChefoes
    cout << "numero chefoes fase 2: " << nChefes << endl;
    Inimigo* pi = nullptr;
    for (int i = 0;i < nChefes;i++) {
        pi = new Chefao(pJog1, pJog2, (Vector2f(1200.f+i*300.f, 400.f)));
        LE.incluir(pi);
        LIs.push_back(pi);
        pGC->incluirInimigo(pi);
    }
}

void Fase2::criarObstMedios()
{
}




Fase2::~Fase2() {
    cout << "destrutora fase2" << endl;
    LIs.clear();
}

void Fase2::executar() {
    while (pGG->aberta()) {
        sf::Event event;
        while (pGG->getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                pGG->fechar();
        }

        LE.percorrer();//executa tudo menos projeteis
        incluirProjeteisGC();
        pGC->executar();
        

        pGG->moverCamera(pJog1, pJog2);

        pGG->clear();
        pGG->desenhaFundo();
        LE.desenhar();
        desenharProjeteis();
        pGG->mostrar();

        destruirProjeteis();
        destruirNeutralizados();


    }
}

void Fase2::criarEntidades() {
}


void Fase2::criarChefe(Vector2f pos) {
    Inimigo* chefe = new Chefao(pJog1, pJog2, pos);
    LE.incluir(chefe);
    pGC->incluirInimigo(chefe);
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

    for (int i = 0; i < data.size(); ++i) {
        int id = data[i];
        if (id == 0)
            continue; // sem tile

        int coluna = i % larguraMapa;
        int linha = i / larguraMapa;

        float x = coluna * larguraTiles;
        float y = linha * alturaTiles;

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



void Fase2::desenharProjeteis()//mostra os projeteis na tela
{
    pJog1->getTiros()->desenhar();
    if (pJog2)
        pJog2->getTiros()->desenhar();
    for (int i = 0;i < LIs.size();i++) {
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
    for (l->primeiro();!l->fim();l->operator++()) {
        pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
    }
    if (pJog2) {
        l = pJog2->getTiros();
        for (l->primeiro();!l->fim();l->operator++()) {
            pGC->incluirProjetil(static_cast<Projetil*>(l->getAtual()));
        }
    }

    for (int i = 0;i < LIs.size();i++) {
        if (LIs[i]) {
            l = LIs[i]->getTiros();
            if (l) {
                for (l->primeiro();!l->fim();l->operator++()) {
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

    for (l->primeiro();!l->fim();l->operator++()) {
        Projetil* pj = static_cast<Projetil*>(l->getAtual());
        if (pj->getAtivo() == false) {
            l->retirar(pj);
            delete pj;
            pj = nullptr;
        }
    }
    if (pJog2) {
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

    for (int i = 0;i < LIs.size();i++) {
        if (LIs[i]) {
            l = LIs[i]->getTiros();
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
