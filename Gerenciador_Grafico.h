#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Ente;
namespace Entidades {
	class Entidade;
}

namespace Gerenciadores {

	class Gerenciador_Grafico
	{
	private:

		sf::RenderWindow* janela;
		sf::Sprite fundo;
		sf::Texture textura;

		sf::View camera;

		Gerenciador_Grafico();

	public:

		~Gerenciador_Grafico();
		sf::RenderWindow* getWindow();
		const bool aberta() const;
		void clear();
		void desenhar(Ente* pE = NULL);
		void desenhar(const sf::RectangleShape& retangulo);
		void desenhaFundo();
		void mostrar();
		void fechar();

		void moverCamera(Entidades::Entidade* p1 = NULL, Entidades::Entidade* p2 = NULL);

		static Gerenciador_Grafico* getInstancia();

		void setJanelaExterna(sf::RenderWindow* j);
	};
}