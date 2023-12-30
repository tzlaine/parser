// Copyright (c) 2023 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Warning: This header is auto-generated (see misc/generate_aggr_to_tuple.py).
// The lack of include guards is intentional.

namespace boost::parser::detail {


template<> struct aggregate_to_tuple_impl<1> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01
] = x;
return parser::tuple<
    decltype(_01)
>(
    std::move(_01)
);
}
};


template<> struct aggregate_to_tuple_impl<2> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02
] = x;
return parser::tuple<
    decltype(_01), decltype(_02)
>(
    std::move(_01), std::move(_02)
);
}
};


template<> struct aggregate_to_tuple_impl<3> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03)
>(
    std::move(_01), std::move(_02), std::move(_03)
);
}
};


template<> struct aggregate_to_tuple_impl<4> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04)
);
}
};


template<> struct aggregate_to_tuple_impl<5> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05)
);
}
};


template<> struct aggregate_to_tuple_impl<6> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06)
);
}
};


template<> struct aggregate_to_tuple_impl<7> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07)
);
}
};


template<> struct aggregate_to_tuple_impl<8> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08)
);
}
};


template<> struct aggregate_to_tuple_impl<9> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09)
);
}
};


template<> struct aggregate_to_tuple_impl<10> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a)
);
}
};


template<> struct aggregate_to_tuple_impl<11> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b)
);
}
};


template<> struct aggregate_to_tuple_impl<12> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c)
);
}
};


template<> struct aggregate_to_tuple_impl<13> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d)
);
}
};


template<> struct aggregate_to_tuple_impl<14> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e)
);
}
};


template<> struct aggregate_to_tuple_impl<15> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f)
);
}
};


template<> struct aggregate_to_tuple_impl<16> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10)
);
}
};


template<> struct aggregate_to_tuple_impl<17> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11)
);
}
};


template<> struct aggregate_to_tuple_impl<18> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12)
);
}
};


template<> struct aggregate_to_tuple_impl<19> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13)
);
}
};


template<> struct aggregate_to_tuple_impl<20> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14)
);
}
};


template<> struct aggregate_to_tuple_impl<21> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15)
);
}
};


template<> struct aggregate_to_tuple_impl<22> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16)
);
}
};


template<> struct aggregate_to_tuple_impl<23> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17)
);
}
};


template<> struct aggregate_to_tuple_impl<24> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18)
);
}
};


template<> struct aggregate_to_tuple_impl<25> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19)
);
}
};


template<> struct aggregate_to_tuple_impl<26> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a)
);
}
};


template<> struct aggregate_to_tuple_impl<27> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b)
);
}
};


template<> struct aggregate_to_tuple_impl<28> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c)
);
}
};


template<> struct aggregate_to_tuple_impl<29> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d)
);
}
};


template<> struct aggregate_to_tuple_impl<30> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e)
);
}
};


template<> struct aggregate_to_tuple_impl<31> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f)
);
}
};


template<> struct aggregate_to_tuple_impl<32> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20)
);
}
};


template<> struct aggregate_to_tuple_impl<33> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21)
);
}
};


template<> struct aggregate_to_tuple_impl<34> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22)
);
}
};


template<> struct aggregate_to_tuple_impl<35> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23)
);
}
};


template<> struct aggregate_to_tuple_impl<36> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24)
);
}
};


template<> struct aggregate_to_tuple_impl<37> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25)
);
}
};


template<> struct aggregate_to_tuple_impl<38> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26)
);
}
};


template<> struct aggregate_to_tuple_impl<39> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27)
);
}
};


template<> struct aggregate_to_tuple_impl<40> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28)
);
}
};


template<> struct aggregate_to_tuple_impl<41> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29)
);
}
};


template<> struct aggregate_to_tuple_impl<42> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a)
);
}
};


template<> struct aggregate_to_tuple_impl<43> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b)
);
}
};


template<> struct aggregate_to_tuple_impl<44> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c)
);
}
};


template<> struct aggregate_to_tuple_impl<45> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d)
);
}
};


template<> struct aggregate_to_tuple_impl<46> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e)
);
}
};


template<> struct aggregate_to_tuple_impl<47> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f)
);
}
};


template<> struct aggregate_to_tuple_impl<48> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30)
);
}
};


template<> struct aggregate_to_tuple_impl<49> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31)
);
}
};


template<> struct aggregate_to_tuple_impl<50> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32)
);
}
};


template<> struct aggregate_to_tuple_impl<51> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33)
);
}
};


