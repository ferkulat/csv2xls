//
// Created by marcel on 6/13/19.
//
#include "catch.hpp"
#include <funcomp.h>
#include <iostream>
#include <sstream>
namespace csv2xls
{
namespace funcompTest
{
    using funcomp::operator|;
    using funcomp::repeatUntil;

    struct Tracer{
        Tracer(){std::cout << "Tracer()\n";}
        Tracer(Tracer const& ){std::cout << "Tracer(Tracer const&)\n";}
        Tracer(Tracer&& ){std::cout << "Tracer(Tracer&&)\n";}
        Tracer operator=(Tracer const&){std::cout << "operator=(Tracer const&)\n";return *this;}
        Tracer operator=(Tracer const&&){std::cout << "operator=(Tracer const&&)\n";return *this;}
        ~Tracer(){std::cout << "~Tracer()\n";}
    };

    struct Data
    {
        int file;
        Tracer tracer;
    };


    auto innerFunc1 = [](Data data)->std::optional<Data>{
        if (data.file == 3)
        {
            return data;
        }
        return std::nullopt;
    };

    auto innerFunc2(int i)
    {
        return [&](std::optional<Data> out)->int{
            if (out->file == 2 && i != '@')
                return i;
            return i+1;

        };
    }

    auto isEnd = [](int i){
        return i == '@';
    };

    TEST_CASE("lol")
    {
//        std::stringstream  file;
//        file << "12345";
//        std::vector<char> out;
//        auto myfun =  innerFunc1|innerFunc2(2)|repeatUntil(isEnd);
//
//        myfun(Data{});
//        REQUIRE(out == std::vector<char>{'1','2','3','4','5'});
    }

}
}
