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
           + unitV(line_seg) * dot(unitV(line_seg), point - line_point1);
}

float interpolate(float t, float a, float b)
{
    return (b - a) * t + a;
}

sf::Vector2f interpolate(float t, sf::Vector2f a, sf::Vector2f b)
{
    return {interpolate(t, a.x, b.x), interpolate(t, a.y, b.y)};
}
