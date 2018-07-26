template<int NumSegments = 50>
std::array<sf::Vector2f, NumSegments> draw_function_graph(float (*fn)(float),
                                                          sf::Vector2f from_,
                                                          sf::Vector2f to_)
{
    std::array<sf::Vector2f, NumSegments> graph;

    for (int point_idx{0}; point_idx < NumSegments; ++point_idx)
    {
        const float progress{static_cast<float>(point_idx) / NumSegments};
        graph[point_idx].x = interpolate(progress, from_.x, to_.x);
        graph[point_idx].y =
            interpolate(progress, from_.y, to_.y) - fn(progress);
    }

    return graph;
}
