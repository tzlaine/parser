/**
 *   Copyright (C) 2010, 2011 Object Modeling Designs
 *   Copyright (c) 2010 Joel de Guzman
 */

#if !defined(OMD_COMMON_ERROR_HANDLER_HPP)
#define OMD_COMMON_ERROR_HANDLER_HPP

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>
#include <string>
#include <iostream>

namespace omd { namespace parser
{
    template <typename Iterator>
    struct error_handler
    {
        template <typename, typename, typename, typename>
        struct result { typedef void type; };

        std::string source_file;
        error_handler(std::string const& source_file = "")
          : source_file(source_file) {}

        void operator()(
            Iterator first, Iterator last,
            Iterator err_pos, boost::spirit::info const& what) const
        {
            Iterator eol = err_pos;
            int line = boost::spirit::get_line(err_pos);

            if (source_file != "")
                std::cerr << source_file;

            if (line != -1)
                std::cerr << '(' << line << ')';

            std::cerr << " : Error! Expecting "  << what;

            std::cerr << " got:\"";
            for (Iterator i = err_pos; i != last; ++i)
            {
                Iterator::value_type c = *i;
                if (c == '\r' || c == '\n')
                    break;
                std::cerr << c;
            }

            std::cerr << "\"" << std::endl;
        }
    };
}}

#endif
