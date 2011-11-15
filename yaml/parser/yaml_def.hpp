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
    }

    template <typename Iterator>
    yaml<Iterator>::yaml(std::string const& source_file)
      : yaml::base_type(yaml_start),
        error_handler(error_handler_t(source_file)),
        flow_g(current_indent),
        current_indent(0)
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
        qi::char_type char_;

        qi::repeat_type repeat;
        qi::eol_type eol;
        qi::omit_type omit;
        qi::_pass_type _pass;
        qi::eps_type eps;
        qi::attr_type attr;

        qi::blank_type blank;
        auto comment = '#' >> *(char_ - eol) >> eol;    // comments
        auto blank_eol = (*blank >> eol) | comment;     // empty until eol

        phx::function<detail::count_chars> count_chars;

        auto flow_compound = skip(space)[flow_g.flow_start];
        auto flow_value = skip(space)[flow_g.flow_value];
        auto flow_scalar = skip(space)[flow_g.scalar_value.scalar_value];

        // no-skip version
        auto flow_scalar_ns = flow_g.scalar_value.scalar_value.alias();

        yaml_start =
                flow_compound
            |   blocks
            ;

        flow_in_block =
                blocks                                //  Give blocks a higher precedence
            |   flow_compound
            |   flow_scalar_ns                        //  Don't allow scalars to skip spaces
            |   (omit[blank_eol]                      //  If all else fails, then null_t
                  >> attr(ast::null_t()))
            ;

        auto get_indent =
            phx::ref(current_indent)
            ;

        auto save_indent =
            eps[_a = get_indent]
            ;

        auto restore_indent =
            eps[get_indent = _a]
            ;

        auto block_main =
                block_seq
            |   block_map
            ;

        blocks %=
                omit[*blank_eol]                      //  Ignore blank lines $$$ BUG $$$ this prevents null elements
            >>  save_indent
            >>  (block_main | !restore_indent)
            >>  restore_indent
            ;

        auto skip_indent =
            repeat(get_indent)[blank]
            ;

        indent = skip_indent >> (*blank)[_val = count_chars(_1)];

        auto start_indent =
            indent[ get_indent = _1 ]
            ;

        auto block_seq_indicator =                    //  Lookahead and see if we have a
            &(start_indent >> '-' >> (blank | eol))   //  sequence indicator. Save the indent
            ;                                         //  in local variable _a

        block_seq =
                omit[block_seq_indicator]
            >>  +block_seq_entry                      //  Get the entries passing in the
            ;                                         //  indent level

        block_seq_entry =
                omit[*blank_eol]                      //  Ignore blank lines
            >>  omit[skip_indent]                     //  Indent get_indent spaces
            >>  omit['-' >> (blank | &eol)]           //  Get the sequence indicator '-'
            >>  flow_in_block                         //  Get the entry
            ;

        auto block_map_indicator =                    //  Lookahead and see if we have a
            &(  start_indent                          //  map indicator. Save the indent
            >>  flow_scalar                           //  in local variable _a
            >>  skip(space)[':']
            )
            ;

        block_map =
                omit[block_map_indicator]
            >>  +block_map_entry                      //  Get the entries passing in the
            ;                                         //  indent level

        block_map_entry =
                omit[*blank_eol]                      //  Ignore blank lines
            >>  omit[skip_indent]                     //  Indent get_indent spaces
            >>  flow_scalar                           //  Get the key
            >>  omit[skip(space)[':']]                //  Get the map indicator ':'
            >>  omit[*blank]                          //  Ignore blank spaces
            >>  flow_in_block                         //  Get the value
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (yaml_start)
            (flow_in_block)
            (blocks)
            (block_seq)
            (block_seq_entry)
            (block_map)
            (block_map_entry)
            (indent)
        );

        qi::on_error<qi::fail>(yaml_start, error_handler(_1, _2, _3, _4));
    }
}}

#endif
