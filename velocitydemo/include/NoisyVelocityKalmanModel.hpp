#pragma once
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <memory>

#include "NoiseGenerator.hpp"
#include "VelocityKalmanFilter.hpp"

class NoisyVelocityKalmanModel {
   private:
    NoiseGenerator _noise;
    std::unique_ptr<VelocityKalmanFilter> _model;

   public:
    NoisyVelocityKalmanModel(
        std::unique_ptr<VelocityKalmanFilter>&& kalmanFilter,
        const float noise = 5.0);
    sf::Vector2f step(const sf::Vector2f& worldCoords);
    sf::Vector2f step(const sf::Vector2f& worldCoords, const float timeDelta);
};