//
// Created by marcel on 5/5/19.
//

#include "catch.hpp"
#include <TypeSafeSkillSet.h>
namespace type_safe_skill_set_test{
    using type_safe_skill_set::TypeSafeSkillSet;
    using type_safe_skill_set::Equality;
    using type_safe_skill_set::Addable;

    TEST_CASE("lol")
    {
        using CompInt = TypeSafeSkillSet<int, struct CompIntTypeTag,  Equality>;

        CompInt ci1(1);
        CompInt ci2(1);
        CompInt ci3(2);
        REQUIRE( ci1 == ci2);
        REQUIRE( ci1 != ci3);

    }
    TEST_CASE("lola")
    {
    using CompInt = TypeSafeSkillSet<int, struct CompIntTypeTag, Equality, Addable>;

    CompInt ci1(1);
    CompInt ci2(1);
    CompInt ci3(2);
    REQUIRE( ci1 == ci2);
    REQUIRE( (ci1 + ci2) == ci3);

    }

}