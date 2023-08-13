#include "VelocityKalmanFilter.hpp"

VelocityKalmanFilter::VelocityKalmanFilter(const double timedelta)
    : KalmanFilter(4, 2) {
    // Initialize state vector to zeros
    _state = Eigen::VectorXd::Zero(_stateDimension);

    // Initialize state covariance matrix to identity (or some initial
    // uncertainty)
    _stateCovariance =
        Eigen::MatrixXd::Identity(_stateDimension, _stateDimension);

    // Initialize process noise covariance matrix (Q). This might need tuning
    // based on system's behavior.
    _processNoise = Eigen::MatrixXd::Identity(_stateDimension, _stateDimension);
    _processNoise.diagonal() << 0.1, 0.1, 0.1, 0.1;

    // State transition matrix (F) for velocity model
    _stateTransition = Eigen::MatrixXd(_stateDimension, _stateDimension);
    _stateTransition << 1, 0, timedelta, 0, 0, 1, 0, timedelta, 0, 0, 1, 0, 0,
        0, 0, 1;
    _measurementMatrix =
        Eigen::MatrixXd(_measurementDimension, _stateDimension);
    _measurementMatrix << 1, 0, 0, 0, 0, 1, 0, 0;
    // Store F in a member variable if needed for later use
}

StateAndCovariance VelocityKalmanFilter::step(const MeasurementData &data) {
    auto predictedStateAndCovariance =
        predict(StateAndCovariance{_state, _stateCovariance});
    auto updatedStateAndCovariance = update(data, predictedStateAndCovariance);
    _state = updatedStateAndCovariance.state;
    _stateCovariance = updatedStateAndCovariance.covariance;
    return updatedStateAndCovariance;
}

StateAndCovariance VelocityKalmanFilter::step(const MeasurementData &data,
                                              const float timeDelta) {
    _stateTransition(0, 2) = timeDelta;
    _stateTransition(1, 3) = timeDelta;
    auto predictedStateAndCovariance =
        predict(StateAndCovariance{_state, _stateCovariance});
    auto updatedStateAndCovariance = update(data, predictedStateAndCovariance);
    _state = updatedStateAndCovariance.state;
    _stateCovariance = updatedStateAndCovariance.covariance;
    return updatedStateAndCovariance;
}