#pragma once
#include "KalmanFilter.hpp"

class ExtendedVelocityKalmanFilter : public KalmanFilter {
   public:
    ExtendedVelocityKalmanFilter(const double timedelta);

    StateAndCovariance step(const MeasurementData& data);
};