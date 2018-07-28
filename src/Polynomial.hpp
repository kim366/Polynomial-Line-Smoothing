#pragma once

#include <array>

template<unsigned Order, typename ParamT = float>
class Polynomial
{
public:
    using ParamArrT = std::array<ParamT, Order + 1>;

    template<typename... ParamTs>
    Polynomial(ParamTs... params_);

    ParamT operator()(ParamT value_);

    const auto& getParams() const { return _params; }
    ParamT getParam(unsigned index_) const { return _params[index_]; }

private:
    ParamArrT _params;
};

template<unsigned Order, typename ParamT, int DerivativeOrder = 1>
Polynomial<Order - DerivativeOrder, ParamT>
    compute_derivative(const Polynomial<Order, ParamT>& polyn_);

#include "Polynomial.inl"
