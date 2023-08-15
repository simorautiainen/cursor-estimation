#include "Legend.hpp"

Legend::Legend(sf::RenderWindow &win) : window(win) {
    std::cout << fontPath << std::endl;
    if (!font.loadFromFile(fontPath)) {
        // Handle error
    }
}

void Legend::draw(const std::vector<std::pair<sf::Color, std::string>> &items) {
    float yOffset = 10;  // Start position
    for (const auto &item : items) {
        sf::RectangleShape colorBox(sf::Vector2f(20, 20));
        colorBox.setFillColor(item.first);
        colorBox.setPosition(10, yOffset);

        sf::Text label(item.second, font, 20);
        label.setPosition(40, yOffset);

        window.draw(colorBox);
        window.draw(label);

        yOffset += 30;  // Move down for next item
    }
}