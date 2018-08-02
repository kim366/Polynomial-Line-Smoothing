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
    if (points_.size() < 3)
        return {};

    std::vector<std::array<sf::Vector2f, NumSegments>> graphs;
    const auto vertex_normals{construct_vertex_normals(points_)};
    const auto slopes{compute_slopes(points_, vertex_normals)};

    enum Direction : bool
    {
        Left,
        Right
    };

    std::vector<Direction> directions{points_.size()};

    for (unsigned point_idx{1}; point_idx < points_.size() - 1; ++point_idx)
    {
        const sf::Vector2f to_point_unit{
            unitv(points_[point_idx] - points_[point_idx - 1])},
            from_point_unit{unitv(points_[point_idx + 1] - points_[point_idx])};

        float angle_left{
            std::acos(dot(normal(to_point_unit), from_point_unit))},
            angle_right{
                std::acos(dot(normal(to_point_unit * -1.f), from_point_unit))};

        // Why `>` ???
        directions[point_idx] = angle_left > angle_right ? Left : Right;
    }

    directions[0] = directions[1];
    directions[directions.size() - 1] = directions[directions.size() - 2];

    for (unsigned point_idx{0}; point_idx < points_.size() - 1; ++point_idx)
    {
        float slope_begin{slopes[point_idx]}, slope_end{-slopes[point_idx + 1]};

        if (directions[point_idx] == Left)
        {
            slope_begin *= -1.f;
            slope_end *= -1.f;
        }

        if (point_idx < directions.size() - 1
            && directions[point_idx] != directions[point_idx + 1])
            slope_end *= -1.f;

        graphs.emplace_back(
            draw_function_graph(Polynomial<3>{slope_begin + slope_end,
                                              -2.f * slope_begin - slope_end,
                                              slope_begin,
                                              0.f},
                                points_[point_idx],
                                points_[point_idx + 1]));
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
