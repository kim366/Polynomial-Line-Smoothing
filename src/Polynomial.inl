#include <cmath>

template<unsigned Order, typename ParamT>
template<typename... ParamTs>
Polynomial<Order, ParamT>::Polynomial(ParamTs... params_) : _params{params_...}
{
    static_assert(std::is_floating_point_v<ParamT>,
                  "Polynomial Parameters must be floating point numbers");
}

template<unsigned Order, typename ParamT>
ParamT Polynomial<Order, ParamT>::operator()(ParamT x_) const
{
    ParamT sum{0};

    for (int power{Order}; power >= 0; --power)
        sum +=
            _params[Order - power] * static_cast<ParamT>(std::pow(x_, power));

    return sum;
}
