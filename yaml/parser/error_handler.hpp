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
          : source_file(source_file)
        {
        }

        void operator()(
            Iterator first, Iterator last,
            Iterator err_pos, boost::spirit::info const& what) const
        {
            Iterator::position_t pos = err_pos.get_position();
            int line = pos.line;

            if (source_file != "")
                std::cerr << "In file " << source_file << ", ";
            else
                std::cerr << "In ";

            if (line != -1)
                std::cerr << "line " << line << ':' << std::endl;

            std::cerr << "Error! Expecting " << what << " here:" << std::endl;

            int ci = 0;
            int col = 0;
            Iterator line_start = boost::spirit::get_line_start(first, err_pos);

            for (Iterator i = ++line_start; i != last; ++i, ++ci)
            {
                typename Iterator::value_type c = *i;
                if (i == err_pos)
                    col = ci;
                if (c == '\r' || c == '\n')
                    break;
                std::cerr << c;
            }

            std::cerr << std::endl;
            for (int i = 0; i != col; ++i)
                std::cerr << '_';

            std::cerr << "^_" << std::endl;
        }
    };
}}

#endif
