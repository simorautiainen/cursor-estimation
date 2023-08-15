#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#ifndef ROOT_PATH
#define ROOT_PATH "."
#endif

const std::string fontPath = std::string(ROOT_PATH) + "/fonts/Roboto-Bold.ttf";

/**
 * @brief draws legend on top left corner based on given colors and strings
 */
class Legend {
   private:
    sf::Font font;
    sf::RenderWindow &window;

   public:
    /**
     * @brief initializes the legend class, here we give the window as parameter
     * and font is got from this repo
     * @param win the window to which render this element
     */
    Legend(sf::RenderWindow &win);

    void draw(const std::vector<std::pair<sf::Color, std::string>> &items);
};
