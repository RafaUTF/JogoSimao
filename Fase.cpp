#include "Fase.h"

void Fase::criarCenario()
{
}

Fase::Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg) :
    pGC(gc), pGG(gg), LE()
{

    Ente::setpGG(gg); // define o gerenciador gr�fico no Ente base
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
        //Personagem* pp = static_cast<Personagem*>(LE.getAtual());
        pe = LE.getAtual();
        if (pe&&pe->getVidas()==0) {
            LE.retirar(pe);
            delete pe;
            pe = nullptr;
        }
    }
}
