#include "Misc.hpp"

#include <cmath>

namespace sf
{

std::ostream& operator<<(std::ostream& os_, const sf::Vector2f& vec_)
{
    os_ << vec_.x << ", " << vec_.y << '\n';
    return os_;
}

} // namespace sf

float dot(sf::Vector2f first_, sf::Vector2f second_)
{
    return first_.x * second_.x + first_.y * second_.y;
}

float mag(sf::Vector2f vec_)
{
    return std::hypot(vec_.x, vec_.y);
}

sf::Vector2f unitv(sf::Vector2f vec_)
{
    return vec_ / mag(vec_);
}

sf::Vector2f put_point_on_line(sf::Vector2f point,
                               sf::Vector2f line_point0,
                               sf::Vector2f line_point1)
{
    const sf::Vector2f line_seg{line_point1 - line_point0};
    return line_point1
           + unitv(line_seg) * dot(unitv(line_seg), point - line_point1);
}

float interpolate(float t, float a, float b)
{
    return (b - a) * t + a;
}

sf::Vector2f interpolate(float t, sf::Vector2f a, sf::Vector2f b)
{
    return {interpolate(t, a.x, b.x), interpolate(t, a.y, b.y)};
}

sf::Vector2f normal(sf::Vector2f vec_)
{
    return {-vec_.y, vec_.x};
}

std::vector<sf::Vector2f>
    construct_vertex_normals(const std::vector<sf::Vector2f>& points_)
{
    std::vector<sf::Vector2f> vertex_normals;
    vertex_normals.reserve(points_.size());

    vertex_normals.emplace_back(unitv(normal(points_[1] - points_[0])));

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

    vertex_normals.emplace_back(unitv(
        normal(points_[points_.size() - 1] - points_[points_.size() - 2])));

    // Flip first / last normal if facing wrong way
    for (auto idices : std::initializer_list<std::pair<unsigned, unsigned>>{
             {0, 1}, {vertex_normals.size() - 1, vertex_normals.size() - 2}})
        if (std::acos(dot(vertex_normals[idices.first],
                          vertex_normals[idices.second]))
            > .5f * pi)
            vertex_normals[idices.first] *= -1.f;

    return vertex_normals;
}
