#pragma once
#include "KalmanFilter.hpp"

class VelocityKalmanFilter : public KalmanFilter {
   public:
    VelocityKalmanFilter(const double timedelta);

    StateAndCovariance step(const MeasurementData& data);
    StateAndCovariance step(const MeasurementData& data, const float timeDelta);
};