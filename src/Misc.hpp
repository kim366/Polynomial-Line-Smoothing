#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <ostream>
#include <vector>

const float pi{3.1415927f};

namespace sf
{
std::ostream& operator<<(std::ostream& os_, const sf::Vector2f& vec_);
}

template<typename ContainerT>
void draw_lines(const ContainerT& points_,
                sf::RenderTarget& target_,
                sf::Color color_ = sf::Color::White);
float dot(sf::Vector2f first_, sf::Vector2f second_);
float mag(sf::Vector2f vec_);
sf::Vector2f normal(sf::Vector2f vec_);
sf::Vector2f unitv(sf::Vector2f vec_);
float interpolate(float t, float a, float b);
sf::Vector2f interpolate(float t, sf::Vector2f a, sf::Vector2f b);

template<int NumSegments = 50, typename PolynomialT>
std::array<sf::Vector2f, NumSegments>
    draw_function_graph(PolynomialT f_, sf::Vector2f from_, sf::Vector2f to_);

template<int NumSegments = 50>
std::vector<std::array<sf::Vector2f, NumSegments>>
    smooth_lines(const std::vector<sf::Vector2f>& points_);

std::vector<sf::Vector2f>
    construct_vertex_normals(const std::vector<sf::Vector2f>& points_);

std::vector<float>
    compute_slopes(const std::vector<sf::Vector2f>& points_,
                   const std::vector<sf::Vector2f>& vertex_normals_);

#include "Misc.inl"
