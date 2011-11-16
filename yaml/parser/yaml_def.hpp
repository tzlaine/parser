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
        struct update_indent
        {
            template <typename Iterator, typename Range, typename Size, typename Fail>
            struct result { typedef void type; };

            template <typename Iterator, typename Range>
            void operator()(
                Iterator const& current_line,       //  start of current line
                Range const& rng,                   //  where we are now
                std::size_t& current_indent,        //  the current indent position
                bool& pass                          //  set to false to fail parsing
            ) const
            {
                std::size_t pos = std::size_t(std::distance(current_line, rng.begin()));
                if (pos >= current_indent)
                    current_indent = pos;
                else
                    pass = false;
            }
        };

        struct check_indent
        {
            template <typename Iterator, typename Range, typename Size, typename Fail>
            struct result { typedef void type; };

            template <typename Iterator, typename Range>
            void operator()(
                Iterator const& current_line,       //  start of current line
                Range const& rng,                   //  where we are now
                std::size_t const& current_indent,  //  the current indent position
                bool& pass                          //  set to false to fail parsing
            ) const
            {
                std::size_t pos = std::size_t(std::distance(current_line, rng.begin()));
                if (pos < current_indent)
                    pass = false;
            }
        };

        struct current_pos
        {
            template <typename Range>
            struct result { typedef typename Range::const_iterator type; };

            template <typename Range>
            typename Range::const_iterator operator()(Range const& rng) const
            {
                return rng.begin();
            }
        };
    }

    template <typename Iterator>
    yaml<Iterator>::yaml(std::string const& source_file)
      : yaml::base_type(yaml_start),
        flow_g(current_indent),
        current_indent(0),
        error_handler(error_handler_t(source_file))
    {
        namespace phx = boost::phoenix;
        phx::function<detail::current_pos> current_pos;
        phx::function<detail::update_indent> update_indent;
        phx::function<detail::check_indent> check_indent;

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
        qi::omit_type omit;
        qi::_pass_type _pass;
        qi::eps_type eps;
        qi::attr_type attr;
        qi::raw_type raw;

        qi::eol_type eol_;
        qi::blank_type blank;

        auto get_current_line =
            phx::ref(current_line)
            ;

        auto set_current_line =
            omit[raw[eps][get_current_line = current_pos(_1)]]
            ;

        auto eol = eol_ >> set_current_line;
        auto comment = '#' >> *(char_ - eol) >> eol;    // comments
        auto blank_eol = (*blank >> eol) | comment;     // empty until eol

        auto flow_compound = skip(space)[flow_g.flow_start];
        auto flow_value = skip(space)[flow_g.flow_value];
        auto flow_scalar = skip(space)[flow_g.scalar_value.scalar_value];

        // no-skip version
        auto flow_scalar_ns = flow_g.scalar_value.scalar_value.alias();

        auto get_indent =
            phx::ref(current_indent)
            ;

        auto save_indent =
            eps[_a = get_indent][ std::cout << phx::val("\n============================") << get_indent << std::endl ]
            ;

        auto increase_indent =
            eps[++get_indent][ std::cout << phx::val("\n============================") << get_indent << std::endl ]
            ;

        auto decrease_indent =
            eps[--get_indent][ std::cout << phx::val("\n============================") << get_indent << std::endl ]
            ;

        auto restore_indent =
            eps[get_indent = _a]
            ;

        yaml_start =
                set_current_line
            >>  (   flow_compound
                |   blocks
                )
            ;

        flow_in_block =
                compact_block
            |   indented_block
            |   flow_compound
            |   flow_scalar_ns                        //  Don't allow scalars to skip spaces
            |   (omit[blank_eol]                      //  If all else fails, then null_t
                  >> attr(ast::null_t()))
            ;

        indented_block %=
                increase_indent
            >>  (blocks | !decrease_indent)
            >>  decrease_indent
            ;

        compact_block =
                !eol
            >>  blocks
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

        indent =
            *blank >> raw[eps] [update_indent(get_current_line, _1, get_indent, _pass)]
            ;

        skip_indent =
            *blank >> raw[eps] [check_indent(get_current_line, _1, get_indent, _pass)]
            ;

        auto start_indent =
            indent[ std::cout << phx::val("\n============================") << get_indent << std::endl  ]
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
            (indented_block)
            (compact_block)
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
