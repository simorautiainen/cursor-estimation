#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "ExtendedVelocityKalmanFilter.hpp"
#include "Legend.hpp"
#include "LineDrawer.hpp"
#include "NoiseGenerator.hpp"
#include "NoisyVelocityKalmanModel.hpp"
#include "VelocityKalmanFilter.hpp"

int main() {
    //------------ smfl initializations
    using FilterAndLine = std::pair<NoisyVelocityKalmanModel, LineDrawer>;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Adjust as needed
    sf::RenderWindow window(sf::VideoMode(1200, 1000),
                            "Kalman Filter Cursor Tracking", sf::Style::Default,
                            settings);

    sf::RenderTexture renderTexture;
    renderTexture.create(window.getSize().x, window.getSize().y);

    //------------- kalman filter and line initializations
    std::vector<FilterAndLine> filtersAndLines;
    LineDrawer realLine(renderTexture, sf::Color::Red);

    // Initialize Kalman Filter
    double timedelta = 1.0 / 200.0;  // Assuming 60 FPS
    auto noisyModel = NoisyVelocityKalmanModel(
        std::make_unique<VelocityKalmanFilter>(timedelta), 25.0);
    auto lessNoisyModel = NoisyVelocityKalmanModel(
        std::make_unique<VelocityKalmanFilter>(timedelta), 5.0);
    auto evenMoreNoisyModel = NoisyVelocityKalmanModel(
        std::make_unique<VelocityKalmanFilter>(timedelta), 35.0);
    auto noisiestModel = NoisyVelocityKalmanModel(
        std::make_unique<VelocityKalmanFilter>(timedelta), 45.0);

    filtersAndLines.push_back(FilterAndLine(
        std::move(noisyModel), LineDrawer{renderTexture, sf::Color::Green}));
    filtersAndLines.push_back(
        FilterAndLine{std::move(lessNoisyModel),
                      LineDrawer{renderTexture, sf::Color::Yellow}});

    filtersAndLines.push_back(
        FilterAndLine{std::move(evenMoreNoisyModel),
                      LineDrawer{renderTexture, sf::Color::Magenta}});
    filtersAndLines.push_back(FilterAndLine{
        std::move(noisiestModel), LineDrawer{renderTexture, sf::Color::Blue}});

    VelocityKalmanFilter kalmanFilterNoisy(timedelta);
    VelocityKalmanFilter kalmanFilterLessNoisy(timedelta);

    // ------------------ Legend
    Legend legend(window);
    std::vector<std::pair<sf::Color, std::string>> legendItems = {
        {sf::Color::Red, "Actual Path"},
        {sf::Color::Yellow, "Noisy Kalman (Medium)"},
        {sf::Color::Green, "Noisy Kalman (High)"},
        {sf::Color::Magenta, "Noisy Kalman (Very High)"},
        {sf::Color::Blue, "Noisy Kalman (Highest)"}};

    // ------------------clock to print fps
    sf::Clock clock;
    float timeSinceLastLog = 0.0f;
    const float logInterval = 1.0f;  // Log every 1 second

    bool started = false;
    sf::Vector2f lastPosition;
    while (window.isOpen()) {
        float timedelta = clock.restart().asSeconds();
        timeSinceLastLog += timedelta;

        if (timeSinceLastLog >= logInterval) {
            float fps = 1.0f / timedelta;
            std::cout << "FPS: " << fps << std::endl;
            timeSinceLastLog = 0.0f;
        }
        renderTexture.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (!started &&
                       event.type == sf::Event::MouseButtonPressed) {
                started = true;
            } else if (started && event.type == sf::Event::MouseMoved) {
                sf::Vector2i point(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2f currentPosition = window.mapPixelToCoords(point);
                realLine.addPoint(currentPosition);
            }
        }
        if (started) {
            sf::Vector2i point = sf::Mouse::getPosition(window);
            sf::Vector2f currentPosition = window.mapPixelToCoords(point);
            for (auto &[model, line] : filtersAndLines) {
                auto pos = model.step(currentPosition, timedelta);
                line.addPoint(pos);
            }
            realLine.addPoint(currentPosition);
        }

        realLine.draw();
        for (auto &[_, line] : filtersAndLines) {
            line.draw();
        }
        renderTexture.display();  // Finalize drawing to the texture

        window.clear();
        sf::Sprite sprite(
            renderTexture.getTexture());  // Create a sprite from the texture
        window.draw(sprite);              // Draw the sprite to the window
        legend.draw(legendItems);
        window.display();
    }

    return 0;
}
