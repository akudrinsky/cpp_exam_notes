 // in process

template<class value_type>
class optional {
private:
    static_assert (!is_reference<value_type>,
                   "instantiation of optional with a reference type is ill-formed");        // it is in std (and a few more others). why? (akudrinsky)
    
    bool is_correct = false;
    value_type value;
    
public:
    constexpr optional () noexcept {}
    ~optional () {
        is_correct = false;
    }
    
    constexpr optional (const optional& other) {
        is_correct  = other.is_correct;
        value       = other.value;                      // maybe make it safer?
    }
    
    
};