template<> struct aggregate_to_tuple_impl<52> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34)
);
}
};


template<> struct aggregate_to_tuple_impl<53> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35)
);
}
};


template<> struct aggregate_to_tuple_impl<54> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36)
);
}
};


template<> struct aggregate_to_tuple_impl<55> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37)
);
}
};


template<> struct aggregate_to_tuple_impl<56> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38)
);
}
};


template<> struct aggregate_to_tuple_impl<57> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39)
);
}
};


template<> struct aggregate_to_tuple_impl<58> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a)
);
}
};


template<> struct aggregate_to_tuple_impl<59> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b)
);
}
};


template<> struct aggregate_to_tuple_impl<60> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c)
);
}
};


template<> struct aggregate_to_tuple_impl<61> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d)
);
}
};


template<> struct aggregate_to_tuple_impl<62> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e)
);
}
};


template<> struct aggregate_to_tuple_impl<63> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f)
);
}
};


template<> struct aggregate_to_tuple_impl<64> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40)
);
}
};


template<> struct aggregate_to_tuple_impl<65> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41)
);
}
};


template<> struct aggregate_to_tuple_impl<66> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42)
);
}
};


template<> struct aggregate_to_tuple_impl<67> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43)
);
}
};


template<> struct aggregate_to_tuple_impl<68> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44)
);
}
};


template<> struct aggregate_to_tuple_impl<69> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45)
);
}
};


template<> struct aggregate_to_tuple_impl<70> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46)
);
}
};


template<> struct aggregate_to_tuple_impl<71> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47)
);
}
};


template<> struct aggregate_to_tuple_impl<72> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48)
);
}
};


template<> struct aggregate_to_tuple_impl<73> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49)
);
}
};


template<> struct aggregate_to_tuple_impl<74> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a)
);
}
};


template<> struct aggregate_to_tuple_impl<75> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b)
);
}
};


template<> struct aggregate_to_tuple_impl<76> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c)
);
}
};


template<> struct aggregate_to_tuple_impl<77> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d)
);
}
};


template<> struct aggregate_to_tuple_impl<78> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e)
);
}
};


template<> struct aggregate_to_tuple_impl<79> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f)
);
}
};


template<> struct aggregate_to_tuple_impl<80> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50)
);
}
};


template<> struct aggregate_to_tuple_impl<81> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51)
);
}
};


template<> struct aggregate_to_tuple_impl<82> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52)
);
}
};


template<> struct aggregate_to_tuple_impl<83> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53)
);
}
};


template<> struct aggregate_to_tuple_impl<84> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54)
);
}
};


template<> struct aggregate_to_tuple_impl<85> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55)
);
}
};


template<> struct aggregate_to_tuple_impl<86> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56)
);
}
};


template<> struct aggregate_to_tuple_impl<87> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57)
);
}
};


template<> struct aggregate_to_tuple_impl<88> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58)
);
}
};


template<> struct aggregate_to_tuple_impl<89> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59)
);
}
};


template<> struct aggregate_to_tuple_impl<90> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a)
);
}
};


template<> struct aggregate_to_tuple_impl<91> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b)
);
}
};


template<> struct aggregate_to_tuple_impl<92> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c)
);
}
};


template<> struct aggregate_to_tuple_impl<93> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d)
);
}
};


template<> struct aggregate_to_tuple_impl<94> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e)
);
}
};


template<> struct aggregate_to_tuple_impl<95> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e, _5f
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e), decltype(_5f)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e), std::move(_5f)
);
}
};


template<> struct aggregate_to_tuple_impl<96> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e, _5f, _60
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e), decltype(_5f),
    decltype(_60)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e), std::move(_5f),
    std::move(_60)
);
}
};


template<> struct aggregate_to_tuple_impl<97> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e, _5f, _60, _61
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e), decltype(_5f),
    decltype(_60), decltype(_61)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e), std::move(_5f),
    std::move(_60), std::move(_61)
);
}
};


template<> struct aggregate_to_tuple_impl<98> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e, _5f, _60, _61, _62
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e), decltype(_5f),
    decltype(_60), decltype(_61), decltype(_62)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e), std::move(_5f),
    std::move(_60), std::move(_61), std::move(_62)
);
}
};


template<> struct aggregate_to_tuple_impl<99> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e, _5f, _60, _61, _62, _63
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e), decltype(_5f),
    decltype(_60), decltype(_61), decltype(_62), decltype(_63)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e), std::move(_5f),
    std::move(_60), std::move(_61), std::move(_62), std::move(_63)
);
}
};


