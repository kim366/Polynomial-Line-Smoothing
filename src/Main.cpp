#include "Misc.hpp"
#include "Polynomial.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
    const sf::ContextSettings aa_8x{0, 0, 8};
    sf::RenderWindow window(
        {350, 350}, "Draw Function Graph", sf::Style::Default, aa_8x);

    float h{1};
    std::vector<sf::Vector2f> points;
    std::vector<sf::Vector2f> smooth_points;

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
                const sf::Vector2f mpos{
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)};

                points.push_back(mpos);

                smooth_points = draw_continuous_function_graphs(
                    Polynomial<3>{2.f * h, -3.f * h, h, 0.f}, points);
            }

            else if (event.type == sf::Event::KeyPressed
                     && event.key.code == sf::Keyboard::Up)
                ++h;

            else if (event.type == sf::Event::KeyPressed
                     && event.key.code == sf::Keyboard::Down)
                --h;
        }

        window.clear();

        draw_lines(points, window, sf::Color::Red);
        for (const auto& graph : graphs)
            draw_lines(graph, window);

        window.display();
    }
}
