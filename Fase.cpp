#include "Fase.h"

void Fase::criarCenario()
{
}

Fase::Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg, int numPlayers) :
	pGC(gc), pGG(gg), LE(), pontos1(0), pontos2(0)
{

    Ente::setpGG(gg); // define o gerenciador gr�fico no Ente base

    pJog1 = new Jogador();
    LE.incluir(pJog1);
    pGC->incluirJogador(pJog1);
    if (numPlayers == 2) {
        pJog2 = new Jogador();
        LE.incluir(pJog2);
        pGC->incluirJogador(pJog2);
    }
	else {
		pJog2 = nullptr;
	}
}

Fase::~Fase() {
    // A lista deve deletar todas as entidades automaticamente.
}

void Fase::executar()
{
}

ListaEntidades* Fase::getListaEntidades() {
    return &LE;
}

void Fase::desenharProjeteis()//mostra os projeteis na tela
{
    pJog1->getTiros()->desenhar();
    if (pJog2)
        pJog2->getTiros()->desenhar();
    
}
void Fase::incluirProjeteisGC()
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

}

void Fase::destruirProjeteis()//pega os desativados e tira da ListaEntidades e do Gerenciador_Colisoes e deleta
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

}

void Fase::destruirNeutralizados()
{
    pGC->retirarPersonagens();

    Entidade* pe = nullptr;
    for (LE.primeiro();!LE.fim();LE.operator++()) {
        pe = LE.getAtual();
        if (pe && pe->getVidas() == 0) {
            Jogador* pjog = static_cast<Jogador*>(pe);
            if (pjog == pJog1) {
                pontos1 += pJog1->getPontos();
                pJog1 = nullptr;
            }
            else if (pjog == pJog2) {
                pontos2 += pJog2->getPontos();
                pJog2 = nullptr;
            }
           
            LE.retirar(pe);
            delete pe;
            pe = nullptr;
        }
    }
}
