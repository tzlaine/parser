/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_YAML_DEF_HPP)
#define OMD_PARSER_YAML_DEF_HPP

#include "yaml.hpp"
#include <algorithm>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

// For debugging:
#if defined(BOOST_SPIRIT_DEBUG)
#define PRINT_INDENT \
[ std::cerr << phx::val("\n============================") << get_indent << std::endl ]
#else
#define PRINT_INDENT
#endif

namespace omd { namespace parser
{
    namespace detail
    {
        struct update_indent
        {
            template <typename Range, typename Size, typename Fail>
            struct result { typedef void type; };

            template <typename Range>
            void operator()(
                Range const& rng,                   //  <-- where we are now
                int& current_indent,                //  <-- the current indent position
                bool& pass                          //  <-- set to false to fail parsing
            ) const
            {
                int pos = rng.begin().get_position().column;
                if (pos >= current_indent)
                    current_indent = pos;
                else
                    pass = false;
            }
        };

        struct check_indent
        {
            template <typename Range, typename Size, typename Fail>
            struct result { typedef void type; };

            template <typename Range>
            void operator()(
                Range const& rng,                   //  <-- where we are now
                int const& current_indent,          //  <-- the current indent position
                bool& pass                          //  <-- set to false to fail parsing
            ) const
            {
                int pos = rng.begin().get_position().column;
                if (pos < current_indent)
                    pass = false;
            }
        };
    }

