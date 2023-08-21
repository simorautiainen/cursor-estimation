find_package(Eigen3 REQUIRED)

# Create a library from your application's sources
add_library(VelocityDemoLib
    src/NoiseGenerator.cpp
    src/NoisyVelocityKalmanModel.cpp
    include/NoiseGenerator.hpp
    include/NoisyVelocityKalmanModel.hpp
)

# Specify where the compiler can find the header files (if they're not in the same directory as the source files)
target_include_directories(VelocityDemoLib PUBLIC include)

# Create your main executable
add_executable(VelocityDemo src/main.cpp)

target_link_libraries(VelocityDemoLib PUBLIC Eigen3::Eigen sfml-graphics SFMLTools Kalman)

# For MainApp, you only need to link AppLib, as it will transitively get the dependencies from AppLib
target_link_libraries(VelocityDemo VelocityDemoLib)