// KalmanFilter.hpp
#pragma once

#include <Eigen/Dense>

struct MeasurementData {
    Eigen::VectorXd measurement;
    Eigen::MatrixXd noiseCovarianceMatrix;  // Measurement noise covariance
};

struct StateAndCovariance {
    Eigen::VectorXd state;
    Eigen::MatrixXd covariance;  // Measurement noise covariance
};

class KalmanFilter {
   public:
    // Constructor
    KalmanFilter(size_t stateDim, size_t measDim)
        : _stateDimension(stateDim), _measurementDimension(measDim) {}

    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~KalmanFilter() {}

    // Predict the next state
    StateAndCovariance predict(
        const StateAndCovariance& previousStateAndCovariance) const;
    StateAndCovariance predict(
        const StateAndCovariance& previousStateAndCovariance,
        const Eigen::MatrixXd& stateTransition);

    // Update the state based on the measurement
    StateAndCovariance update(
        const MeasurementData& data,
        const StateAndCovariance& predictedStateAndCovariance) const;

    // Get the current state estimate
    Eigen::VectorXd getStateEstimate() const { return _state; }

    // ... other common methods or utilities ...

   protected:
    size_t _stateDimension;
    size_t _measurementDimension;
    Eigen::VectorXd _state;              // State vector
    Eigen::MatrixXd _stateCovariance;    // State covariance matrix
    Eigen::MatrixXd _processNoise;       // Process noise covariance matrix
    Eigen::MatrixXd _stateTransition;    // State transition matrix
    Eigen::MatrixXd _measurementMatrix;  // Measurement matrix
};
