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

/**
 * @brief the kalman filter base class. Idea is to have a generic predict and
 * update steps and the derived class will implement a correct constructor where
 * the matrices are initialized accordingly to the physics what the model is
 * trying to model
 */
class KalmanFilter {
   public:
    /**
     * @brief constructor that initializes the statedim and measurement dims
     * @param stateDim is the dimension of states, how many states the model has
     * @param measdim the measurement dim, how many measurements are given for
     * the model
     */
    KalmanFilter(size_t stateDim, size_t measDim)
        : _stateDimension(stateDim), _measurementDimension(measDim) {}

    /**
     * @brief uses the state and covariance matrices of previous step to
     * calculate the predicted ones
     * @param previousStateAndCovariance contains the previous state vector and
     * covariance matrix
     */
    StateAndCovariance predict(
        const StateAndCovariance& previousStateAndCovariance) const;

    /**
     * @brief uses the state and covariance matrices of previous step and the
     * stateTransition matrix to calculate the predicted state and covariance
     * matrices.
     * Why we want to edit the state transition matrix and give a new one for
     * predicting?
     *   - there are kalman filter models where you want to edit the parameters
     * of state transition matrix, for example the timedelta in velocity model.
     * But if you get measurements with static timedelta intervals, you don't
     * need to use this predict for velocity model.
     *
     * @param previousStateAndCovariance contains the previous state vector and
     * covariance matrix
     * @param stateTransition the state transition matrix based on which the
     * predicted states are calculated
     */
    StateAndCovariance predict(
        const StateAndCovariance& previousStateAndCovariance,
        const Eigen::MatrixXd& stateTransition);

    /**
     * @brief the update step of the kalman filter, based on given data and the
     * predicted steps output, this returns the new state and covariance
     * matrices.
     * @param data containing the measured data and measured/estimated
     * noiseCovariance matrix
     * @param predictedStateAndCovariance the matrices from predict step
     * @returns kalman filters output which is the new state matrices
     */
    StateAndCovariance update(
        const MeasurementData& data,
        const StateAndCovariance& predictedStateAndCovariance) const;

   protected:
    size_t _stateDimension;
    size_t _measurementDimension;
    Eigen::VectorXd _state;              // State vector
    Eigen::MatrixXd _stateCovariance;    // State covariance matrix
    Eigen::MatrixXd _processNoise;       // Process noise covariance matrix
    Eigen::MatrixXd _stateTransition;    // State transition matrix
    Eigen::MatrixXd _measurementMatrix;  // Measurement matrix
};
