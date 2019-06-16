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
        std::stringstream file;
        Tracer tracer;
    };

    template<typename Callee, typename Predicate>
    struct helper
    {
        Callee callee;
        Predicate pred;
        helper(Callee callee_, Predicate pred_)
        :callee(callee_), pred(pred_)
        {
        }
        template<typename... ARGs>
        auto operator()(ARGs&&... args)const
        {
            while (true)
            {
                auto const result = callee(std::forward<ARGs>(args)...);
                if (pred(result))
                    return result;
            }

        }
    };

    template <typename Callee, typename Caller> auto operator>>=(Callee callee, Caller caller)
    {
        if constexpr (std::is_base_of_v<funcomp::HigherOrderFunction, Caller>)
        {
            return [hof = caller(callee)](auto&&... arg) { return hof(arg...); };
        }
        else
        {
            return [callee, caller](auto&&... arg) { return caller(callee(arg...)); };
        }
    }

    template <typename Pred> struct RepeatUntil : public funcomp::HigherOrderFunction
    {
        Pred m_pred;
        RepeatUntil(Pred pred)
                : m_pred(pred)
        {
        }
        template <typename Callee> auto operator()(Callee callee) const
        {
            return helper<Callee, Pred>(callee,m_pred);
        }
    };

    auto innerFunc1 = [](std::stringstream & stream)->char{
        if (stream.good())
        {
            char val = static_cast<char>(stream.get());
            auto count = stream.gcount();
            if( count == 1 )
                return val;
        }
        return '@';
    };

    auto innerFunc2(std::vector<char>& out)
    {
        return [&](char i)->char{
            if (i != '@')
                out.push_back(i);
            return i;

        };
    }

    auto isEnd = [](char i){
        return i == '@';
    };

    TEST_CASE("lol")
    {
        std::stringstream  file;
        file << "12345";
        std::vector<char> out;
        auto myfun =  RepeatUntil(isEnd)(innerFunc1 >>= innerFunc2(out));

        myfun(file);
        REQUIRE(out == std::vector<char>{'1','2','3','4','5'});
    }

}
}
