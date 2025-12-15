
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Config.hpp>
#include <iostream>

#include "../include/BodyRec.hpp"
#include "../include/CollisionRec.hpp"

int main()
{
    // Create a window (use Vector2u to be compatible with SFML 3)
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800u, 600u)), "Physics Engine SFML Demo");
    window.setFramerateLimit(60);

    // Create a simple body and a platform
    pe::BodyRec body(380.0, 50.0, 40.0, 40.0);
    pe::CollisionRec platform(0.0, 500.0, 800.0, 100.0);

    // set gravity on the body (constant force pointing down)
    body.setGravity(pe::Vector(0.0, 400.0));
    body.setMass(1.0);

    // Shapes for drawing
    sf::RectangleShape bodyShape(sf::Vector2f(static_cast<float>(body.getSizeX()), static_cast<float>(body.getSizeY())));
    bodyShape.setFillColor(sf::Color::Green);

    sf::RectangleShape platformShape(sf::Vector2f(800.f, 100.f));
    platformShape.setFillColor(sf::Color(150, 150, 150));
    platformShape.setPosition(sf::Vector2f(0.f, 500.f));

    sf::Clock clock;
    while (window.isOpen())
    {
        // Basic close on Escape (avoid relying on differing SFML event APIs)
        // Close on Escape key; API changed between SFML 2 and 3
#if defined(SFML_VERSION_MAJOR) && (SFML_VERSION_MAJOR >= 3)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
#else
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
#endif
            window.close();
            break;
        }

        // elapsed time in nanoseconds to match Java semantic used in project
        sf::Time dt = clock.restart();
        long elapsedNanos = static_cast<long>(dt.asSeconds() * 1e9);

        // Update physics
        platform.update(elapsedNanos);
        body.update(elapsedNanos);

        // Check collision
        pe::CollisionEvent ev = platform.collideWith(body);
        auto cols = ev.getCollisionPosition();
        if (cols[0] || cols[1] || cols[2] || cols[3])
        {
            bodyShape.setFillColor(sf::Color::Red);
        }
        else
        {
            bodyShape.setFillColor(sf::Color::Green);
        }

        // Draw
        window.clear(sf::Color::Black);
        // body relative position
        pe::Vector rel = body.getRelativePosition();
        bodyShape.setPosition(sf::Vector2f(static_cast<float>(rel.getX()), static_cast<float>(rel.getY())));
        window.draw(platformShape);
        window.draw(bodyShape);
        window.display();
    }

    return 0;
}
