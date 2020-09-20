// Copyright (C) 2018 Robert N. Steagall
// Copyright (C) 2019 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_DETAIL_TEXT_TRANSCODE_ALGORITHM_HPP
#define BOOST_PARSER_DETAIL_TEXT_TRANSCODE_ALGORITHM_HPP

#include <boost/parser/detail/text/transcode_iterator.hpp>
#include <boost/parser/detail/text/detail/unpack.hpp>

#include <boost/config.hpp>


namespace boost { namespace text {

    /** The result returned from some variations of the transcode
        algorithms. */
    template<typename Iter, typename OutIter>
    struct transcode_result
    {
        Iter iter;
        OutIter out;
    };

    namespace detail {
        template<typename OutIter>
        constexpr OutIter
        read_into_utf8_iter(uint32_t cp, OutIter out)
        {
            if (cp < 0x80) {
                *out = static_cast<char>(cp);
                ++out;
            } else if (cp < 0x800) {
                *out = static_cast<char>(0xC0 + (cp >> 6));
                ++out;
                *out = static_cast<char>(0x80 + (cp & 0x3f));
                ++out;
            } else if (cp < 0x10000) {
                *out = static_cast<char>(0xe0 + (cp >> 12));
                ++out;
                *out = static_cast<char>(0x80 + ((cp >> 6) & 0x3f));
                ++out;
                *out = static_cast<char>(0x80 + (cp & 0x3f));
                ++out;
            } else {
                *out = static_cast<char>(0xf0 + (cp >> 18));
                ++out;
                *out = static_cast<char>(0x80 + ((cp >> 12) & 0x3f));
                ++out;
                *out = static_cast<char>(0x80 + ((cp >> 6) & 0x3f));
                ++out;
                *out = static_cast<char>(0x80 + (cp & 0x3f));
                ++out;
            }
            return out;
        }

        template<typename OutIter>
        constexpr OutIter
        read_into_utf16_iter(uint32_t cp, OutIter out)
        {
            uint16_t const high_surrogate_base = 0xd7c0;
            uint16_t const low_surrogate_base = 0xdc00;

            if (cp < 0x10000) {
                *out = static_cast<uint16_t>(cp);
                ++out;
            } else {
                *out = static_cast<uint16_t>(cp >> 10) + high_surrogate_base;
                ++out;
                *out = static_cast<uint16_t>(cp & 0x3ff) + low_surrogate_base;
                ++out;
            }
            return out;
        }

        template<
            bool UseN,
            typename InputIter,
            typename Sentinel,
            typename OutIter>
        transcode_result<InputIter, OutIter> transcode_utf_8_to_16(
            InputIter first,
            Sentinel last,
            std::ptrdiff_t n,
            OutIter out,
            std::input_iterator_tag)
        {
            for (; first != last && (!UseN || n); --n) {
                unsigned char const c = *first;
                if (c < 0x80) {
                    *out = *first;
                    ++first;
                    ++out;
                } else {
                    auto const cp = detail::advance(first, last);
                    out = detail::read_into_utf16_iter(cp, out);
                }
            }
            return {first, out};
        }

        template<bool UseN, typename Iter, typename OutIter>
        transcode_result<Iter, OutIter> transcode_utf_8_to_16(
            Iter first,
            Iter last,
            std::ptrdiff_t n,
            OutIter out,
            std::random_access_iterator_tag)
        {
            return transcode_utf_8_to_16<UseN>(
                first, last, n, out, std::input_iterator_tag{});
        }

        template<
            bool UseN,
            typename InputIter,
            typename Sentinel,
            typename OutIter>
        transcode_result<InputIter, OutIter> transcode_utf_8_to_32(
            InputIter first,
            Sentinel last,
            std::ptrdiff_t n,
            OutIter out,
            std::input_iterator_tag)
        {
            for (; first != last && (!UseN || n); --n) {
                unsigned char const c = *first;
                if (c < 0x80) {
                    *out = *first;
                    ++first;
                    ++out;
                } else {
                    *out = detail::advance(first, last);
                    ++out;
                }
            }
            return {first, out};
        }

