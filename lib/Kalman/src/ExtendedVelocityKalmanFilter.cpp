#include "ExtendedVelocityKalmanFilter.hpp"

ExtendedVelocityKalmanFilter::ExtendedVelocityKalmanFilter(
    const double timedelta)
    : KalmanFilter(4, 4) {
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
    _measurementMatrix << Eigen::MatrixXd::Identity(_stateDimension,
                                                    _stateDimension);
    // Store F in a member variable if needed for later use
}

StateAndCovariance ExtendedVelocityKalmanFilter::step(
    const MeasurementData &data) {
    auto predictedStateAndCovariance =
        predict(StateAndCovariance{_state, _stateCovariance});
    auto updatedStateAndCovariance = update(data, predictedStateAndCovariance);
    _state = updatedStateAndCovariance.state;
    _stateCovariance = updatedStateAndCovariance.covariance;
    return updatedStateAndCovariance;
}