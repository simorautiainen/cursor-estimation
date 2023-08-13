#include "KalmanFilter.hpp"

#include <iostream>

StateAndCovariance KalmanFilter::predict(
    const StateAndCovariance &previousStateAndCovariance,
    const Eigen::MatrixXd &stateTransition) {
    auto state = stateTransition * previousStateAndCovariance.state;
    auto stateCovariance = stateTransition *
                               previousStateAndCovariance.covariance *
                               stateTransition.transpose() +
                           _processNoise;
    return StateAndCovariance{state, stateCovariance};
}

StateAndCovariance KalmanFilter::predict(
    const StateAndCovariance &previousStateAndCovariance) const {
    auto state = _stateTransition * previousStateAndCovariance.state;
    auto stateCovariance = _stateTransition *
                               previousStateAndCovariance.covariance *
                               _stateTransition.transpose() +
                           _processNoise;
    return StateAndCovariance{state, stateCovariance};
}

StateAndCovariance KalmanFilter::update(
    const MeasurementData &data,
    const StateAndCovariance &previousStateAndCovariance) const {
    previousStateAndCovariance.covariance *_measurementMatrix.transpose();

    auto kalmanGain =
        previousStateAndCovariance.covariance * _measurementMatrix.transpose() *
        (_measurementMatrix * previousStateAndCovariance.covariance *
             _measurementMatrix.transpose() +
         data.noiseCovarianceMatrix)
            .inverse();

    auto state =
        previousStateAndCovariance.state +
        kalmanGain * (data.measurement -
                      _measurementMatrix * previousStateAndCovariance.state);
    auto stateCovariance =
        (Eigen::MatrixXd::Identity(_stateDimension, _stateDimension) -
         kalmanGain * _measurementMatrix) *
        previousStateAndCovariance.covariance;
    return StateAndCovariance{state, stateCovariance};
}