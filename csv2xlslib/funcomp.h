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
            return [pred=m_pred, callee](auto &&... args) {
                while (true)
                {
                    auto const result = callee(args...);
                    if (pred(result))
                        return result;
                }
            };
        }
    };
    template<typename Callee>
    struct Do
    {
        Callee callee;
        constexpr Do(Callee callee_)
                    :callee(callee_)
                    {}
        template<typename Pred>
        constexpr auto If(Pred&& pred)
        {
            return [callee_=callee, pred](auto && value){
                if (pred(value))
                {
                    if constexpr (std::is_invocable_v<Callee,decltype(value)>)
                    {
                        return callee_(value);
                    }
                    else
                    {
                        return callee_();
                    }
                }
                return value;
            };
        }
    };

    template <typename Callee, typename Caller> auto operator|(Callee callee, Caller caller)
    {
        if constexpr (std::is_base_of_v<funcomp::HigherOrderFunction, Caller>)
        {
            return [hof = caller(callee)](auto&&... arg) { return hof(arg...); };
        }
        else
        {
            return [callee_=std::move(callee), caller](auto&&... arg) { return caller(callee_(arg...)); };
        }
    }

    }

#endif //CSV2XLS_FUNCOMP_H
