#include "Fase.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

void Fase::criarCenario()
{
}

Fase::Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers_) :
    pGC(gc), pGG(gg), LE(), pontos1(0), pontos2(0)
{
	tiros = new ListaEntidades();

    Ente::setpGG(gg); // define o gerenciador gr�fico no Ente base

    numPlayers = numPlayers_;

    pJog1 = new Jogador(tiros);
    LE.incluir(pJog1);
    pGC->incluirJogador(pJog1);
    if (numPlayers == 2) {
        pJog2 = new Jogador(tiros);
        LE.incluir(pJog2);
        pGC->incluirJogador(pJog2);
    }
    else {
        pJog2 = nullptr;
    }
}

Fase::~Fase() {
    // A lista deve deletar todas as entidades automaticamente.
	cout << "destrutora fase apagando a lista de projeteis(tiros)" << endl;
    delete tiros;
    tiros = nullptr;
}

void Fase::executar()
{
}

ListaEntidades* Fase::getListaEntidades() {
    return &LE;
}

void Fase::gravarNome(sf::RenderWindow* window) {
    
    // Salva a view atual da fase
    sf::View viewAnterior = window->getView();

    // Cria uma view fixa (HUD) centralizada na tela
    sf::View viewHUD(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
    viewHUD.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
    sf::Font font;
    if (!font.loadFromFile("upheavtt.ttf")) {
        return; // Verifique se a fonte está disponível
    }

    std::string nome;
    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(28);
    texto.setFillColor(sf::Color::White);


    sf::Text instrucao("Digite seu nome e pressione Enter:", font, 24);
    instrucao.setFillColor(sf::Color::White);

    instrucao.setPosition(window->getSize().x / 2.f - 180, window->getSize().y / 2.f - 60);
    texto.setPosition(window->getSize().x / 2.f - 100, window->getSize().y / 2.f);

    bool inserindo = true;
    while (inserindo && window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                return;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!nome.empty())
                        nome.pop_back();
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    inserindo = false;
                }
                else if (event.text.unicode < 128 && nome.size() < 15) {
                    nome += static_cast<char>(event.text.unicode);
                }
            }
        }

        texto.setString("Nome: " + nome);

		window->setView(viewHUD);
        window->clear(sf::Color::Black);
        window->draw(instrucao);
        window->draw(texto);
        window->display();
    }

    window->setView(viewAnterior);


    int total = pontos1 + pontos2;

    std::ifstream in("leaderboard.json");
    json lb = json::array();
    if (in.is_open()) {
        in >> lb;
    }

    lb.push_back({ {"nome", nome}, {"pontuacao", total} });

    std::sort(lb.begin(), lb.end(), [](const json& a, const json& b) {
        return a["pontuacao"] > b["pontuacao"];
        });

    if (lb.size() > 10)
        lb.erase(lb.begin() + 10, lb.end());

    std::ofstream out("leaderboard.json");
    out << lb.dump(4);
}

void Fase::desenharProjeteis()//mostra os projeteis na tela
{
	tiros->desenhar();
   
}
void Fase::incluirProjeteisGC()
{
    for (tiros->primeiro();!tiros->fim();tiros->operator++()) {
        pGC->incluirProjetil(static_cast<Projetil*>(tiros->getAtual()));
    }
}

void Fase::destruirProjeteis()//pega os desativados e tira da ListaEntidades e do Gerenciador_Colisoes e deleta
{
    pGC->retirarProjeteis();

    Projetil* pj = nullptr;
    for (tiros->primeiro();!tiros->fim();tiros->operator++()) {
        pj = static_cast<Projetil*>(tiros->getAtual());
		if (pj && pj->getAtivo() == false) {
			tiros->retirar(pj);
			delete pj;
			pj = nullptr;
		}
    }
}

