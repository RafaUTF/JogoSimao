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
    try {
        carregarTextura("boss.png");
        corpo.setTexture(&textura);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        corpo.setFillColor(sf::Color::Red); // fallback color
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

