#ifndef BOOST_PARSER_CONCEPTS_HPP
#define BOOST_PARSER_CONCEPTS_HPP

#include <boost/parser/parser_fwd.hpp>

#ifndef BOOST_PARSER_DOXYGEN

#define BOOST_PARSER_CXX20_CONCEPTS                                            \
    201703L < __cplusplus && defined(__cpp_lib_concepts)
#define BOOST_PARSER_CMCSTL2_CONCEPTS                                          \
    201703L <= __cplusplus && __has_include(<stl2/ranges.hpp>) &&              \
    !defined(BOOST_PARSER_DISABLE_CMCSTL2)

#if BOOST_PARSER_CXX20_CONCEPTS || BOOST_PARSER_CMCSTL2_CONCEPTS
#define BOOST_PARSER_USE_CONCEPTS 1
#include <stl2/ranges.hpp>
#else
#define BOOST_PARSER_USE_CONCEPTS 0
#endif

#if defined(__GNUC__) && __GNUC__ < 9
#define BOOST_PARSER_CONCEPT concept bool
#else
#define BOOST_PARSER_CONCEPT concept
#endif

#if BOOST_PARSER_CXX20_CONCEPTS
namespace ranges = std::ranges;
namespace std_ = std;
#elif BOOST_PARSER_CMCSTL2_CONCEPTS
namespace ranges = std::experimental::ranges;
namespace std_ = std::experimental;
#endif

#endif


namespace boost { namespace parser {

#if BOOST_PARSER_USE_CONCEPTS

    // clang-format off

    template<typename T>
    BOOST_PARSER_CONCEPT parsable_iterator =
        ranges::forward_iterator<T> && std::is_integral<std_::iter_value_t<T>>{};

    template<typename T>
    BOOST_PARSER_CONCEPT cp_iterator =
        parsable_iterator<T> && sizeof(std_::iter_value_t<T>) == 4u;

    template<typename T>
    BOOST_PARSER_CONCEPT parsable_range =
        ranges::forward_range<T> && std::is_integral<ranges::range_value_t<T>>{} ||
        parsable_pointer<T>;

    template<typename T>
    BOOST_PARSER_CONCEPT parsable_pointer =
        std::is_pointer<std::decay_t<T>>{} &&
        std::is_integral<std::remove_pointer_t<std::decay_t<T>>>{};

    template<typename T>
    BOOST_PARSER_CONCEPT parsable_range_or_pointer =
        parsable_range<T> || parsable_pointer<T>;

    template<typename Iter, typename Sentinel>
    using minimal_parse_context = decltype(detail::make_context(
        std::declval<Iter>(),
        std::declval<Sentinel>(),
        std::declval<bool &>(),
        std::declval<int &>(),
        std::declval<default_error_handler const &>(),
        std::declval<nope &>(),
        std::declval<symbol_table_tries_t &>()));

    template<typename T, typename Iter, typename Sentinel>
    BOOST_PARSER_CONCEPT parser_attr_out_param = requires (
        T const & t,
        hana::bool_<true> use_cbs,
        hana::bool_<false> dont_use_cbs,
        Iter & first,
        Sentinel last,
        minimal_parse_context<Iter, Sentinel> const & context,
        detail::skip_skipper skip,
        detail::flags flags,
        bool & success,
        decltype(t.call(use_cbs, first, last, context, skip, flags, success)) & attr) {
        { t.call(use_cbs, first, last, context, skip, flags, success, attr) };
        { t.call(dont_use_cbs, first, last, context, skip, flags, success, attr) };
    };

    template<typename T, typename Iter, typename Sentinel>
    BOOST_PARSER_CONCEPT parser =
        parsable_iterator<Iter> && std_::sentinel_for<Sentinel, Iter> &&
        requires (
            T const & t,
            hana::bool_<true> use_cbs,
            hana::bool_<false> dont_use_cbs,
            Iter & first,
            Sentinel last,
            minimal_parse_context<Iter, Sentinel> const & context,
            detail::skip_skipper skip,
            detail::flags flags,
            bool & success) {
            { t.call(use_cbs, first, last, context, skip, flags, success) };
            { t.call(dont_use_cbs, first, last, context, skip, flags, success) };
       } &&
       parser_attr_out_param<Iter, Sentinel>;

    template<typename T, typename Iter, typename Sentinel>
    BOOST_PARSER_CONCEPT error_handler =
        parsable_iterator<Iter> && std_::sentinel_for<Sentinel, Iter> &&
        requires (
            T const & t,
            Iter first,
            Sentinel last,
            parse_error<Iter> const & e,
            diagnostic_kind kind,
            std::string_view message,
            minimal_parse_context<Iter, Sentinel> const & context) {
            { t(first, last, e) } -> std_::same_as<error_handler_result>;
            { t.diagnose(kind, message, context, first) };
            { t.diagnose(kind, message, context) };
        };

    // clang-format on

#endif

}}

#endif
