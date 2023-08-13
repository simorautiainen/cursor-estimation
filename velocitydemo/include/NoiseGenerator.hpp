#pragma once

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <random>

/**
 * @brief a helper class to add noise to inputs and provide the noise covariance
 * matrix for kalman filter
 */
class NoiseGenerator {
   private:
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    Eigen::MatrixXd noiseCovarianceMatrix;

   public:
    /**
     * @brief initializes the noise generator and the covariance matrix based on
     * given noise
     * @param noise gaussian noise variance meaning the pixels which gets added
     * to the actual inputs
     */
    NoiseGenerator(float noise);

    /**
     * @brief adds noise to the actual cursor input
     * @param input coordinates which to add the gaussian noise
     * @returns noisy coordinates
     */
    Eigen::VectorXd addNoise(const sf::Vector2f& input);

    /**
     * @brief helper function to get the covariance matrix
     * @returns the noise covariance matrix
     */
    const Eigen::MatrixXd& getNoiseCovarianceMatrix() const;
};