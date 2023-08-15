#include "NoisyVelocityKalmanModel.hpp"

NoisyVelocityKalmanModel::NoisyVelocityKalmanModel(
    std::unique_ptr<VelocityKalmanFilter>&& kalmanFilter, const float noise)
    : _model(std::move(kalmanFilter)), _noise(NoiseGenerator(noise)) {}

sf::Vector2f NoisyVelocityKalmanModel::step(const sf::Vector2f& worldCoords,
                                            const float timeDelta) {
    MeasurementData noisyData;
    noisyData.measurement = _noise.addNoise(worldCoords);
    noisyData.noiseCovarianceMatrix = _noise.getNoiseCovarianceMatrix();

    auto updatedState = _model->step(noisyData, timeDelta);
    sf::Vector2f pos(updatedState.state(0), updatedState.state(1));
    return pos;
}