#include "VelocityKalmanFilter.hpp"

#include <iostream>

VelocityKalmanFilter::VelocityKalmanFilter(const double timedelta)
    : KalmanFilter(4, 2) {
    // Initialize state vector to zeros
    _state = Eigen::VectorXd::Zero(_stateDimension);

    // Initialize state covariance matrix to identity (or some initial
    // uncertainty)
    _stateCovariance =
        Eigen::MatrixXd::Identity(_stateDimension, _stateDimension);

    // State transition matrix (F) for velocity model
    _stateTransition = Eigen::MatrixXd(_stateDimension, _stateDimension);
    _stateTransition << 1, 0, timedelta, 0.5 * timedelta * timedelta, 0, 1, 0,
        timedelta, 0, 0, 1, 0, 0, 0, 0, 1;

    _measurementMatrix =
        Eigen::MatrixXd(_measurementDimension, _stateDimension);
    _measurementMatrix << 1, 0, 0, 0, 0, 1, 0, 0;
}

StateAndCovariance VelocityKalmanFilter::step(const MeasurementData &data,
                                              const float timeDelta) {
    _stateTransition(0, 2) = timeDelta;
    _stateTransition(1, 3) = timeDelta;
    static const double maxCursorSpeed = 200;  // 200 pixels/second
    static const double maxCursorAcceleration =
        maxCursorSpeed / 0.1;  // we an reach the speed in 0.1 sec
    double sigma_a =
        0.20 * maxCursorAcceleration;     // 20% of 500 pixels/second^2
    double sigma_a2 = sigma_a * sigma_a;  // Square to get the variance

    _processNoise = Eigen::MatrixXd::Zero(_stateDimension, _stateDimension);
    _processNoise(0, 0) = std::pow(timeDelta, 4) / 4.0 * sigma_a2;
    _processNoise(0, 2) = std::pow(timeDelta, 3) / 2.0 * sigma_a2;
    _processNoise(1, 1) = std::pow(timeDelta, 4) / 4.0 * sigma_a2;
    _processNoise(1, 3) = std::pow(timeDelta, 3) / 2.0 * sigma_a2;
    _processNoise(2, 0) = std::pow(timeDelta, 3) / 2.0 * sigma_a2;
    _processNoise(2, 2) = std::pow(timeDelta, 2) * sigma_a2;
    _processNoise(3, 1) = std::pow(timeDelta, 3) / 2.0 * sigma_a2;
    _processNoise(3, 3) = std::pow(timeDelta, 2) * sigma_a2;

    auto predictedStateAndCovariance =
        predict(StateAndCovariance{_state, _stateCovariance});
    auto updatedStateAndCovariance = update(data, predictedStateAndCovariance);
    _state = updatedStateAndCovariance.state;
    _stateCovariance = updatedStateAndCovariance.covariance;

    return updatedStateAndCovariance;
}