    template <typename Iterator>
    yaml<Iterator>::yaml(std::string const& source_file)
      : yaml::base_type(stream),
        flow_g(current_indent),
        current_indent(-1),
        error_handler(error_handler_t(source_file))
    {
        namespace phx = boost::phoenix;
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

        qi::eol_type eol;
        qi::eoi_type eoi_;
        qi::blank_type blank;

        auto comment = '#' >> *(char_ - eol) >> eol;    // comments
        auto blank_eol = (*blank >> eol) | comment;     // empty until eol

        auto flow_string = skip(space)[flow_g.scalar_value.string_value.unicode_start];

        // no-skip version
        auto flow_scalar_ns = flow_g.scalar_value.scalar_value.alias();

        auto get_indent =
            phx::ref(current_indent)
            ;

        auto save_indent =
            eps[_a = get_indent] PRINT_INDENT
            ;

        auto zero_indent =
            eps[_a = get_indent, get_indent = 0] PRINT_INDENT
            ;

        auto increase_indent =
            eps[get_indent += 1] PRINT_INDENT
            ;

        auto decrease_indent =
            eps[get_indent -= 1] PRINT_INDENT
            ;

        auto restore_indent =
            eps[get_indent = _a] PRINT_INDENT
            ;

        indent =
            *blank >> raw[eps] [update_indent(_1, get_indent, _pass)]
            ;

        skip_indent =
            *blank >> raw[eps] [check_indent(_1, get_indent, _pass)]
            ;

        auto skip_exact_indent =
            repeat(get_indent-1)[blank]     // note: indent is one based!
            ;

        skip_indent_child =
            *blank >> raw[eps] [check_indent(_1, get_indent + 1, _pass)]
            ;

        auto eoi =
            omit[
                -('#' >> *(char_ - eoi_))   //  allow comments at the very end
            >>  eoi_
            ];

        stream =
            skip(space)[document > eoi]
            ;

        document =
                explicit_document
            |   implicit_document
            ;

        explicit_document =
            +(  (skip(space)["---"] >> blank_eol)
            >   implicit_document
            >   (skip(space)["..."] >> blank_eol)
            )
            ;

        implicit_document =
                flow_compound
            |   blocks
            ;

        //  Allow newlines before scalars as long as they are properly indented
        auto scalar_in_block =
                omit[-(+blank_eol >> skip_indent_child)]
            >>  flow_scalar_ns
            ;

        // flow compound (arrays and maps) need no indentations. Set indent to
        // zero while parsing.
        flow_compound %=
                zero_indent
            >>  (skip(space)[flow_g.flow_start] | !restore_indent)
            >>  restore_indent
            ;

        block_node =
                compact_block
            |   indented_block
            |   flow_compound
            |   scalar_in_block
            |   (omit[blank_eol | eoi]                //  If all else fails, then null_t
                  >> attr(ast::null_t()))
            ;

        indented_block %=
                increase_indent
            >>  (blocks | !decrease_indent)
            >>  decrease_indent
            ;

        compact_block =
                !blank_eol
            >>  blocks
            ;

        auto block_main =
                block_literal
            |   block_seq
            |   explicit_block_map
            |   implicit_block_map
            ;

        blocks %=
                omit[*blank_eol]
            >>  save_indent
            >>  (block_main | !restore_indent)
            >>  restore_indent
            ;

        auto start_indent =
            omit[indent] PRINT_INDENT
            ;

        auto block_literal_first_line =
                *eol                [ _val += '\n' ]  //  blank lines (normalized)
            >>  start_indent                          //  Get first line indent
            >>  +(char_ - eol)      [ _val += _1 ]    //  Get the line
            ;

        auto block_literal_line =
                *eol                [ _val += '\n' ]  //  blank lines (normalized)
            >>  skip_exact_indent                     //  Indent get_indent spaces
            >>  +(char_ - eol)      [ _val += _1 ]    //  Get the line
            ;

        block_literal =
                start_indent >> '|' >> (blank | eol)  //  literal-style indicator.
            >>  block_literal_first_line
            >>  *block_literal_line
            ;

        auto block_seq_indicator =                    //  Lookahead and see if we have a
            &(start_indent >> '-' >> (blank | eol))   //  sequence indicator.
            ;

        block_seq =
                omit[block_seq_indicator]
            >>  +block_seq_entry                      //  Get the entries
            ;

        block_seq_entry =
                omit[*blank_eol]                      //  Ignore blank lines
            >>  omit[skip_indent]                     //  Indent get_indent spaces
            >>  omit['-' >> (blank | &eol)]           //  Get the sequence indicator '-'
            >>  block_node                            //  Get the entry
            ;

        auto implicit_block_map_indicator =           //  Lookahead and see if we have an
            &(  start_indent                          //  implicit map indicator.
            >>  flow_string
            >>  skip(space)[':']
            )
            ;

        implicit_block_map =
                omit[implicit_block_map_indicator]
            >>  +block_map_entry                      //  Get the entries
            ;

        auto explicit_block_map_indicator =           //  Lookahead and see if we have an
            &(start_indent >> '?' >> (blank | eol))   //  explicit map indicator.
            ;

        explicit_block_map =
                omit[explicit_block_map_indicator]
            >>  +block_map_entry                      //  Get the entries
            ;

        block_map_entry =
                explicit_block_map_entry
            |   implicit_block_map_entry
            ;

        implicit_block_map_entry =
                omit[*blank_eol]                      //  Ignore blank lines
            >>  omit[skip_indent]                     //  Indent get_indent spaces
            >>  flow_string                           //  Get the key
            >>  omit[skip(space)[':']]                //  Get the map indicator ':'
            >>  omit[*blank]                          //  Ignore blank spaces
            >>  block_node                            //  Get the value
            ;

        explicit_block_map_entry =
                omit[*blank_eol]                      //  Ignore blank lines
            >>  omit[skip_indent]                     //  Indent get_indent spaces
            >>  omit['?' >> (blank | &eol)]           //  Get the map-key indicator '?'
            >>  flow_string                           //  Get the key

            >>  omit[*blank_eol]                      //  Ignore blank lines
            >>  omit[skip_indent]                     //  Indent get_indent spaces
            >>  omit[':' >> (blank | &eol)]           //  Get the map-value indicator ':'
            >>  block_node                            //  Get the value
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (stream)
            (document)
            (explicit_document)
            (implicit_document)
            (block_node)
            (indented_block)
            (compact_block)
            (blocks)
            (block_literal)
            (block_seq)
            (block_seq_entry)
            (implicit_block_map)
            (implicit_block_map_entry)
            (block_map_entry)
            (explicit_block_map)
            (explicit_block_map_entry)
            (indent)
        );

        qi::on_error<qi::fail>(stream, error_handler(_1, _2, _3, _4));
    }
}}

#endif
