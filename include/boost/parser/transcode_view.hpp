// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_TRANSCODE_VIEW_HPP
#define BOOST_PARSER_TRANSCODE_VIEW_HPP

#include <boost/parser/detail/text/transcode_view.hpp>


namespace boost::parser {

#if defined(BOOST_PARSER_DOXYGEN)

    /** A view adaptor that produces a UTF-8 view of the given view. */
    constexpr detail::unspecified as_utf8;

    /** A view adaptor that produces a UTF-16 view of the given view. */
    constexpr detail::unspecified as_utf16;

    /** A view adaptor that produces a UTF-32 view of the given view. */
    constexpr detail::unspecified as_utf32;

#else

    using format = detail::text::format;

#if BOOST_PARSER_DETAIL_TEXT_USE_ALIAS_CTAD

    template<class V>
    using utf8_view = detail::text::utf_view<format::utf8, V>;
    template<class V>
    using utf16_view = detail::text::utf_view<format::utf16, V>;
    template<class V>
    using utf32_view = detail::text::utf_view<format::utf32, V>;

#else

#if BOOST_PARSER_USE_CONCEPTS
    template<detail::text::utf_range V>
        requires std::ranges::view<V>
#else
    template<typename V>
#endif
    class utf8_view : public detail::text::utf_view<format::utf8, V>
    {
    public:
        constexpr utf8_view()
#if BOOST_PARSER_USE_CONCEPTS
            requires std::default_initializable<V>
#endif
        = default;
        constexpr utf8_view(V base) :
            detail::text::utf_view<format::utf8, V>{std::move(base)}
        {}
    };
#if BOOST_PARSER_USE_CONCEPTS
    template<detail::text::utf_range V>
        requires std::ranges::view<V>
#else
    template<typename V>
#endif
    class utf16_view : public detail::text::utf_view<format::utf16, V>
    {
    public:
        constexpr utf16_view()
#if BOOST_PARSER_USE_CONCEPTS
            requires std::default_initializable<V>
#endif
        = default;
        constexpr utf16_view(V base) :
            detail::text::utf_view<format::utf16, V>{std::move(base)}
        {}
    };
#if BOOST_PARSER_USE_CONCEPTS
    template<detail::text::utf_range V>
        requires std::ranges::view<V>
#else
    template<typename V>
#endif
    class utf32_view : public detail::text::utf_view<format::utf32, V>
    {
    public:
        constexpr utf32_view()
#if BOOST_PARSER_USE_CONCEPTS
            requires std::default_initializable<V>
#endif
        = default;
        constexpr utf32_view(V base) :
            detail::text::utf_view<format::utf32, V>{std::move(base)}
        {}
    };

#if BOOST_PARSER_USE_CONCEPTS
    template<class R>
    utf8_view(R &&) -> utf8_view<std::views::all_t<R>>;
    template<class R>
    utf16_view(R &&) -> utf16_view<std::views::all_t<R>>;
    template<class R>
    utf32_view(R &&) -> utf32_view<std::views::all_t<R>>;
#endif

#endif

    inline constexpr auto as_utf8 = detail::text::as_utf8;
    inline constexpr auto as_utf16 = detail::text::as_utf16;
    inline constexpr auto as_utf32 = detail::text::as_utf32;

#endif
}

#endif
