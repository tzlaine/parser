
#ifndef BOOST_PARSER_DETAIL_WINDOWS_VS_OUTPUT_STREAM_HPP
#define BOOST_PARSER_DETAIL_WINDOWS_VS_OUTPUT_STREAM_HPP


#include <array>
#include <functional>
#include <iostream>
#include <sstream>

#include <Windows.h>

namespace boost { namespace parser {
    namespace impl { namespace windows {

        namespace {

            template<class CharT, class TraitsT = std::char_traits<CharT>>
            class basic_debugbuf : public std::basic_stringbuf<CharT, TraitsT>
            {
            public:
                virtual ~basic_debugbuf(void) { sync(); }

            protected:
                int sync()
                {
                    output_debug_string(this->str().c_str());
                    this->str(std::basic_string<CharT>()); // Clear the string buffer

                    return 0;
                }

                void output_debug_string(const CharT * text) {}
            };

            template<>
            inline void basic_debugbuf<char>::output_debug_string(const char * text)
            {
                // from example in MSDN
                // Save in-memory logging buffer to a log file on error.

                std::wstring dest;
                int convert_result = MultiByteToWideChar(CP_UTF8, 0, text, static_cast<int>(std::strlen(text)), nullptr, 0);
                if (convert_result <= 0) {
                    // cannot convert to wide-char -> use ANSI API
                    ::OutputDebugStringA(text);
                } else {
                    dest.resize(convert_result + 10);
                    convert_result = MultiByteToWideChar(
                        CP_UTF8,
                        0,
                        text,
                        static_cast<int>(std::strlen(text)),
                        dest.data(),
                        static_cast<int>(dest.size()));
                    if (convert_result <= 0) {
                        // cannot convert to wide-char -> use ANSI API
                        ::OutputDebugStringA(text);
                    } else {
                        ::OutputDebugStringW(dest.c_str());
                    }
                }
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
            ~basic_dostream() { delete this->rdbuf(); }
        };

        typedef basic_dostream<char> dostream;
        typedef basic_dostream<wchar_t> wdostream;

        inline dostream cout;
        inline wdostream wcout;

    }}

}}

/** A macro returning a stream writing to the VisualStudio Debug-Output window.
    To redirect trace-mode output to VisualStudio Debug-Output window use
    #define BOOST_PARSER_TRACE_OSTREAM BOOST_PARSER_VISUALSTUDIO_TRACE_OSTREAM

    Note: Therfore this <boost/parser/detail/windows/vs_output_stream.hpp> must 
          be included before <boost/parser.hpp>
*/

#define BOOST_PARSER_VISUALSTUDIO_TRACE_OSTREAM boost::parser::impl::windows::cout

#endif
