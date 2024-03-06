#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Ray casting", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    getchar();
    return 0;
}