// Copyright (C) 2018 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/parser/parser.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::parser;
using boost::is_same;

void compile_attribute_non_unicode()
{
    // range
    {
        char const r[] = "";

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<char>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
    }
    // pointer-as-range (covers iter/sent case, as that's what gets used internally)
    {
        char const * r = "";

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<char>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
    }
    // iter/iter
    {
        char const chars[] = "";
        auto first = std::begin(chars);
        auto const last = std::end(chars);

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<char>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
    }
}

void compile_attribute_unicode_utf8()
{
#if defined(__cpp_char8_t)
    {
        char8_t const chars[] = u8"";
        auto first = std::begin(chars);
        auto const last = std::end(chars);

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<uint32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<uint32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, uint32_t>>>));
        }
    }
#endif
    {
        char const chars[] = "";
        auto const r = boost::parser::detail::text::as_utf8(chars);

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<uint32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<uint32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, uint32_t>>>));
        }
    }
#if defined(__cpp_char8_t)
    {
        char8_t const r[] = u8"";

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<uint32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<uint32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, uint32_t>>>));
        }
    }
    {
        char8_t const * r = u8"";

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<uint32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<uint32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(r, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, uint32_t>>>));
        }
    }
#endif
}

void compile_attribute_unicode_utf32()
{
    {
        int const chars[] = {0};
        auto first = std::begin(chars);
        auto const last = std::end(chars);

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<int>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<int>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<int, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, int>>>));
        }
    }
    {
        uint32_t const chars[] = {0};
        auto first = std::begin(chars);
        auto const last = std::end(chars);

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<uint32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<uint32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, uint32_t>>>));
        }
    }
    {
        char32_t const chars[] = {0};
        auto first = std::begin(chars);
        auto const last = std::end(chars);

        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<char32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<char32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(first, last, parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, char32_t>>>));
        }
    }
    {
        {
            constexpr auto parser = char_;
            using attr_t = decltype(parse(U"", parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char32_t>>));
        }
        {
            constexpr auto parser = *char_;
            using attr_t = decltype(parse(U"", parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<std::vector<char32_t>>>));
        }
        {
            constexpr auto parser = string("foo");
            using attr_t = decltype(parse(U"", parser));
            BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
        }
        {
            constexpr auto parser = char_ >> string("foo");
            using attr_t = decltype(parse(U"", parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<char32_t, std::string>>>));
        }
        {
            constexpr auto parser = string("foo") >> char_;
            using attr_t = decltype(parse(U"", parser));
            BOOST_MPL_ASSERT(
                (is_same<attr_t, std::optional<tuple<std::string, char32_t>>>));
        }
    }
}

rule<class test_rule, std::string> const test_rule = "test_rule";
auto const test_rule_def = +char_;
BOOST_PARSER_DEFINE_RULE(test_rule);

rule<class ints, std::vector<int>> const ints = "ints";
auto twenty_zeros = [](auto & ctx) { _val(ctx).resize(20, 0); };
auto push_back = [](auto & ctx) { _val(ctx).push_back(_attr(ctx)); };
auto const ints_def = lit("20-zeros")[twenty_zeros] | +int_[push_back];
BOOST_PARSER_DEFINE_RULE(ints);

void compile_attribute_sentinel()
{
    char const * chars = "";
    auto first = chars;
    boost::parser::detail::text::null_sentinel last;

    {
        constexpr auto parser = eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = eol;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = eoi;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = attr(3.0);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<double>>));
    }
    {
        constexpr auto parser = attr('c');
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        constexpr auto parser = cp;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
    }
    {
        constexpr auto parser = cu;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = 'c'_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8'c'_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U'c'_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = "str"_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8"str"_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U"str"_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = 'c'_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8'c'_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U'c'_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = "str"_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8"str"_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U"str"_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }
    {
        constexpr auto parser = lit('c');
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = lit(U'c');
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = lit("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        std::string str = "str";
        auto parser = lit(str);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = bool_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<bool>>));
    }
    {
        constexpr auto parser = bin;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = oct;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = hex;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = ushort_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned short>>));
    }
    {
        constexpr auto parser = uint_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = ulong_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned long>>));
    }
    {
        constexpr auto parser = ulong_long;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned long long>>));
    }
    {
        constexpr auto parser = short_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<short>>));
    }
    {
        constexpr auto parser = int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<int>>));
    }
    {
        constexpr auto parser = long_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<long>>));
    }
    {
        constexpr auto parser = long_long;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<long long>>));
    }
    {
        constexpr auto parser = float_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<float>>));
    }
    {
        constexpr auto parser = double_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<double>>));
    }
    {
        symbols<float> parser;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<float>>));
    }
    {
        auto const c = [](auto & ctx) { return true; };
        constexpr auto parser = if_(c)[double_];
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<double>>));
    }
    {
        auto const x = [](auto & ctx) { return 2; };
        auto parser = switch_(x)(0, double_)(2, int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, std::optional<std::variant<double, int>>>));
    }

    {
        constexpr auto parser = int_ | int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<int>>));
    }
    {
        constexpr auto parser = double_ | int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, std::optional<std::variant<double, int>>>));
    }
    {
        constexpr auto parser = double_ | int_ | eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<
                attr_t,
                std::optional<std::optional<std::variant<double, int>>>>));
    }

    {
        constexpr auto parser = *cu >> string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<
                attr_t,
                std::optional<tuple<std::vector<char>, std::string>>>));
    }
    {
        constexpr auto parser = cu >> string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }

    {
        auto a = [](auto & ctx) {};
        constexpr auto parser = cu[a];
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }

    {
        using attr_t = decltype(parse(first, last, test_rule));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
#if 0 // Intentionally ill-formed
        std::vector<char> vec;
        auto result = parse(first, last, test_rule, vec);
#endif
    }

    {
        using attr_t = decltype(parse(first, last, ints));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::vector<int>>>));
    }
}

