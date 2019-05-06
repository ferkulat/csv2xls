//
// Created by marcel on 5/5/19.
//

#ifndef CSV2XLS_SKILLEDTYPE_H
#define CSV2XLS_SKILLEDTYPE_H

#include <istream>
#include "crtp.h"
namespace skilled_type
{
template <typename T, typename TypeTag, template <typename> typename... Skills> class SkilledType;

template <typename T, typename TypeTag, template <typename> typename... Skills>
std::istream& operator>>(std::istream& is, SkilledType<T, TypeTag, Skills...>& target);

template <typename T, typename TypeTag, template <typename> typename... Skills>
std::ostream& operator<<(std::ostream& os, SkilledType<T, TypeTag, Skills...> const& target);

template <typename T, typename TypeTag, template <typename> typename... Skills>
class SkilledType : public Skills<SkilledType<T, TypeTag, Skills...>>...
{
    T value;

  public:
    using type         = T;
    SkilledType() = default;
    constexpr explicit SkilledType(T t_)
        : value(std::move(t_))
    {
    }
    constexpr T const& Get() const
    {
        return value;
    }
    constexpr T& Get()
    {
        return value;
    }

  private:
    friend std::istream&
    operator>><T, TypeTag, Skills...>(std::istream& is, SkilledType<T, TypeTag, Skills...>& target);

    friend std::ostream&
    operator<<<T, TypeTag, Skills...>(std::ostream& os, SkilledType<T, TypeTag, Skills...> const& target);
};

template <typename T, typename TypeTag, template <typename> typename... Skills>
std::istream& operator>>(std::istream& is, SkilledType<T, TypeTag, Skills...>& target)
{
    is >> target.value;
    return is;
}

template <typename T, typename TypeTag, template <typename> typename... Skills>
std::ostream& operator<<(std::ostream& os, SkilledType<T, TypeTag, Skills...> const& target)
{
    os << target.value;
    return os;
}

template <typename Derived> struct Equality : public crtp<Derived, Equality>
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

template <typename Derived> struct RelativeComparable : public crtp<Derived, RelativeComparable>
{
    constexpr bool operator<(Derived const& other) const
    {
        return this->underlying().Get() < other.Get();
    }
    constexpr bool operator>(Derived const& other) const
    {
        return this->underlying().Get() > other.Get();
    }
};

template <typename Derived> struct Addable : public crtp<Derived, Addable>
{
    constexpr Derived operator+(Derived const& other) const
    {
        return Derived(other.Get() + this->underlying().Get());
    }
};

template <typename U> struct ComparableWith
{
    template <typename T> struct templ : crtp<T, templ>
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

template <typename T> struct Incrementable : crtp<T, Incrementable>
{
    T& operator++()
    {
        ++(this->underlying().Get());
        return this->underlying();
    }
    T operator++(int)
    {
        T tmp(this->underlying().Get());
        operator++();
        return tmp;
    }
};

} // namespace skilled_type
#endif // CSV2XLS_SKILLEDTYPE_H
