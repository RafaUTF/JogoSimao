#include "Chefao.h"




Chefao::Chefao(ListaEntidades* t, Jogador* pp1, Jogador* pp2, Vector2f pos) :
    Inimigo(t, pos), forca(FORCA_CHEFE)
{
    chefao = true;

    num_vidas = VIDA_CHEFE;

    nivel_maldade = DANO_ALTO;

    aceleracao = ACELERACAO_CHEFE;

    p1 = pp1;
    p2 = pp2;
    //criarTiros();

    corpo.setSize(Vector2f(150.f, 150.f));
    centralizarEntidade();
    if (!textura.loadFromFile("boss.png")) {
        std::cerr << "Erro ao carregar a textura boss!" << std::endl;
    }
    else {
        corpo.setTexture(&textura);
    }
}
Chefao::~Chefao()
{
    cout << "destrutora chefao" << endl;
}

void Chefao::executar()
{
    escolherAlvo();
    mover();//mover inimigo
    if (pAlvo) {
        atirar(forca);
    }
    //tiros->percorrer();
}

void Chefao::salvar()
{
}

void Chefao::mover() {

	sofrerGravidade();
   
    if (pAlvo)
        perseguir();

    corpo.move(vel);


}

