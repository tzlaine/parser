#ifndef BOOST_PARSER_ERROR_HANDLING_VS_OUTPUT_HPP
#define BOOST_PARSER_ERROR_HANDLING_VS_OUTPUT_HPP

#include <boost/parser/error_handling.hpp>
#include <boost/parser/detail/printing.hpp>

#include <boost/parser/detail/text/algorithm.hpp>
#include <boost/parser/detail/text/transcode_iterator.hpp>
#include <boost/parser/detail/windows/vs_output_stream.hpp>

#include <array>
#include <functional>
#include <iostream>
#include <sstream>

#include <Windows.h>

namespace boost { namespace parser {

    /** An error handler that allows users to supply callbacks to handle the
        reporting of warnings and errors.  The reporting of errors and/or
        warnings can be suppressed by supplying one or both
        default-constructed callbacks. */
    struct vs_output_error_handler : stream_error_handler
    {
        vs_output_error_handler(std::string_view filename) 
        : stream_error_handler{filename, impl::windows::cout, impl::windows::cout}
        {}

        vs_output_error_handler(std::wstring_view filename) :
            stream_error_handler{filename, impl::windows::cout, impl::windows::cout}
        {}
    };


}}

#endif
