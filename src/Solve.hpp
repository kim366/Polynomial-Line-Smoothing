#include "Polynomial.hpp"

#include <vector>

template<unsigned PolynOrder, typename ParamT>
std::vector<ParamT> solve(const Polynomial<PolynOrder, ParamT>& polyn_,
                          ParamT y_ = 0)
{
    return {y_};
}
