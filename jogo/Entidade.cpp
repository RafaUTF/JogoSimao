#include "Entidade.h"

Entidade::Entidade(float xx, float yy)
{
    x = xx;
    y = yy;
}
Entidade::~Entidade()
{
}

float Entidade::getXcm()
{
    return corpo.getPosition().x + corpo.getSize().x / 2;
}
float Entidade::getYcm()
{
    return corpo.getPosition().y + corpo.getSize().y / 2;
}

float Entidade::getRaioX()
{
    return corpo.getSize().x / 2;
}

float Entidade::getRaioY()
{
    return corpo.getSize().y / 2;
}


void Entidade::executar()
{
    cout<<"executar entidade aleatoria"<<endl;
}

