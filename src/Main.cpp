#include "Misc.hpp"
#include "Polynomial.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    const sf::ContextSettings aa_8x{0, 0, 8};
    sf::RenderWindow window(
        {350, 350}, "Draw Function Graph", sf::Style::Default, aa_8x);

    const float h{1};
    const std::array<sf::Vector2f, 2> points{{{50.f, 200.f}, {300.f, 400.f}}};
    auto graph{draw_function_graph(
        Polynomial<3>{2.f * h, -3.f * h, h, 0.f}, points[0], points[1])};

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
                // sf::Vector2f mpos{static_cast<float>(event.mouseButton.x)
                // static_cast<float>(event.mouseButton.y)};
            }
        }

        window.clear();

        draw_lines(points, window, sf::Color::Red);
        draw_lines(graph, window);

        window.display();
    }
}
