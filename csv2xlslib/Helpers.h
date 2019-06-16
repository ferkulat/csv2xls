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
    EndlessRange(T start):value(start){}
    T operator()()const{
        return value++;
    }
};


#endif //CSV2XLS_HELPERS_H
