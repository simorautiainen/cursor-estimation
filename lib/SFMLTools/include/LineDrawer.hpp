#pragma once

#include <SFML/Graphics.hpp>

class LineDrawer {
   private:
    sf::RenderTexture &renderTexture;
    sf::Color color;
    sf::Vector2f lastPoint;
    bool hasLastPoint;
    sf::CircleShape lastCircle;
    std::vector<sf::Vector2f> points;  // Store all points
   public:
    LineDrawer(sf::RenderTexture &rt, sf::Color col);
    void addPoint(const sf::Vector2f &worldCoords);
    void draw();
};
