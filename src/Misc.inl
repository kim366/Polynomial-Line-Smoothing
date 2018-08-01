#include <iostream>

template<int NumSegments = 50, typename PolynomialT>
std::array<sf::Vector2f, NumSegments>
    draw_function_graph(PolynomialT f_, sf::Vector2f from_, sf::Vector2f to_)
{
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
        const float progress{static_cast<float>(point_idx) / NumSegments};
        graph[point_idx].x = interpolate(progress, from_.x, to_.x);
        graph[point_idx].y =
            interpolate(progress, from_.y, to_.y) - f_(progress);
    }

    return graph;
}
