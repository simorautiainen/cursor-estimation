add_library(Kalman src/VelocityKalmanFilter.cpp src/KalmanFilter.cpp)
find_package(Eigen3 REQUIRED)

target_include_directories(Kalman PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Kalman Eigen3::Eigen)