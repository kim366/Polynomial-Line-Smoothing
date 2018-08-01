#include "Polynomial.hpp"

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

template<int NumSegments = 50>
std::vector<std::array<sf::Vector2f, NumSegments>>
    smooth_lines(const std::vector<sf::Vector2f>& points_)
{
    const float h{1}, pi{3.1415927f};
    std::vector<std::array<sf::Vector2f, NumSegments>> graphs;

    std::vector<sf::Vector2f> vertex_normals;

    // Construct vertex normals outward of
    for (unsigned point_idx = 1; point_idx < points_.size() - 1; ++point_idx)
    {
        // See notes 2018-08-01

        const sf::Vector2f away{
            unitv(points_[point_idx - 1] - points_[point_idx])},
            toward{unitv(points_[point_idx] - points_[point_idx + 1])};

        sf::Vector2f v_normal{unitv(normal(away + toward))};

        if (std::acos(dot(away, v_normal)) < .5f * pi)
            v_normal *= -1.f;

        vertex_normals.emplace_back(v_normal);
    }

    for (unsigned point_idx = 1; point_idx < points_.size(); ++point_idx)
    {
        graphs.emplace_back(
            draw_function_graph(Polynomial<3>{2.f * h, -3.f * h, h, 0.f},
                                points_[point_idx - 1],
                                points_[point_idx]));
    }

    return graphs;
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
