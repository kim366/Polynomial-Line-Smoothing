#pragma once

#include "Polynomial.hpp"

#define COMPUTE_DERIVATIVE_ORDER(polyn, deriv_order)                           \
    comp_deriv_impl<decltype(polyn)::PolynOrder,                               \
                    decltype(polyn)::PolynParam,                               \
                    deriv_order>::compute_derivative(polyn)

#define COMPUTE_DERIVATIVE(polyn) COMPUTE_DERIVATIVE_ORDER(polyn, 1)

template<unsigned Order, typename ParamT, int DerivativeOrder>
struct comp_deriv_impl
{
    static Polynomial<Order - DerivativeOrder, ParamT>
        compute_derivative(const Polynomial<Order, ParamT>& polyn_)
    {
        using DerivedPolynT = Polynomial<Order - 1, ParamT>;

        typename DerivedPolynT::ParamArrT derived_params;

        for (unsigned param_idx{0}; param_idx < Order; ++param_idx)
            derived_params[param_idx] = static_cast<float>(Order - param_idx)
                                        * polyn_.getParam(param_idx);

        const DerivedPolynT derived_polyn{std::move(derived_params)};
        return comp_deriv_impl<Order, ParamT, DerivativeOrder - 1>::
            compute_derivative(derived_polyn);
    }
};

template<unsigned Order, typename ParamT>
struct comp_deriv_impl<Order, ParamT, 0>
{
    static Polynomial<Order, ParamT>
        compute_derivative(const Polynomial<Order, ParamT>& polyn_)
    {
        return polyn_;
    }
};

// #include "ComputeDerivative.inl"
