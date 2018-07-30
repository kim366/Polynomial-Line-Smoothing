#pragma once

#include "Polynomial.hpp"

template<int DerivativeOrder = 1,
         unsigned Order,
         typename ParamT,
         typename std::enable_if_t<DerivativeOrder != 0>* = {}>
Polynomial<Order - DerivativeOrder, ParamT>
    compute_derivative(const Polynomial<Order, ParamT>& polyn_)
{
    using DerivedPolynT = Polynomial<Order - 1, ParamT>;

    typename DerivedPolynT::ParamArrT derived_params;

    for (unsigned param_idx{0}; param_idx < Order; ++param_idx)
        derived_params[param_idx] =
            static_cast<float>(Order - param_idx) * polyn_.getParam(param_idx);

    const DerivedPolynT derived_polyn{std::move(derived_params)};
    return compute_derivative<DerivativeOrder - 1>(derived_polyn);
}

template<int DerivativeOrder = 1,
         unsigned Order,
         typename ParamT,
         typename std::enable_if_t<DerivativeOrder == 0>* = {}>
Polynomial<Order, ParamT>
    compute_derivative(const Polynomial<Order, ParamT>& polyn_)
{
    return polyn_;
}

// #include "ComputeDerivative.inl"
