#pragma once

template<int NumSegments = 50>
std::array<sf::Vector2f, NumSegments> draw_function_graph(float (*fn)(float),
                                                          sf::Vector2f from_,
                                                          sf::Vector2f to_)
{
    std::array<sf::Vector2f, NumSegments> graph;

    for (int point_idx = 0; point_idx < NumSegments; ++point_idx)
    {
        graph[point_idx] = vinterpolate(
            static_cast<float>(point_idx) / NumSegments, from_, to_);
    }

    return graph;
}
