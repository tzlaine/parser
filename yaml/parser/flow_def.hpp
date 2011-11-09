/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 */

#if !defined(OMD_PARSER_FLOW_DEF_HPP)
#define OMD_PARSER_FLOW_DEF_HPP

#include "flow.hpp"

#include <boost/fusion/adapted/std_pair.hpp>

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
    flow<Iterator>::flow(std::string const& source_file)
      : flow::base_type(value),
        error_handler(error_handler_t(source_file))
    {
        value =
             scalar_value
           | object
           | array
           ;

        object =
              '{'
           >  -(member_pair >> *(',' > member_pair))
           >  '}'
           ;

        member_pair =
              scalar_value
           >> ':'
           >> value
           ;

        array =
              '['
           >  -(value >> *(',' > value))
           >  ']'
           ;

        BOOST_SPIRIT_DEBUG_NODES(
            (value)
            (object)
            (member_pair)
            (array)
        );

        qi::_1_type _1;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;
        qi::on_error<qi::fail>(value, error_handler(_1, _2, _3, _4));
    }
}}

#endif