template<> struct aggregate_to_tuple_impl<100> {
template<typename T> static constexpr auto call(T x) {
auto & [
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _0a, _0b, _0c, _0d, _0e, _0f,
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _1a, _1b, _1c, _1d, _1e,
    _1f, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _2a, _2b, _2c, _2d,
    _2e, _2f, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _3a, _3b, _3c,
    _3d, _3e, _3f, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _4a, _4b,
    _4c, _4d, _4e, _4f, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _5a,
    _5b, _5c, _5d, _5e, _5f, _60, _61, _62, _63, _64
] = x;
return parser::tuple<
    decltype(_01), decltype(_02), decltype(_03), decltype(_04), decltype(_05),
    decltype(_06), decltype(_07), decltype(_08), decltype(_09), decltype(_0a),
    decltype(_0b), decltype(_0c), decltype(_0d), decltype(_0e), decltype(_0f),
    decltype(_10), decltype(_11), decltype(_12), decltype(_13), decltype(_14),
    decltype(_15), decltype(_16), decltype(_17), decltype(_18), decltype(_19),
    decltype(_1a), decltype(_1b), decltype(_1c), decltype(_1d), decltype(_1e),
    decltype(_1f), decltype(_20), decltype(_21), decltype(_22), decltype(_23),
    decltype(_24), decltype(_25), decltype(_26), decltype(_27), decltype(_28),
    decltype(_29), decltype(_2a), decltype(_2b), decltype(_2c), decltype(_2d),
    decltype(_2e), decltype(_2f), decltype(_30), decltype(_31), decltype(_32),
    decltype(_33), decltype(_34), decltype(_35), decltype(_36), decltype(_37),
    decltype(_38), decltype(_39), decltype(_3a), decltype(_3b), decltype(_3c),
    decltype(_3d), decltype(_3e), decltype(_3f), decltype(_40), decltype(_41),
    decltype(_42), decltype(_43), decltype(_44), decltype(_45), decltype(_46),
    decltype(_47), decltype(_48), decltype(_49), decltype(_4a), decltype(_4b),
    decltype(_4c), decltype(_4d), decltype(_4e), decltype(_4f), decltype(_50),
    decltype(_51), decltype(_52), decltype(_53), decltype(_54), decltype(_55),
    decltype(_56), decltype(_57), decltype(_58), decltype(_59), decltype(_5a),
    decltype(_5b), decltype(_5c), decltype(_5d), decltype(_5e), decltype(_5f),
    decltype(_60), decltype(_61), decltype(_62), decltype(_63), decltype(_64)
>(
    std::move(_01), std::move(_02), std::move(_03), std::move(_04), std::move(_05),
    std::move(_06), std::move(_07), std::move(_08), std::move(_09), std::move(_0a),
    std::move(_0b), std::move(_0c), std::move(_0d), std::move(_0e), std::move(_0f),
    std::move(_10), std::move(_11), std::move(_12), std::move(_13), std::move(_14),
    std::move(_15), std::move(_16), std::move(_17), std::move(_18), std::move(_19),
    std::move(_1a), std::move(_1b), std::move(_1c), std::move(_1d), std::move(_1e),
    std::move(_1f), std::move(_20), std::move(_21), std::move(_22), std::move(_23),
    std::move(_24), std::move(_25), std::move(_26), std::move(_27), std::move(_28),
    std::move(_29), std::move(_2a), std::move(_2b), std::move(_2c), std::move(_2d),
    std::move(_2e), std::move(_2f), std::move(_30), std::move(_31), std::move(_32),
    std::move(_33), std::move(_34), std::move(_35), std::move(_36), std::move(_37),
    std::move(_38), std::move(_39), std::move(_3a), std::move(_3b), std::move(_3c),
    std::move(_3d), std::move(_3e), std::move(_3f), std::move(_40), std::move(_41),
    std::move(_42), std::move(_43), std::move(_44), std::move(_45), std::move(_46),
    std::move(_47), std::move(_48), std::move(_49), std::move(_4a), std::move(_4b),
    std::move(_4c), std::move(_4d), std::move(_4e), std::move(_4f), std::move(_50),
    std::move(_51), std::move(_52), std::move(_53), std::move(_54), std::move(_55),
    std::move(_56), std::move(_57), std::move(_58), std::move(_59), std::move(_5a),
    std::move(_5b), std::move(_5c), std::move(_5d), std::move(_5e), std::move(_5f),
    std::move(_60), std::move(_61), std::move(_62), std::move(_63), std::move(_64)
);
}
};


}

