#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#ifndef ROOT_PATH
#define ROOT_PATH "."
#endif

const std::string fontPath = std::string(ROOT_PATH) + "/fonts/Roboto-Bold.ttf";

class Legend {
   private:
    sf::Font font;
    sf::RenderWindow &window;

   public:
    Legend(sf::RenderWindow &win);

    void draw(const std::vector<std::pair<sf::Color, std::string>> &items);
};
