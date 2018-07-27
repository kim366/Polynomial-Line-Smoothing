template<unsigned Order, typename ParamT>
template<typename... ParamTs>
Polynomial<Order, ParamT>::Polynomial(ParamTs... params_) : _params{params_...}
{
    static_assert(std::is_floating_point_v<ParamT>,
                  "Polynomial Parameters must be floating point numbers");
}

template<unsigned Order, typename ParamT>
ParamT Polynomial<Order, ParamT>::operator()(ParamT x)
{
    return x;
}
