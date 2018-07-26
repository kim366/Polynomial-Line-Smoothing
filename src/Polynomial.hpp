#pragma once

template<typename ParamT, int Degree>
class Polynomial
{
public:
    Polynomial(std::initializer_list<ParamT> params_);

private:
    std::array<ParamT, Degree> _params;
};

#include "Polynomial.inl"
