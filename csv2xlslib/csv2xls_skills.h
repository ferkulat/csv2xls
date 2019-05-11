//
// Created by marcel on 5/11/19.
//

#ifndef CSV2XLS_CSV2XLS_SKILLS_H
#define CSV2XLS_CSV2XLS_SKILLS_H
#include <Crtp.h>
namespace csv2xls
{
template <typename U> struct ComparableWith
{
    template <typename T> struct templ : Crtp<T, templ>
    {
        constexpr bool isLess(U const& other) const
        {
            return this->underlying().Get() < other.Get();
        }
        constexpr bool isEqual(U const& other) const
        {
            return this->underlying().Get() == other.Get();
        }
        constexpr bool isGreater(U const& other) const
        {
            return this->underlying().Get() > other.Get();
        }
        constexpr bool isLessEqual(U const& other) const
        {
            return (this->isLess(other)) || (this->isEqual(other));
        }
        constexpr bool isGreaterEqual(U const& other) const
        {
            return (this->isGreater(other)) || (this->isEqual(other));
        }
    };
};
}
#endif // CSV2XLS_CSV2XLS_SKILLS_H
