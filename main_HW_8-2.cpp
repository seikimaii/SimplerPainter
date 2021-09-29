#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
	
	sf::VideoMode mode(642,640);
	sf::RenderWindow window(mode,L"¤pµe®a");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		return EXIT_FAILURE;
	}
	sf::Text save("Image Saved!!", font);
	save.setFillColor(sf::Color::Black);
	save.setPosition(250.f, 0.f);
	sf::Texture background;
	if (!background.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}
	sf::Sprite backgroundSprite(background);
	backgroundSprite.setPosition(0, 40);
	sf::RenderTexture renderTexture;
	renderTexture.create(600, 560);
	renderTexture.clear(sf::Color::White);
	renderTexture.display();

	sf::CircleShape cursor(10);
	cursor.setOrigin(10, 10);
	cursor.setFillColor(sf::Color::Black);

	sf::Sprite renderSprite(renderTexture.getTexture());
	sf::Vector2f offset(20, 60);
	renderSprite.setPosition(offset);

	std::vector<sf::Color> colors = {
		sf::Color::Red, sf::Color::Black, sf::Color::Green,
		sf::Color(252,196,64), sf::Color(0,76,153), sf::Color::Cyan,
		sf::Color(255,204,153)
	};

	std::vector<sf::RectangleShape> swatch;
	for (size_t i = 0; i < colors.size(); i++) {
		sf::RectangleShape shape({ 20, 20 });
		shape.setOutlineColor(sf::Color(230, 230, 230));
		shape.setOutlineThickness(2);
		shape.setFillColor(colors[i]);
		shape.setPosition(float(20 + i * 20), 10.f);
		swatch.push_back(shape);
	}
	bool saved = false;
	while (window.isOpen()) {
		sf::Event evt;
		if (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				for (const auto& color : swatch) {
					if (color.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
						cursor.setFillColor(color.getFillColor());
					}
				}
				saved = false;
				break;
			case sf::Event::KeyPressed:
				//std::cout << evt.key.code << std::endl;
				switch (evt.key.code) {
				case sf::Keyboard::S:
					renderTexture.getTexture().copyToImage().saveToFile("test.png");
					saved = true;
					break;
				case sf::Keyboard::Num1:
					cursor.setFillColor(sf::Color::Red);
					break;
				case sf::Keyboard::Num2:
					cursor.setFillColor(sf::Color::Black);
					break;
				case sf::Keyboard::Num3:
					cursor.setFillColor(sf::Color::Green);
					break;
				}
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto pos = sf::Mouse::getPosition(window);
			cursor.setPosition(sf::Vector2f(pos) - offset);
			renderTexture.draw(cursor);
			renderTexture.display();
		}

		window.clear(sf::Color::White);
		for (const auto& s : swatch) {
			window.draw(s);
		}
		if (saved) {
			window.draw(save);
		}
		window.draw(backgroundSprite);
		window.draw(renderSprite);
		auto pos = sf::Mouse::getPosition(window);
		cursor.setPosition(sf::Vector2f(pos));
		window.draw(cursor);
		window.display();
	}

	return EXIT_SUCCESS;
}