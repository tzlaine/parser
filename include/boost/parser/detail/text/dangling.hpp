// Copyright (C) 2020 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_PARSER_DETAIL_TEXT_DANGLING_HPP
#define BOOST_PARSER_DETAIL_TEXT_DANGLING_HPP

#include <boost/parser/detail/text/config.hpp>


#if defined(BOOST_TEXT_DOXYGEN) || BOOST_PARSER_USE_CONCEPTS

namespace boost::parser::detail::text {
    template<std::ranges::range R, std::ranges::view V>
    using borrowed_view_t = std::
        conditional_t<std::ranges::borrowed_range<R>, V, std::ranges::dangling>;
}

#endif

#endif
