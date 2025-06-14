#include "Fase.h"

void Fase::criarCenario()
{
}

Fase::Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg) :
    pGC(gc), pGG(gg),LE()
{

    Ente::setpGG(gg); // define o gerenciador gráfico no Ente base
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
