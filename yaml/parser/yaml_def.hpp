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

        struct parse_block
        {
            template <typename, typename, typename, typename>
            struct result { typedef void type; };

            template <typename YamlG, typename Attr, typename Ranges>
            void operator()(YamlG* g, Attr& attr, Ranges const& rngs, bool& pass) const
            {
                ast::array_t* arr_p = boost::get<ast::array_t>(&attr);

                // hack:
                if (arr_p == 0)
                {
                    attr = ast::array_t();
                    arr_p = boost::get<ast::array_t>(&attr);
                }

                using boost::spirit::qi::parse;
                typedef typename Ranges::second_type::const_iterator iter_t;

                {
                    //~ ast::value_t value;
                    //~ iter_t first = rngs.first.begin();
                    //~ iter_t last = rngs.first.end();

                    //~ bool is_array = phrase_parse(first, last, '-', g->ws, value);
                    //~ if (boost::get<ast::null_t>(&attr))
                    //~ {
                        //~ attr = ast::array_t();
                    //~ }

                    //~ arr_p = boost::get<ast::array_t>(&attr);

                    //~ if (!arr_p)
                    //~ {
                        //~ pass = false;
                        //~ return;
                    //~ }

                    //~ if (phrase_parse(first, last, g->scalar, g->ws, value))
                    //~ {
                        //~ arr_p->push_back(value);
                    //~ }
                    //~ else
                    //~ {
                        //~ pass = false;
                        //~ return;
                    //~ }

                    std::string utf8;
                    detail::push_utf8 push_back;
                    BOOST_FOREACH(uchar code_point, rngs.first)
                    {
                        push_back(utf8, code_point);
                    }
                    arr_p->push_back(utf8);
                }

                {
                    ast::value_t value;
                    iter_t first = rngs.second.begin();
                    iter_t last = rngs.second.end();
                    if (parse(first, last, *g, value))
                        arr_p->push_back(value);
                }
            }
        };
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
        qi::raw_type raw;
        qi::omit_type omit;
        qi::_pass_type _pass;

        qi::blank_type blank;
        phx::function<detail::count_chars> count_chars;

        auto append = _val += _1;
        //~ auto pb = phx::push_back(_val, _1);
        phx::function<detail::parse_block> parse_block;

        start =
                skip(space)[flow_value]
            |   blocks
            ;

        flow = skip(space)[flow_value];
        scalar = skip(space)[flow_value.scalar_value];

        //~ block_content =
                //~ '-' >> scalar
            //~ |   scalar >> ':'
            //~ ;

        blocks = +(block[parse_block(this, _val, _1, _pass)]);

        block %=
                omit[indent[_a = _1]]             // indent and save the number of indents
            >>  raw[first_line]                   // get the rest of the first line
            >>  raw[*(blank_line | line(_a))]     // get the lines
            >>  repeat(_a)[blank]                 // must end with exact indent as started
            ;

        auto endl = eol | eoi;

        line =                                    // a line is:
                repeat(_r1 + 1, inf)[blank]       // at least current indent + 1 blanks
            >>  (+(char_ - endl))                 // one or more non-endl characters
            >>  endl                              // terminated by endl
            ;

        first_line =                              // the first_line is:
                (+(char_ - endl))                 // one or more non-endl characters
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