void compile_attribute()
{
    compile_attribute_non_unicode();
    compile_attribute_unicode_utf8();
    compile_attribute_unicode_utf32();
    compile_attribute_sentinel();

    char const chars[] = "";
    auto first = std::begin(chars);
    auto const last = std::end(chars);

    {
        constexpr auto parser = eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = eol;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = eoi;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = attr(3.0);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<double>>));
    }
    {
        constexpr auto parser = attr('c');
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        constexpr auto parser = cp;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<uint32_t>>));
    }
    {
        constexpr auto parser = cu;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = 'c'_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8'c'_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U'c'_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = "str"_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8"str"_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U"str"_l;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = 'c'_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8'c'_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U'c'_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<char>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = "str"_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = u8"str"_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }
    {
        using namespace boost::parser::literals;
        constexpr auto parser = U"str"_p;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }
    {
        constexpr auto parser = lit('c');
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = lit(U'c');
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = lit("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        std::string str = "str";
        auto parser = lit(str);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }
    {
        constexpr auto parser = bool_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<bool>>));
    }
    {
        constexpr auto parser = bin;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = oct;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = hex;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = ushort_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned short>>));
    }
    {
        constexpr auto parser = uint_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned int>>));
    }
    {
        constexpr auto parser = ulong_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned long>>));
    }
    {
        constexpr auto parser = ulong_long;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<unsigned long long>>));
    }
    {
        constexpr auto parser = short_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<short>>));
    }
    {
        constexpr auto parser = int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<int>>));
    }
    {
        constexpr auto parser = long_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<long>>));
    }
    {
        constexpr auto parser = long_long;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<long long>>));
    }
    {
        constexpr auto parser = float_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<float>>));
    }
    {
        constexpr auto parser = double_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<double>>));
    }
    {
        symbols<float> parser;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<float>>));
    }
    {
        auto const c = [](auto & ctx) { return true; };
        constexpr auto parser = if_(c)[double_];
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<double>>));
    }
    {
        auto const x = [](auto & ctx) { return 2; };
        auto parser = switch_(x)(0, double_)(2, int_);
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, std::optional<std::variant<double, int>>>));
    }

    {
        constexpr auto parser = int_ | int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<int>>));
    }
    {
        constexpr auto parser = double_ | int_;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<attr_t, std::optional<std::variant<double, int>>>));
    }
    {
        constexpr auto parser = double_ | int_ | eps;
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<
                attr_t,
                std::optional<std::optional<std::variant<double, int>>>>));
    }

    {
        constexpr auto parser = *cu >> string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT(
            (is_same<
                attr_t,
                std::optional<tuple<std::vector<char>, std::string>>>));
    }
    {
        constexpr auto parser = cu >> string("str");
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
    }

    {
        auto a = [](auto & ctx) {};
        constexpr auto parser = cu[a];
        using attr_t = decltype(parse(first, last, parser));
        BOOST_MPL_ASSERT((is_same<attr_t, bool>));
    }

    {
        using attr_t = decltype(parse(first, last, test_rule));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::string>>));
#if 0 // Intentionally ill-formed
        std::vector<char> vec;
        auto result = parse(first, last, test_rule, vec);
#endif
    }

    {
        using attr_t = decltype(parse(first, last, ints));
        BOOST_MPL_ASSERT((is_same<attr_t, std::optional<std::vector<int>>>));
    }
}
