//
// Created by marcel on 5/31/19.
//

#ifndef CSV2XLS_MATCHVARIANTTYPE_H
#define CSV2XLS_MATCHVARIANTTYPE_H
// https://www.bfilipek.com/2019/02/2lines3featuresoverload.html
#include <variant>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename V, typename... Os>
constexpr auto MatchType(V&& variant, Os... overloads)
{
    return std::visit(overloaded{overloads...}, std::forward<V>(variant));
}

template <typename... ARGS>
auto matchesOneOf(ARGS... args)
{
    return [args...](auto input){
        return  MatchType(input, args..., [](auto ){return false;});
    };
}

#endif //CSV2XLS_MATCHVARIANTTYPE_H
