/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_FLOW_DEF_HPP)
#define OMD_PARSER_FLOW_DEF_HPP

#include "flow.hpp"

#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace omd { namespace parser
{
    template <typename Iterator>
    white_space<Iterator>::white_space()
      : white_space::base_type(start)
    {
        qi::char_type char_;
        qi::eol_type eol;
        qi::space_type space;

        start =
                space                           // tab/space/cr/lf
            |   '#' >> *(char_ - eol) >> eol    // comments
            ;
    }

    template <typename Iterator>
    flow<Iterator>::flow(
        int& indent,
        qi::symbols<char>& anchors,
        std::string const& source_file)
      : flow::base_type(flow_start),
        scalar_value(indent, anchors),
        error_handler(error_handler_t(source_file))
    {
        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::_val_type _val;
        qi::lit_type lit;
        qi::char_type char_;

        namespace phx = boost::phoenix;
        auto pb = phx::push_back(_val, _1);
        auto ins = phx::insert(_val, _1);
        phx::function<qi::symbols<char>::adder> add_anchor(anchors.add);

        flow_start =
                top_anchored_value
            |   object
            |   array
            ;

        top_anchored_value %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  flow_start
            ;

        flow_value =
                anchored_value
            |   scalar_value
            |   object
            |   array
            ;

        anchored_value %=
                '&'
            >>  (+~char_(" \n\r\t,{}[]")) [ add_anchor(_1) ]
            >>  flow_value
            ;

        object =
                '{'
            >   -(member_pair[ins] >> *(',' > member_pair[ins]))
            >   '}'
            ;

        member_pair =
                scalar_value.string_value
            >>  ':'
            >>  flow_value
            ;

        array =
                '['
            >   -(flow_value[pb] >> *(',' > flow_value[pb]))
            >   ']'
            ;

        BOOST_SPIRIT_DEBUG_NODES(
            (flow_start)
            (flow_value)
            (object)
            (member_pair)
            (array)
            (anchored_value)
            (top_anchored_value)
        );

        qi::on_error<qi::fail>(flow_start, error_handler(_1, _2, _3, _4));
    }
}}

#endif
