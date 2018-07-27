#include <cmath>

template<unsigned Order, typename ParamT>
template<typename... ParamTs>
Polynomial<Order, ParamT>::Polynomial(ParamTs... params_) : _params{params_...}
{
    static_assert(std::is_floating_point_v<ParamT>,
                  "Polynomial Parameters must be floating point numbers");
}

template<unsigned Order, typename ParamT>
ParamT Polynomial<Order, ParamT>::operator()(ParamT value_)
{
    ParamT sum{0};

    for (int power{Order}; power >= 0; --power)
        sum += _params[Order - power]
               * static_cast<ParamT>(std::pow(value_, power));

    return sum;
}

template<unsigned Order, typename ParamT>
Polynomial<Order - 1, ParamT>
    compute_derivative(const Polynomial<Order, ParamT>& polyn_,
                       int derivative_order_)
{
    using DerivedPolynT = Polynomial<Order - 1, ParamT>;

    typename DerivedPolynT::ParamArrT derived_params;

    for (int param_idx = 0; param_idx < Order; ++param_idx)
    {
        derived_params[param_idx] =
            (Order - param_idx) * polyn_.getParam(param_idx);
    }

    return {derived_params};
}
