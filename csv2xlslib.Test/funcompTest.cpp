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
        Tracer& operator=(Tracer const& ){std::cout << "operator=(Tracer const&)\n";return *this;}
        Tracer& operator=(Tracer const&&){std::cout << "operator=(Tracer const&&)\n";return *this;}
        ~Tracer(){std::cout << "~Tracer()\n";}
    };
    struct NonCopyable{
        int m_i;
        explicit  NonCopyable(int i):m_i(i){}
        NonCopyable(NonCopyable const&)= delete;
        NonCopyable(NonCopyable &&)= default;
        NonCopyable& operator=(NonCopyable const&)=delete;
        NonCopyable& operator=(NonCopyable &&)=default;

        bool operator==(NonCopyable const& other)const{
            return m_i == other.m_i;
        }
    };
    struct Copyable{
        int m_i;
        explicit  Copyable(int i)
            :m_i(i)
        {std::cout << "Copyable(int i)\n";}
        bool operator==(Copyable const& other)const{
            return m_i == other.m_i;
        }

        Copyable(Copyable const& other):m_i(other.m_i){
            std::cout << "Copyable(Copyable const&)\n";
        }

        Copyable(Copyable && other):m_i(other.m_i){
            std::cout << "Copyable(Copyable &&)\n";
        }

        Copyable& operator=(Copyable const& other){
            std::cout << "operator=(Copyable const&)\n";
            m_i= other.m_i;
            return *this;
        }

        Copyable& operator=(Copyable && other){
            std::cout << "operator=(Copyable &&)\n";
            m_i= other.m_i;
            return *this;
        }

        ~Copyable(){
            std::cout << "~Copyable()\n";
        }
    };

    enum class Error {IsOdd};
    TEST_CASE("callee returns Result<T, E> but caller expects T")
    {
        using ReturnType = ResultType::Result<int, Error>;

        auto evenOnly    = [](int i){return (i%2==0)? ReturnType(i) : ReturnType(Error::IsOdd);};
        auto multiplyBy2 = [](int i){return i*2;};

        auto composed = evenOnly|multiplyBy2;

        REQUIRE(ResultType::Result<int, Error>(4) == composed(2));
        REQUIRE(ResultType::Result<int, Error>(Error::IsOdd) == composed(3));
    }

    TEST_CASE("track copying when callee returns Result<Copyable, E> but caller expects T")
    {
        using ReturnType = ResultType::Result<Copyable, Error>;

        auto evenOnly    = [](Copyable i){return (i.m_i %2==0)? ReturnType(std::move(i)) : ReturnType(Error::IsOdd);};
        auto multiplyBy2 = [](Copyable i){return Copyable(i.m_i*2);};

        auto multiplyEvensBy8 = evenOnly|(multiplyBy2|multiplyBy2|multiplyBy2);

        REQUIRE(ResultType::Result<Copyable, Error>(Copyable(16))  == multiplyEvensBy8(Copyable(2)));
        REQUIRE(ResultType::Result<Copyable, Error>(Error::IsOdd)  == multiplyEvensBy8(Copyable(3)));
    }

    TEST_CASE("callee returns Result<NonCopyable, E> but caller expects NonCopyable")
    {
        using ReturnType = ResultType::Result<NonCopyable, Error>;

        auto evenOnly    = [](NonCopyable i){return (i.m_i%2==0)? ReturnType(std::move(i)) : ReturnType(Error::IsOdd);};
        auto multiplyBy2 = [](NonCopyable i){return NonCopyable(i.m_i*2);};

        auto multiplyEvensBy2 = evenOnly|multiplyBy2;
        auto const expected_success = ResultType::Result<NonCopyable, Error>(NonCopyable(4));
        auto const actual_success = multiplyEvensBy2(NonCopyable(2));
        REQUIRE( expected_success == actual_success);
    }

}
}
