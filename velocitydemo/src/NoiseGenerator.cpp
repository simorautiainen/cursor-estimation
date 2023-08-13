#include "NoiseGenerator.hpp"

NoiseGenerator::NoiseGenerator(float noise) : distribution(0.0, noise) {
    noiseCovarianceMatrix = Eigen::MatrixXd::Identity(2, 2) * noise * noise;
}

Eigen::VectorXd NoiseGenerator::addNoise(const sf::Vector2f& input) {
    Eigen::VectorXd noisyMeasurement(2);
    noisyMeasurement << input.x + distribution(generator),
        input.y + distribution(generator);
    return noisyMeasurement;
}

const Eigen::MatrixXd& NoiseGenerator::getNoiseCovarianceMatrix() const {
    return noiseCovarianceMatrix;
}