#pragma once

#include <array>

template<unsigned Order, typename ParamT = float>
class Polynomial
{
public:
    using ParamArrT = std::array<ParamT, Order + 1>;
    static const auto PolynOrder{Order};
    using PolynParam = ParamT;

    template<typename... ParamTs>
    Polynomial(ParamTs... params_);

    template<unsigned OtherOrder, typename OtherParamT>
    Polynomial(const Polynomial<OtherOrder, OtherParamT>& other_)
    {
        for (unsigned index{0}; index < other_.getParams().size(); ++index)
            _params[index] = other_.getParam(index);
    }

    template<typename ArrElemT, unsigned ArrSize>
    Polynomial(std::array<ArrElemT, ArrSize>&& arr_) : _params{std::move(arr_)}
    {
    }

    template<typename ArrElemT, unsigned ArrSize>
    Polynomial(const std::array<ArrElemT, ArrSize>& arr_) : _params{arr_}
    {
    }

    ParamT operator()(ParamT x_);

    const auto& getParams() const { return _params; }
    ParamT getParam(unsigned index_) const { return _params[index_]; }

private:
    ParamArrT _params;
};

#include "Polynomial.inl"
