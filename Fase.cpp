#include "Fase.h"

Fase::Fase(Gerenciador_Colisoes* gc, Gerenciador_Grafico* gg) :
    pGC(gc), pGG(gg)
{
    Ente::setpGG(gg); // define o gerenciador gráfico no Ente base
}

Fase::~Fase() {
    // A lista deve deletar todas as entidades automaticamente.
}

ListaEntidades* Fase::getListaEntidades() {
    return &LE;
}
