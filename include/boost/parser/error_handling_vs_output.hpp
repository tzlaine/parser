#ifndef BOOST_PARSER_ERROR_HANDLING_VS_OUTPUT_HPP
#define BOOST_PARSER_ERROR_HANDLING_VS_OUTPUT_HPP

#include <boost/parser/error_handling.hpp>
#include <boost/parser/detail/printing.hpp>

#include <boost/parser/detail/text/algorithm.hpp>
#include <boost/parser/detail/text/transcode_iterator.hpp>

#include <array>
#include <functional>
#include <iostream>
#include <sstream>

#include <Windows.h>

namespace boost { namespace parser {
    namespace impl { namespace dbg {

        namespace {

            template<class CharT, class TraitsT = std::char_traits<CharT>>
            class basic_debugbuf : public std::basic_stringbuf<CharT, TraitsT>
            {
            public:
                virtual ~basic_debugbuf(void) { sync(); }

            protected:
                int sync()
                {
                    output_debug_string(str().c_str());
                    str(std::basic_string<CharT>()); // Clear the string buffer

                    return 0;
                }

                void output_debug_string(const CharT * text) {}
            };

            template<>
            inline void basic_debugbuf<char>::output_debug_string(const char * text)
            {
                ::OutputDebugStringA(text);
            }

            template<>
            inline void basic_debugbuf<wchar_t>::output_debug_string(const wchar_t * text)
            {
                ::OutputDebugStringW(text);
            }
        }


        template<class CharT, class TraitsT = std::char_traits<CharT>>
        class basic_dostream : public std::basic_ostream<CharT, TraitsT>
        {
        public:
            basic_dostream() :
                std::basic_ostream<CharT, TraitsT>(
                    new basic_debugbuf<CharT, TraitsT>())
            {}
            ~basic_dostream() { delete rdbuf(); }
        };

        typedef basic_dostream<char> dostream;
        typedef basic_dostream<wchar_t> wdostream;

        inline dostream cout;
        inline wdostream wcout;

    }}


    /** An error handler that allows users to supply callbacks to handle the
        reporting of warnings and errors.  The reporting of errors and/or
        warnings can be suppressed by supplying one or both
        default-constructed callbacks. */
    struct vs_output_error_handler : stream_error_handler
    {
        vs_output_error_handler() 
        : stream_error_handler{"", impl::dbg::dostream, impl::dbg::dostream}
        {}
    };


}}

#endif
