#pragma once

#include <array>

template<unsigned Order, typename ParamT = float>
class Polynomial
{
public:
    using ParamArrT = std::array<ParamT, Order + 1>;

    template<typename... ParamTs>
    Polynomial(ParamTs... params_);

    template<unsigned OtherOrder, typename OtherParamT>
    Polynomial(const Polynomial<OtherOrder, OtherParamT>& other_)
    {
        for (unsigned index{0}; index < other_.getParams().size(); ++index)
            _params[index] = other_.getParam(index);
    }

    ParamT operator()(ParamT x_) const;

    const auto& getParams() const { return _params; }

    void setParams(ParamArrT&& params_) { _params = std::move(params_); }

private:
    ParamArrT _params;
};

#include "Polynomial.inl"
