/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_YAML_DEF_HPP)
#define OMD_PARSER_YAML_DEF_HPP

#include "yaml.hpp"
#include <algorithm>

namespace omd { namespace parser
{
    namespace detail
    {
        struct count_chars
        {
            template <typename Range>
            struct result { typedef std::size_t type; };

            template <typename Range>
            std::size_t operator()(Range const& rng) const
            {
                return std::distance(rng.begin(), rng.end());
            }
        };

        //~ struct parse_block
        //~ {
            //~ template <typename This>
            //~ struct result { typedef void type; };

            //~ template <typename This>
            //~ void operator()(This* g) const
            //~ {

            //~ }
        //~ };
    }

    template <typename Iterator>
    yaml<Iterator>::yaml(std::string const& source_file)
      : yaml::base_type(start),
        error_handler(error_handler_t(source_file))
    {
        namespace phx = boost::phoenix;

        qi::skip_type skip;
        auto space = ws.start.alias();

        qi::_val_type _val;
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::_r1_type _r1;
        qi::_a_type _a;

        qi::repeat_type repeat;
        qi::inf_type inf;
        qi::eol_type eol;
        qi::eoi_type eoi;
        qi::char_type char_;

        qi::blank_type blank;
        phx::function<detail::count_chars> count_chars;

        auto append = _val += _1;
        auto pb = phx::push_back(_val, _1);

        start =
                skip(space)[flow_value]
            |   blocks
            ;

        blocks = +block[pb];

        block =
                indent[_a = _1]                   // indent and save the number of indents
            >>  first_line[append]                // get the rest of the first line
            >>  *(blank_line | line(_a)[append])  // get the lines
            >>  repeat(_a)[blank]                 // must end with exact indent as started
            ;

        auto endl = eol | eoi;

        line =                                    // a line is:
                repeat(_r1 + 1, inf)[blank]       // at least current indent + 1 blanks
            >>  (+(char_ - endl)[append])         // one or more non-endl characters
            >>  endl                              // terminated by endl
            ;

        first_line =                              // the first_line is:
                (+(char_ - endl)[append])         // one or more non-endl characters
            >>  endl                              // terminated by endl
            ;

        blank_line = *blank >> eol;
        indent = (*blank)[_val = count_chars(_1)];

        BOOST_SPIRIT_DEBUG_NODES(
            (start)
            (blocks)
            (block)
            (line)
            (first_line)
            (blank_line)
            (indent)
        );

        qi::on_error<qi::fail>(start, error_handler(_1, _2, _3, _4));
    }
}}

#endif
