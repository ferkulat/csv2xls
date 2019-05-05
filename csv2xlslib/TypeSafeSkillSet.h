//
// Created by marcel on 5/5/19.
//

#ifndef CSV2XLS_TYPESAFESKILLSET_H
#define CSV2XLS_TYPESAFESKILLSET_H

#include <istream>
#include "crtp.h"
namespace type_safe_skill_set
{

template <typename T, typename TypeTag, template <typename> typename... Skills>
class TypeSafeSkillSet : public Skills<TypeSafeSkillSet<T, TypeTag, Skills...>>...
{
    T value;

  public:
    using type         = T;
    TypeSafeSkillSet() = default;
    constexpr explicit TypeSafeSkillSet(T t_)
        : value(std::move(t_))
    {
    }
    constexpr T const& Get() const
    {
        return value;
    }
    constexpr T & Get()
    {
        return value;
    }
};

template <typename Derived>
struct Equality: public crtp<Derived, Equality>
{
    constexpr bool operator==(Derived const& other) const
    {
        return other.Get() == this->underlying().Get();
    }
    constexpr bool operator!=(Derived const& other) const
    {
        return other.Get() != this->underlying().Get();
    }
};

template <typename Derived>
struct Addable : public crtp<Derived, Addable>
{
    constexpr Derived operator+(Derived const& other) const
    {
        return Derived(other.Get() + this->underlying().Get());
    }
};

template <typename U>
struct ComparableWith
{
    template<typename T>
    struct templ: crtp<T, templ>
    {
    constexpr  bool isLess        (U const& other) const { return this->underlying().Get() < other.Get(); }
    constexpr  bool isEqual       (U const& other) const { return this->underlying().Get() == other.Get();}
    constexpr  bool isGreater     (U const& other) const { return this->underlying().Get() > other.Get(); }
    constexpr  bool isLessEqual   (U const& other) const { return (this->isLess(other))    || (this->isEqual(other));      }
    constexpr  bool isGreaterEqual(U const& other) const { return (this->isGreater(other)) || (this->isEqual(other));      }
    };
};

template <typename T>
struct PreIncrementable : crtp<T, PreIncrementable>
{
    T& operator++() { ++(this->underlying().Get()); return this->underlying(); }
};

}
#endif //CSV2XLS_TYPESAFESKILLSET_H
