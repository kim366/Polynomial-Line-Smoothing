#include "ConnectedBezierCurves.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    const sf::ContextSettings aa_8x{0, 0, 8};
    sf::RenderWindow window(
        {350, 350}, "SFML Bezier", sf::Style::Default, aa_8x);

    while (true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed
                || (event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Escape))
                return 0;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mpos{static_cast<float>(event.mouseButton.x),
                                  static_cast<float>(event.mouseButton.y)};
                curves.addPoint(mpos);
            }
        }

        window.clear();
        window.display();
    }
}
