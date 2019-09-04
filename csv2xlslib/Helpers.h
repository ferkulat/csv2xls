//
// Created by marcel on 6/16/19.
//

#ifndef CSV2XLS_HELPERS_H
#define CSV2XLS_HELPERS_H
template<typename... Preds>
constexpr auto EitherOf(Preds... preds){
    return [preds...](auto const& value) {
        return (... || preds(value));
    };
}


template<typename... T>
constexpr auto isEitherOf(T... t){
    return [t...](auto const& value) {
        return (... || (t == value));
    };
}

template<typename... Preds>
constexpr auto AllOf(Preds... preds){
    return [preds...](auto const& value) {
        return (... && preds(value));
    };
}

template<typename T>
class EndlessRange
{
    mutable T value;
public:
    constexpr EndlessRange(EndlessRange const&)=delete;
    constexpr EndlessRange(EndlessRange &&)=default;
    constexpr EndlessRange& operator=(EndlessRange&&)=default;
    constexpr EndlessRange(T start):value(start){}
    constexpr T operator()()const{
        return value++;
    }
};
template<typename T>
struct isType
{
    constexpr auto operator()(T const&)const{
        return true;
    }
};


#endif //CSV2XLS_HELPERS_H
