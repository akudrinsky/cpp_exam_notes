template<bool B, typename T, typename F>
struct conditional {
    using type = F;
};

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

struct true_type {
    static const bool value = true;
};

struct false_type {
    static const bool value = false;
};

template<unsigned long long N, unsigned long long i>
struct prime_check {
    static const bool value = (N % i) && conditional<i * i <= N, prime_check<N, i+1>, true_type>::type::value;
};

template<unsigned long long N>
struct is_prime {
    static const bool value = prime_check<N, 2>::value;
};

template<>
struct is_prime<1> {
    static const bool value = false;
};

template<>
struct is_prime<0> {
    static const bool value = false;
};