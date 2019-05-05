//
// Created by marcel on 5/5/19.
//

#include "catch.hpp"
#include <SkilledType.h>
namespace skilled_type_test{
    using skilled_type::SkilledType;
    using skilled_type::Equality;
    using skilled_type::Addable;

    TEST_CASE("lol")
    {
        using CompInt = SkilledType<int, struct CompIntTypeTag,  Equality>;

        CompInt ci1(1);
        CompInt ci2(1);
        CompInt ci3(2);
        REQUIRE( ci1 == ci2);
        REQUIRE( ci1 != ci3);

    }
    TEST_CASE("lola")
    {
        using CompInt = SkilledType<int, struct CompIntTypeTag, Equality, Addable>;

        CompInt ci1(1);
        CompInt ci2(1);
        CompInt ci3(2);
        REQUIRE( ci1 == ci2);
        REQUIRE( (ci1 + ci2) == ci3);

    }

}