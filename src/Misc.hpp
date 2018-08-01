#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <ostream>
#include <vector>

namespace sf
{
std::ostream& operator<<(std::ostream& os_, const sf::Vector2f& vec_);
}

void draw_lines(const std::vector<sf::Vector2f>& points_,
                sf::RenderTarget& target_,
                sf::Color color_ = sf::Color::White);
float dot(sf::Vector2f first_, sf::Vector2f second_);
float mag(sf::Vector2f vec_);
sf::Vector2f unitV(sf::Vector2f vec_);
float interpolate(float t, float a, float b);
sf::Vector2f interpolate(float t, sf::Vector2f a, sf::Vector2f b);
template<int NumSegments = 50, typename PolynomialT>
std::array<sf::Vector2f, NumSegments>
    draw_function_graph(PolynomialT, sf::Vector2f from_, sf::Vector2f to_);

#include "Misc.inl"
