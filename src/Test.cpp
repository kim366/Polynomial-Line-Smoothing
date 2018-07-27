#define CATCH_CONFIG_MAIN
#include "Polynomial.hpp"
#include "catch.hpp"

TEST_CASE("Polynomials are computed correctly.")
{
    Polynomial<2> f{1.f, 0.f, 1.f};
}
