#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief A support class that allows drawing lines between last 200 points
 * which means it shows as a tail between latest point and current point
 */
class LineDrawer {
   private:
    sf::RenderTexture &_renderTexture;
    sf::Color _color;
    std::vector<sf::Vector2f> _points;  // Store all points
    float _thickness;

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
    sf::VertexArray createThickLine(const sf::Vector2f &point1,
                                    const sf::Vector2f &point2);

   public:
    /**
     * @brief Initializes the class. We use a render texture
     * (`sf::RenderTexture`) instead of directly drawing to the window. This
     * approach allows us to draw lines on an off-screen canvas (or back buffer)
     * before displaying the final image.We do this because we want to clear the
     * buffer each time without showing that to the user since this class
     * draws a trailing tail between the point and past points
     * @param rt The off-screen canvas (render texture) that will be used for
     * drawing. It should be linked to the main window.
     * @param col The color of the lines to be drawn.
     */
    LineDrawer(sf::RenderTexture &rt, sf::Color col,
               const float thickness = 5.0f);

    /**
     * @brief adds point to the std::vector which gets drawn in draw.
     * @param worldCoords point of where to draw newest line in the world
     * world = we can zoom in SFML window and the line can get out of the window
     * so if we have world coords, we can still kinda draw the lines but they
     * are out of screen. Thats why we don't need to worry about drawing the
     * Vertexes out of screen, because we give them as worldcoords.
     * @attention if user gives the coords in some other than worldcoords this
     * probably don't work
     */
    void addPoint(const sf::Vector2f &worldCoords);

    /**
     * @brief draws lines between consecutive points in the points array
     * does some magic with the library and the angles so the line is smooth
     */
    void draw();
};
