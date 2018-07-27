#define CATCH_CONFIG_MAIN
#include "Polynomial.hpp"
#include "catch.hpp"

TEST_CASE("Polynomials are computed correctly.")
{
    Polynomial<2> f{1.f, 0.f, 1.f};

    CHECK(f(0) == 1.f);
    CHECK(f(2) == 5.f);
    CHECK(f(-4) == 17.f);
}
