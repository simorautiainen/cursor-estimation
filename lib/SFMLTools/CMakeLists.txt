add_library(SFMLTools src/LineDrawer.cpp src/Legend.cpp)


target_include_directories(SFMLTools PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(SFMLTools sfml-graphics)