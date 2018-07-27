#pragma once

#include <array>

template<unsigned Order, typename ParamT = float>
class Polynomial
{
public:
    template<typename... ParamTs>
    Polynomial(ParamTs... params_);

    ParamT operator()(ParamT value_);

private:
    std::array<ParamT, Order + 1> _params;
};

#include "Polynomial.inl"
