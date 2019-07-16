#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <foo/foo.h>

TEST_CASE( "run" ) {
  REQUIRE( 2 == 2 );
}