        template<bool UseN, typename Iter, typename OutIter>
        transcode_result<Iter, OutIter> transcode_utf_8_to_32(
            Iter first,
            Iter last,
            std::ptrdiff_t n,
            OutIter out,
            std::random_access_iterator_tag)
        {
            return transcode_utf_8_to_32<UseN>(
                first, last, n, out, std::input_iterator_tag{});
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_8(
            utf8_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            for (; first != last && (!UseN || n); ++first, ++out) {
                *out = *first;
                --n;
            }
            return {first, out};
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_16(
            utf8_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            return detail::transcode_utf_8_to_16<UseN>(
                first,
                last,
                n,
                out,
                typename std::iterator_traits<Iter>::iterator_category{});
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_32(
            utf8_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            return detail::transcode_utf_8_to_32<UseN>(
                first,
                last,
                n,
                out,
                typename std::iterator_traits<Iter>::iterator_category{});
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_8(
            utf16_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            uint32_t const high_surrogate_max = 0xdbff;
            uint16_t const high_surrogate_base = 0xd7c0;
            uint16_t const low_surrogate_base = 0xdc00;

            for (; first != last && (!UseN || n); ++first, --n) {
                uint32_t const hi = *first;
                if (surrogate(hi)) {
                    if (hi <= high_surrogate_max) {
                        ++first;
                        if (first == last) {
                            uint32_t const cp = replacement_character();
                            out = detail::read_into_utf8_iter(cp, out);
                            ++out;
                            return {first, out};
                        }
                        uint32_t const lo = *first;
                        if (low_surrogate(lo)) {
                            uint32_t const cp =
                                ((hi - high_surrogate_base) << 10) +
                                (lo - low_surrogate_base);
                            out = detail::read_into_utf8_iter(cp, out);
                            continue;
                        }
                    }
                    out = detail::read_into_utf8_iter(
                        replacement_character(), out);
                } else {
                    out = detail::read_into_utf8_iter(hi, out);
                }
            }

            return {first, out};
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_16(
            utf16_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            for (; first != last && (!UseN || n); ++first, ++out, --n) {
                *out = *first;
            }
            return {first, out};
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_32(
            utf16_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            uint32_t const high_surrogate_max = 0xdbff;
            uint16_t const high_surrogate_base = 0xd7c0;
            uint16_t const low_surrogate_base = 0xdc00;

            for (; first != last && (!UseN || n); ++first, --n) {
                uint32_t const hi = *first;
                if (surrogate(hi)) {
                    if (hi <= high_surrogate_max) {
                        ++first;
                        if (first == last) {
                            *out = replacement_character();
                            ++out;
                            return {first, out};
                        }
                        uint32_t const lo = *first;
                        if (low_surrogate(lo)) {
                            uint32_t const cp =
                                ((hi - high_surrogate_base) << 10) +
                                (lo - low_surrogate_base);
                            *out = cp;
                            ++out;
                            continue;
                        }
                    }
                    *out = replacement_character();
                    ++out;
                } else {
                    *out = hi;
                    ++out;
                }
            }

            return {first, out};
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_8(
            utf32_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            for (; first != last && (!UseN || n); ++first, --n) {
                out = detail::read_into_utf8_iter(*first, out);
            }
            return {first, out};
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_16(
            utf32_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            for (; first != last && (!UseN || n); ++first, --n) {
                out = detail::read_into_utf16_iter(*first, out);
            }
            return {first, out};
        }

        template<bool UseN, typename Iter, typename Sentinel, typename OutIter>
        transcode_result<Iter, OutIter> transcode_to_32(
            utf32_tag, Iter first, Sentinel last, std::ptrdiff_t n, OutIter out)
        {
            for (; first != last && (!UseN || n); ++first, ++out, --n) {
                *out = *first;
            }
            return {first, out};
        }
    }

#if 0
    /** Copies the code points in the range [first, last) to out, changing the
        encoding from UTF-8 to UTF-32.  */
    template<typename InputIter, typename Sentinel, typename OutIter>
    transcode_result<InputIter, OutIter> transcode_utf_8_to_32_take_n(
        InputIter first, Sentinel last, std::ptrdiff_t n, OutIter out)
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_32<true>(r.tag_, r.f_, r.l_, n, out);
    }

    /** Copies the first `n` code points in the range [first, last) to out,
        changing the encoding from UTF-8 to UTF-32.  */
    template<typename InputIter, typename Sentinel, typename OutIter>
    transcode_result<InputIter, OutIter> transcode_utf_8_to_32_take_n(
        InputIter first, Sentinel last, std::ptrdiff_t n, OutIter out)
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_32<true>(r.tag_, r.f_, r.l_, n, out);
    }

    /** Copies the first `n` code points in the range [first, last) to out,
        changing the encoding from UTF-8 to UTF-32.  */
    template<typename InputIter, typename Sentinel, typename OutIter>
    transcode_result<InputIter, OutIter>
    transcode_utf_8_to_32_take_n(Range && r, std::ptrdiff_t n, OutIter out)
    {
        return detail::transcode_utf_8_to_32_dispatch<true, Range, OutIter>::
            call(r, n, out)
                .out;
    }
#endif

}}

namespace boost { namespace text { BOOST_PARSER_DETAIL_TEXT_NAMESPACE_V1 {

    namespace dtl {
        template<
            bool UseN,
            typename Range,
            typename OutIter,
            bool _16Ptr = detail::_16_ptr<Range>::value,
            bool CPPtr = detail::cp_ptr<Range>::value>
        struct transcode_to_8_dispatch
        {
            static constexpr auto
            call(Range && r, std::ptrdiff_t n, OutIter out) noexcept
            {
                auto const u = detail::unpack_iterator_and_sentinel(
                    std::begin(r), std::end(r));
                return detail::transcode_to_8<UseN>(
                    u.tag_, u.f_, u.l_, n, out);
            }
        };

        template<bool UseN, typename Ptr, typename OutIter>
        struct transcode_to_8_dispatch<UseN, Ptr, OutIter, true, false>
        {
            static constexpr auto
            call(Ptr p, std::ptrdiff_t n, OutIter out) noexcept
            {
                return detail::transcode_to_8<UseN>(
                    detail::utf16_tag{}, p, null_sentinel{}, n, out);
            }
        };

        template<bool UseN, typename Ptr, typename OutIter>
        struct transcode_to_8_dispatch<UseN, Ptr, OutIter, false, true>
        {
            static constexpr auto
            call(Ptr p, std::ptrdiff_t n, OutIter out) noexcept
            {
                return detail::transcode_to_8<UseN>(
                    detail::utf32_tag{}, p, null_sentinel{}, n, out);
            }
        };

        template<
            bool UseN,
            typename Range,
            typename OutIter,
            bool CharPtr = detail::char_ptr<Range>::value,
            bool CPPtr = detail::cp_ptr<Range>::value>
        struct transcode_to_16_dispatch
        {
            static constexpr auto
            call(Range && r, std::ptrdiff_t n, OutIter out) noexcept
            {
                auto const u = detail::unpack_iterator_and_sentinel(
                    std::begin(r), std::end(r));
                return detail::transcode_to_16<UseN>(
                    u.tag_, u.f_, u.l_, n, out);
            }
        };

        template<bool UseN, typename Ptr, typename OutIter>
        struct transcode_to_16_dispatch<UseN, Ptr, OutIter, true, false>
        {
            static constexpr auto
            call(Ptr p, std::ptrdiff_t n, OutIter out) noexcept
            {
                return detail::transcode_to_16<UseN>(
                    detail::utf8_tag{}, p, null_sentinel{}, n, out);
            }
        };

        template<bool UseN, typename Ptr, typename OutIter>
        struct transcode_to_16_dispatch<UseN, Ptr, OutIter, false, true>
        {
            static constexpr auto
            call(Ptr p, std::ptrdiff_t n, OutIter out) noexcept
            {
                return detail::transcode_to_16<UseN>(
                    detail::utf32_tag{}, p, null_sentinel{}, n, out);
            }
        };

        template<
            bool UseN,
            typename Range,
            typename OutIter,
            bool CharPtr = detail::char_ptr<Range>::value,
            bool _16Ptr = detail::_16_ptr<Range>::value>
        struct transcode_to_32_dispatch
        {
            static constexpr auto
            call(Range && r, std::ptrdiff_t n, OutIter out) noexcept
            {
                auto const u = detail::unpack_iterator_and_sentinel(
                    std::begin(r), std::end(r));
                return detail::transcode_to_32<UseN>(
                    u.tag_, u.f_, u.l_, n, out);
            }
        };

        template<bool UseN, typename Ptr, typename OutIter>
        struct transcode_to_32_dispatch<UseN, Ptr, OutIter, true, false>
        {
            static constexpr auto
            call(Ptr p, std::ptrdiff_t n, OutIter out) noexcept
            {
                return detail::transcode_to_32<UseN>(
                    detail::utf8_tag{}, p, null_sentinel{}, n, out);
            }
        };

        template<bool UseN, typename Ptr, typename OutIter>
        struct transcode_to_32_dispatch<UseN, Ptr, OutIter, false, true>
        {
            static constexpr auto
            call(Ptr p, std::ptrdiff_t n, OutIter out) noexcept
            {
                return detail::transcode_to_32<UseN>(
                    detail::utf16_tag{}, p, null_sentinel{}, n, out);
            }
        };
    }

    /** Copies the code points in the range `[first, last)` to `out`, changing
        the encoding to UTF-8. */
    template<typename Iter, typename Sentinel, typename OutIter>
    OutIter transcode_to_utf8(Iter first, Sentinel last, OutIter out)
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_8<false>(r.tag_, r.f_, r.l_, -1, out).out;
    }

    /** Copies the code points in the range `r` to `out`, changing the
        encoding from UTF-8.  */
    template<typename Range, typename OutIter>
    OutIter transcode_to_utf8(Range && r, OutIter out)
    {
        return dtl::transcode_to_8_dispatch<false, Range, OutIter>::call(
            r, -1, out).out;
    }

    /** Copies the code points in the range `[first, last)` to `out`, changing
        the encoding to UTF-16. */
    template<typename Iter, typename Sentinel, typename OutIter>
    OutIter transcode_to_utf16(Iter first, Sentinel last, OutIter out)
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_16<false>(r.tag_, r.f_, r.l_, -1, out).out;
    }

    /** Copies the code points in the range `r` to `out`, changing the
        encoding from UTF-16.  */
    template<typename Range, typename OutIter>
    OutIter transcode_to_utf16(Range && r, OutIter out)
    {
        return dtl::transcode_to_16_dispatch<false, Range, OutIter>::call(
            r, -1, out).out;
    }

    /** Copies the code points in the range `[first, last)` to `out`, changing
        the encoding to UTF-32. */
    template<typename Iter, typename Sentinel, typename OutIter>
    OutIter transcode_to_utf32(Iter first, Sentinel last, OutIter out)
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_32<false>(r.tag_, r.f_, r.l_, -1, out).out;
    }

    /** Copies the code points in the range `r` to `out`, changing the
        encoding from UTF-32.  */
    template<typename Range, typename OutIter>
    OutIter transcode_to_utf32(Range && r, OutIter out)
    {
        return dtl::transcode_to_32_dispatch<false, Range, OutIter>::call(
            r, -1, out).out;
    }

}}}

#if defined(BOOST_TEXT_DOXYGEN) || BOOST_PARSER_USE_CONCEPTS

namespace boost { namespace text { BOOST_PARSER_DETAIL_TEXT_NAMESPACE_V2 {

