#include "LineDrawer.hpp"

#include <cmath>

LineDrawer::LineDrawer(sf::RenderTexture &rt, sf::Color col)
    : renderTexture(rt), color(col) {}

static sf::VertexArray createThickLine(
    const sf::Vector2f &point1, const sf::Vector2f &point2,
    const sf::Color &color, float thickness,
    const sf::Color &outlineColor = sf::Color::Transparent,
    float outlineThickness = 0.f) {
    sf::Vector2f direction = point2 - point1;
    sf::Vector2f unitDirection =
        direction /
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normal(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (thickness / 2.f) * normal;
    sf::Vector2f offsetOutline = (thickness / 2.f + outlineThickness) * normal;

    sf::VertexArray vertices(sf::Quads, 8);

    vertices[0].position = point1 + offsetOutline;
    vertices[1].position = point2 + offsetOutline;
    vertices[2].position = point2 - offsetOutline;
    vertices[3].position = point1 - offsetOutline;

    for (unsigned int i = 0; i < 4; ++i) vertices[i].color = outlineColor;

    vertices[4].position = point1 + offset;
    vertices[5].position = point2 + offset;
    vertices[6].position = point2 - offset;
    vertices[7].position = point1 - offset;

    for (unsigned int i = 4; i < 8; ++i) vertices[i].color = color;

    return vertices;
}

void LineDrawer::addPoint(const sf::Vector2f &worldCoords) {
    if (points.size() >= 200) {
        points.erase(points.begin());
    }
    points.push_back(worldCoords);
}
void LineDrawer::draw() {
    if (points.size() < 2) {
        return;  // Not enough points to draw a line
    }

    static float thickness = 5.0f;  // Adjust as needed

    for (size_t i = 1; i < points.size(); ++i) {
        sf::Vector2f p1 = points[i - 1];
        sf::Vector2f p2 = points[i];

        if (i < points.size() - 1) {
            sf::Vector2f nextPoint = points[i + 1];
            sf::Vector2f direction = (nextPoint - p1);
            direction /= std::sqrt(direction.x * direction.x +
                                   direction.y * direction.y);
            p2 += direction *
                  (thickness *
                   0.5f);  // Adjust the endpoint of the current segment
        }

        sf::VertexArray thickLine = createThickLine(p1, p2, color, thickness);
        renderTexture.draw(thickLine);
    }

    if (!points.empty()) {
        const float radius = 5.0f;
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setPosition(points.back().x - radius, points.back().y - radius);
        renderTexture.draw(circle);
    }
}
