#define CATCH_CONFIG_MAIN
#include "ComputeDerivative.hpp"
#include "Polynomial.hpp"
#include "catch.hpp"

TEST_CASE("Polynomials are computed correctly.")
{
    Polynomial<2> f{1.f, 0.f, 1.f};

    CHECK(f(0) == 1.f);
    CHECK(f(2) == 5.f);
    CHECK(f(-4) == 17.f);
}

TEST_CASE("1st order polynomial derivatives work.")
{
    Polynomial<3> f{-5.f, 3.f, 7.f, -4.f};
    Polynomial<2> dfdx{comp_deriv_impl<2, float, 1>::compute_derivative(f)};

    CHECK(dfdx.getParams() == decltype(dfdx.getParams()){-15.f, 6.f, 7.f});
}

TEST_CASE("Higher order polynomial derivatives work.")
{
    Polynomial<3> f{2.f, 7.f, 1.f, 3.f};
    Polynomial<1> dfdx2{comp_deriv_impl<3, float, 2>::compute_derivative(f)};

    CHECK(dfdx2.getParams() == decltype(dfdx2.getParams()){2.f, 14.f});
}
