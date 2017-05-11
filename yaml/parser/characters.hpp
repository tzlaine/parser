/**
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef YAML_PARSER_CHARACTERS_HPP
#define YAML_PARSER_CHARACTERS_HPP

#include <yaml/parser/parser_fwd.hpp>
#include <yaml/parser/error_handler.hpp>


namespace yaml { namespace parser {

    struct characters_t
    {
        explicit characters_t (bool verbose);

        qi::rule<iterator_t, parsed_uchar_t()> printable;
        qi::rule<iterator_t, parsed_uchar_t()> nb_json;
        qi::rule<iterator_t> bom;
        qi::rule<iterator_t, parsed_uchar_t()> nb_char;
        qi::rule<iterator_t, parsed_uchar_t()> ns_char;
        qi::rule<iterator_t, parsed_uchar_t()> uri_char;
        qi::rule<iterator_t, parsed_uchar_t()> tag_char;
        qi::rule<iterator_t, parsed_uchar_t()> esc_char;
    };

} }

#if YAML_HEADER_ONLY
#include <yaml/parser/characters_def.hpp>
#endif

#endif
