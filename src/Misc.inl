#include <iostream>

template<int NumSegments = 50, typename PolynomialT>
std::array<sf::Vector2f, NumSegments>
    draw_function_graph(PolynomialT f_, sf::Vector2f from_, sf::Vector2f to_)
{
    const sf::Vector2f direction{to_ - from_},
        unit_normal{unitv(normal(direction))}, unit_direct{unitv(direction)};

    const float tilt_sin{unit_direct.y}, tilt_cos{unit_direct.x},
        x_axis_mag{mag(direction)};

    std::array<sf::Vector2f, NumSegments> graph;

    // Transform params from 0 - 1 to 0 - lentgh of x-axis
    // thus correcting f'(0)
    auto transformed_params{std::move(f_.getParams())};
    for (auto& param : transformed_params)
        param *= x_axis_mag;
    f_.setParams(std::move(transformed_params));

    for (int point_idx{0}; point_idx < NumSegments; ++point_idx)
    {
        const float x{static_cast<float>(point_idx) / (NumSegments - 1)},
            y{f_(x)};
        graph[point_idx] = interpolate(x, from_, to_)
                           // rotation matrix
                           - sf::Vector2f{x * tilt_cos - y * tilt_sin,
                                          x * tilt_sin + y * tilt_cos};
    }

    return graph;
}

template<int NumSegments = 50, typename PolynomialT>
std::vector<sf::Vector2f>
    draw_continuous_function_graphs(PolynomialT f_,
                                    const std::vector<sf::Vector2f>& points_)
{
    return {};
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
