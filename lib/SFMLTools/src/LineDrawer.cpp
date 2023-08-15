#include "LineDrawer.hpp"

#include <cmath>

LineDrawer::LineDrawer(sf::RenderTexture &rt, sf::Color col, float thickness)
    : _renderTexture(rt), _color(col), _thickness(thickness) {}

/**
 * @brief creates a thickline based on given arguments. in SFML you
 * cannot create a thicker line than 1 with just basic sf::Line, and
 * also the colors are weird in the normal line. This is a bit of
 * overkill just to display the line better because
 * this adds a bit computationally heavy operations just for
 * visuals
 * @param point1 first point from the line starts
 * @param point2 second point where the line ends
 * @returns vertex array containing vertexes that make up the line
 */
sf::VertexArray LineDrawer::createThickLine(const sf::Vector2f &point1,
                                            const sf::Vector2f &point2) {
    const static auto outlineColor = sf::Color::Transparent;
    const static auto outlineThickness = 0.f;

    sf::Vector2f direction = point2 - point1;
    sf::Vector2f unitDirection =
        direction /
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normal(-unitDirection.y, unitDirection.x);

    sf::Vector2f offset = (_thickness / 2.f) * normal;
    sf::Vector2f offsetOutline = (_thickness / 2.f + outlineThickness) * normal;

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

    for (unsigned int i = 4; i < 8; ++i) vertices[i].color = _color;

    return vertices;
}

void LineDrawer::addPoint(const sf::Vector2f &worldCoords) {
    if (_points.size() >= 200) {
        _points.erase(_points.begin());
    }
    _points.push_back(worldCoords);
}

void LineDrawer::draw() {
    if (_points.size() < 2) {
        return;  // Not enough points to draw a line
    }

    for (size_t i = 1; i < _points.size(); ++i) {
        sf::Vector2f p1 = _points[i - 1];
        sf::Vector2f p2 = _points[i];

        if (i < _points.size() - 1) {
            sf::Vector2f nextPoint = _points[i + 1];
            sf::Vector2f direction = (nextPoint - p1);
            direction /= std::sqrt(direction.x * direction.x +
                                   direction.y * direction.y);
            p2 += direction *
                  (_thickness *
                   0.5f);  // Adjust the endpoint of the current segment
        }

        sf::VertexArray thickLine = createThickLine(p1, p2);
        _renderTexture.draw(thickLine);
    }

    if (!_points.empty()) {
        const float radius = 5.0f;
        sf::CircleShape circle(radius);
        circle.setFillColor(_color);
        circle.setPosition(_points.back().x - radius,
                           _points.back().y - radius);
        _renderTexture.draw(circle);
    }
}
