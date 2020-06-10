/*
 My implementation of std::optional. The project is on its embryonic stage, so no tests are available yet.
 */
#include <optional>
#include <algorithm>

template<class value_type>
class optional {
private:
    static_assert (!is_reference<value_type>,
                   "instantiation of optional with a reference type is ill-formed");        // it is in std (and a few more others). why? (akudrinsky)
    
    bool        is_correct = false;
    value_type  value;
    
public:
    /* Constructors, destructor. */
    
    constexpr optional () noexcept {}
    
    constexpr optional (std::nullopt) noexcept {
        is_correct = false;
    }
    
    constexpr optional (const optional& other) {
        if (other.is_correct)
            value = other.value;                      // maybe make it safer (in case no copy for value_type)?
        
        is_correct = other.is_correct;
    }
    
    template<class value_type>
    constexpr explicit optional (value_type& data) {    // NO (!!!) such in std. why?
        is_correct  = true;
        value       = data;
    }
    
    // to do: convert-copy constructor and maybe more
    
    ~optional () {
        is_correct = false;
    }
    
    /* Assignment. */
    
    constexpr operator= (std::nullopt) noexcept {
        is_correct = false;
    }
    
    constexpr optional& operator= (const operator& other) {
        
    }
    
    // to do: convert - assignment and maybe more
    
    /* Getters. Do not check 'is_correct', as in std */
    
    constexpr const value_type* operator-> () const {
        return &value;
    }
    
    constexpr       value_type* operator-> () {
        return &value;
    }
    
    constexpr const value_type& operator* () const {
        return value;
    }
    
    constexpr       value_type& operator* () {
        return value;
    }
    
    /* 'is_correct' checks */
    constexpr explicit operator bool() const noexcept {
        return is_correct;
    }
    
    constexpr bool has_value () const noexcept {
        return is_correct;
    }
    
    /* Getters. Do check 'is_correct', throw std::bad_optional_access exception in a bad scenario */
    
    constexpr T& value () & {                   // for strange "&" visit https://habr.com/ru/post/216783/. It will still work without it.
        if (is_correct) {
            return value;
        }
        else {
            throw std::bad_optional_access;
        }
    }
    
    constexpr const T& value() const& {
        if (is_correct) {
            return value;
        }
        else {
            throw std::bad_optional_access;
        }
    }
    
    // to do: value_or
    
    /* Modifiers. */
    
    void swap (optional& other) {       //noexcept (is_nothrow_move_constructible_v<value_type> and is_nothrow_swappable_v<value_type>) (what is it????)
        if (is_correct and other.is_correct) {
            std::swap (value, other.value);
        }
        else if (is_correct) {          // std::move would be better (how it works?)
            value = other.value;
        }
        else if (other.is_correct) {
            other.value = value;
        }
    }
    
    void reset noexcept () {
        if (is_correct) {
            value.~value_type ();
            is_correct = false;
        }
    }
    
    // to do: emplace
};

