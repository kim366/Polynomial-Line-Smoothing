#define CATCH_CONFIG_MAIN
#include "ComputeDerivative.hpp"
#include "Polynomial.hpp"
#include "Solve.hpp"
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
    Polynomial<2> dfdx{compute_derivative(f)};

    CHECK(dfdx.getParams() == decltype(dfdx.getParams()){-15.f, 6.f, 7.f});
}

TEST_CASE("Higher order polynomial derivatives work.")
{
    Polynomial<3> f{2.f, 7.f, 1.f, 3.f};
    Polynomial<1> dfdx2{compute_derivative<2>(f)};

    CHECK(dfdx2.getParams() == decltype(dfdx2.getParams()){12.f, 14.f});
}

TEST_CASE("Solutions of 2nd order polynomials are computed correctly.")
{
    Polynomial<2> f{4.f, -8.f, 3.f};
    CHECK(solve(f) == decltype(solve(f)){.5f, 1.5f});
    CHECK(solve(f, 3.f) == decltype(solve(f)){0.f, 2.f});
}

TEST_CASE("Solutions of 5th order polynomials are computed correctly.")
{
    Polynomial<5> f{3.f, -4.f, -1.f, 2.f, -4.f, 0.f};
    const auto solutions{solve(f)};
    REQUIRE(solutions.size() == 3);
    CHECK(solutions[0] == -1.f);
    CHECK(solutions[1] == 0.f);
    CHECK(solutions[2] == Approx(1.6f));
}
