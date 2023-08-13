#pragma once
#include "KalmanFilter.hpp"

/**
 * @brief This is the velocity kalman filter with measurement dim of 2
 * idea is you only give position but the state transition matrix calculates the
 * predicted velocity based on new point and latest point. The naming is a bit
 * off because velocity model also means a model where measurement dim is 4 and
 * you give the measured velocity as well as the position
 */
class VelocityKalmanFilter : public KalmanFilter {
   public:
    /**
     * @brief initializes the state and process noise and state transition and
     * measurement matrixes
     * @param timedelta is the static time delta, can be a random value if you
     * use the step method with timeDelta
     */
    VelocityKalmanFilter(const double timedelta = 0.f);

    /**
     * @brief calls the kalman filters predict and update steps based on given
     * data
     * @param data the newest data point
     * @returns the new state of the model
     */
    StateAndCovariance step(const MeasurementData& data);

    /**
     * @brief calls the kalman filters predict and update steps based on given
     * data and edits the state transition matrix with timeDelta, so the time
     * between points is correct. This allows us to have arbitary time between
     * the measured points, and we don't need a static measurement rate
     * @param data the newest data point
     * @param timeDelta the time between this and the last point
     * @returns the new state of the model
     */
    StateAndCovariance step(const MeasurementData& data, const float timeDelta);
};