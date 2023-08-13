#pragma once
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <memory>

#include "NoiseGenerator.hpp"
#include "VelocityKalmanFilter.hpp"

/**
 * @brief a wrapper for the noise and model to easily add new points
 */
class NoisyVelocityKalmanModel {
   private:
    NoiseGenerator _noise;
    std::unique_ptr<VelocityKalmanFilter> _model;

   public:
    NoisyVelocityKalmanModel(
        std::unique_ptr<VelocityKalmanFilter>&& kalmanFilter,
        const float noise = 5.0);

    /**
     * @brief adds noise to the coords and gives them to the velocity kalman
     * filter and returns the estimation
     * @param worldCoords the actual cursor position transferred to world coords
     * world = we can zoom in SFML window and the line can get out of the window
     * so if we have world coords, we can still kinda draw the lines but they
     * are out of screen. Thats why we don't need to worry about drawing the
     * Vertexes out of screen, because we give them as worldcoords.
     * @returns the  new state of the kalman filter
     */
    sf::Vector2f step(const sf::Vector2f& worldCoords);

    /**
     * @brief adds noise to the coords and gives them to the velocity kalman
     * filter and returns the estimation
     * @param worldCoords the actual cursor position transferred to world coords
     * world = we can zoom in SFML window and the line can get out of the window
     * so if we have world coords, we can still kinda draw the lines but they
     * are out of screen. Thats why we don't need to worry about drawing the
     * Vertexes out of screen, because we give them as worldcoords.
     * @param timeDelta the time between given point and the last given point
     * @returns the  new state of the kalman filter
     */
    sf::Vector2f step(const sf::Vector2f& worldCoords, const float timeDelta);
};