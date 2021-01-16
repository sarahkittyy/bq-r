#include "catch2/catch.hpp"

#include <json.hpp>
#include "level.hpp"

TEST_CASE("levels work as expected", "[level]") {
	using namespace Catch::Generators;
	using nlohmann::json;

	SECTION("deserialization and serialization work just fine") {
		level lvl_a(40, 40);

		int x		 = GENERATE(take(3, random(0, 39)));
		int y		 = GENERATE(take(3, random(0, 39)));
		tile::type t = GENERATE(tile::Block, tile::Spike, tile::Start, tile::End);

		lvl_a.set_tile(x, y, t);

		REQUIRE(lvl_a.get_tile(x, y).get_type() == t);

		level lvl_b(lvl_a.serialize());

		REQUIRE(lvl_b.get_tile(x, y).get_type() == t);
	}
}
