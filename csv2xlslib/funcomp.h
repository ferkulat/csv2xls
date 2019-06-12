//
// Created by marcel on 6/13/19.
//

#ifndef CSV2XLS_FUNCOMP_H
#define CSV2XLS_FUNCOMP_H
#include <type_traits>

namespace funcomp{

    struct HigherOrderFunction{};
    template<typename Predicate>
    auto repeatWhile(Predicate predicate)
    {
        return [predicate](auto callee){
            bool success = true;
            while(success)
            {
                success = predicate(callee());
            }
        };
    }

    template <typename Pred> struct repeatUntil : HigherOrderFunction
    {
        Pred m_pred;
        repeatUntil(Pred pred)
                : m_pred(pred)
        {
        }
        template <typename Callee> auto operator()(Callee callee) const
        {
            while (true)
            {
                auto const result = callee();
                if (m_pred(result))
                    return result;
            }
        }
    };
    template<typename Callee, typename Pred>
    auto DoIf(Callee callee, Pred pred)
    {
        return [callee, pred](auto& value){
            if (pred(value))
            {
                if constexpr (std::is_invocable_v<Callee,declval(value)>)
                {
                    return calee(value);
                }
                else
                {
                    return callee();
                }
            }
            return value;
        };
    }

    template<typename Callee, typename Caller>
    auto operator|(Callee callee, Caller caller)
    {
        if constexpr (std::is_base_of_v<HigherOrderFunction, Caller>)
        {
            return [callee, caller](){
                return caller(callee);
            };
        }
        else
        {
            return [callee, caller](auto const&... arg) { return caller(callee(arg...)); };
        }
    }


}

#endif //CSV2XLS_FUNCOMP_H