    /** Copies the code points in the range `[first, last)` to `out`, changing
        the encoding to UTF-8. */
    template<
        typename I,
        std::sentinel_for<I> S,
        std::output_iterator<uint8_t> O>
        // clang-format off
        requires utf16_iter<I> || utf32_iter<I>
    O transcode_to_utf8(I first, S last, O out)
    // clang-format on
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_8<false>(r.tag_, r.f_, r.l_, -1, out).out;
    }

    /** Copies the code points in the range `r` to `out`, changing the
        encoding from UTF-8.  */
    template<typename R, std::output_iterator<uint8_t> O>
        // clang-format off
        requires utf16_range<R> || utf32_range<R> ||
                 utf16_pointer<R> || utf32_pointer<R>
    O transcode_to_utf8(R && r, O out)
    // clang-format on
    {
        if constexpr (utf16_pointer<R>) {
            return detail::transcode_to_8<false>(
                       detail::utf16_tag{}, r, null_sentinel{}, -1, out)
                .out;
        } else if constexpr (utf32_pointer<R>) {
            return detail::transcode_to_8<false>(
                       detail::utf32_tag{}, r, null_sentinel{}, -1, out)
                .out;
        } else {
            auto const u = detail::unpack_iterator_and_sentinel(
                std::ranges::begin(r), std::ranges::end(r));
            return detail::transcode_to_8<false>(u.tag_, u.f_, u.l_, -1, out)
                .out;
        }
    }

