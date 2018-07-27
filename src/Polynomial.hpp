#pragma once

#include <array>

template<unsigned Order, typename ParamT = float>
class Polynomial
{
public:
    template<typename... ParamTs>
    Polynomial(ParamTs... params_);

    ParamT operator()(ParamT value_);

    const auto& getParams() const { return _params; }

private:
    std::array<ParamT, Order + 1> _params;
};

template<unsigned Order, typename ParamT>
Polynomial<Order - 1, ParamT>
    compute_derivative(const Polynomial<Order, ParamT>& polyn_,
                       int derivative_order_ = 1);

#include "Polynomial.inl"
