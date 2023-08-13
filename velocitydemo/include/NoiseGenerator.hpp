#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <random>

class NoiseGenerator {
   private:
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    Eigen::MatrixXd noiseCovarianceMatrix;

   public:
    NoiseGenerator(float noise);

    Eigen::VectorXd addNoise(const sf::Vector2f& input);

    const Eigen::MatrixXd& getNoiseCovarianceMatrix() const;
};