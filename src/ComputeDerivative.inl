template<unsigned Order, typename ParamT, int DerivativeOrder>
Polynomial<Order - DerivativeOrder, ParamT>
    comp_deriv_impl<Order, ParamT, DerivativeOrder>::comp_deriv(
        const Polynomial<Order, ParamT>& polyn_)
{
    using DerivedPolynT = Polynomial<Order - 1, ParamT>;

    typename DerivedPolynT::ParamArrT derived_params;

    for (unsigned param_idx{0}; param_idx < Order; ++param_idx)
        derived_params[param_idx] =
            static_cast<float>(Order - param_idx) * polyn_.getParam(param_idx);

    const DerivedPolynT derived_polyn{std::move(derived_params)};
    return comp_deriv_impl<Order - 1, ParamT, DerivativeOrder - 1>::comp_deriv(
        derived_polyn);
}