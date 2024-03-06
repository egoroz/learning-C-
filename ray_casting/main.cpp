#include <iostream>
#include <SFML/Graphics.hpp>


int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ray casting", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Shader shader;
	shader.loadFromFile("shader.frag", sf::Shader::Fragment);
    
    while(window.isOpen()){
        sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
        }

        window.display();
    }

    return 0;
}