//
// Created by marcel on 5/5/19.
//

#ifndef CSV2XLS_CRTP_H
#define CSV2XLS_CRTP_H
template <typename T, template<typename> class crtpType>
struct crtp
{
    T& underlying() { return static_cast<T&>(*this); }
    T const& underlying() const { return static_cast<T const&>(*this); }
};

#endif //CSV2XLS_CRTP_H