    /** Copies the code points in the range `[first, last)` to `out`, changing
        the encoding to UTF-16. */
    template<
        typename I,
        std::sentinel_for<I> S,
        std::output_iterator<uint16_t> O>
        // clang-format off
        requires utf8_iter<I> || utf32_iter<I>
    O transcode_to_utf16(I first, S last, O out)
    // clang-format on
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_16<false>(r.tag_, r.f_, r.l_, -1, out).out;
    }

    /** Copies the code points in the range `r` to `out`, changing the
        encoding from UTF-16.  */
    template<typename R, std::output_iterator<uint16_t> O>
        // clang-format off
        requires utf8_range<R> || utf32_range<R> ||
                 utf8_pointer<R> || utf32_pointer<R>
    O transcode_to_utf16(R && r, O out)
    // clang-format on
    {
        if constexpr (utf8_pointer<R>) {
            return detail::transcode_to_16<false>(
                       detail::utf8_tag{}, r, null_sentinel{}, -1, out)
                .out;
        } else if constexpr (utf32_pointer<R>) {
            return detail::transcode_to_16<false>(
                       detail::utf32_tag{}, r, null_sentinel{}, -1, out)
                .out;
        } else {
            auto const u = detail::unpack_iterator_and_sentinel(
                std::ranges::begin(r), std::ranges::end(r));
            return detail::transcode_to_16<false>(u.tag_, u.f_, u.l_, -1, out)
                .out;
        }
    }

