#include <iostream>

template<int NumSegments = 50, typename PolynomialT>
std::array<sf::Vector2f, NumSegments>
    draw_function_graph(PolynomialT f_, sf::Vector2f from_, sf::Vector2f to_)
{
    const sf::Vector2f unit_normal{unitv(normal(to_ - from_))};

    std::array<sf::Vector2f, NumSegments> graph;
    const float x_axis_mag{mag(from_ - to_)};

    // Transform params from 0 - 1 to 0 - lentgh of x-axis
    // thus correcting f'(0)
    auto transformed_params{std::move(f_.getParams())};
    for (auto& param : transformed_params)
        param *= x_axis_mag;
    f_.setParams(std::move(transformed_params));

    for (int point_idx{0}; point_idx < NumSegments; ++point_idx)
    {
        const float progress{static_cast<float>(point_idx) / (NumSegments - 1)};
        graph[point_idx] =
            interpolate(progress, from_, to_) - sf::Vector2f{0.f, f_(progress)};
    }

    return graph;
}

template<typename ContainerT>
void draw_lines(const ContainerT& points_,
                sf::RenderTarget& target_,
                sf::Color color_)
{
    for (auto point{points_.cbegin()}; point != points_.cend();)
    {
        auto cur_point{point};
        if (++point != points_.cend())
        {
            sf::Vertex line[2]{{*cur_point, color_}, {*point, color_}};

            target_.draw(line, 2, sf::Lines);
        }
    }
}