    /** Copies the code points in the range `[first, last)` to `out`, changing
        the encoding to UTF-32. */
    template<
        typename I,
        std::sentinel_for<I> S,
        std::output_iterator<uint32_t const &> O>
        // clang-format off
        requires utf8_iter<I> || utf16_iter<I>
    O transcode_to_utf32(I first, S last, O out)
    // clang-format on
    {
        auto const r = detail::unpack_iterator_and_sentinel(first, last);
        return detail::transcode_to_32<false>(r.tag_, r.f_, r.l_, -1, out).out;
    }

    /** Copies the code points in the range `r` to `out`, changing the
        encoding from UTF-32.  */
    template<typename R, std::output_iterator<uint32_t> O>
        // clang-format off
        requires utf8_range<R> || utf16_range<R> ||
                 utf8_pointer<R> || utf16_pointer<R>
    O transcode_to_utf32(R && r, O out)
    // clang-format on
    {
        if constexpr (utf8_pointer<R>) {
            return detail::transcode_to_32<false>(
                       detail::utf8_tag{}, r, null_sentinel{}, -1, out)
                .out;
        } else if constexpr (utf16_pointer<R>) {
            return detail::transcode_to_32<false>(
                       detail::utf16_tag{}, r, null_sentinel{}, -1, out)
                .out;
        } else {
            auto const u = detail::unpack_iterator_and_sentinel(
                std::ranges::begin(r), std::ranges::end(r));
            return detail::transcode_to_32<false>(u.tag_, u.f_, u.l_, -1, out)
                .out;
        }
    }

}}}

#endif

#endif
