/**
 *   Copyright (C) 2010, 2011 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *
 */
#ifndef OMD_AST_VALUE_IMPL_HPP
#define OMD_AST_VALUE_IMPL_HPP

#include "../ast.hpp"
#include <algorithm>
#include <boost/foreach.hpp>

namespace omd { namespace ast
{
    namespace detail
    {
        struct value_equal
        {
            typedef bool result_type;

            template <typename A, typename B>
            bool operator()(A const& a, B const& b) const
            {
                return false; // comparing different types returns false
            }

            template <typename T>
            bool operator()(T const& a, T const& b) const
            {
                return a == b;
            }

            bool operator()(object_t const& a, object_t const& b) const
            {
                if (a.size() != b.size())
                    return false;
                object_t::const_iterator ii = b.begin();
                for (object_t::const_iterator i = a.begin(); i != a.end(); ++i)
                {
                    if (*i != *ii++)
                        return false;
                }
                return true;
            }

            bool operator()(array_t const& a, array_t const& b) const
            {
                if (a.size() != b.size())
                    return false;
                array_t::const_iterator ii = b.begin();
                for (array_t::const_iterator i = a.begin(); i != a.end(); ++i)
                {
                    if (*i != *ii++)
                        return false;
                }
                return true;
            }
        };
    }

    inline bool operator==(value_t const& a, value_t const& b)
    {
        return boost::apply_visitor(detail::value_equal(), a.get(), b.get());
    }

    inline bool operator!=(value_t const& a, value_t const& b)
    {
        return !(a == b);
    }

    namespace detail
    {
        struct value_compare
        {
            typedef bool result_type;

            template <typename A, typename B>
            bool operator()(A const& a, B const& b) const
            {
                BOOST_ASSERT(false); // this should not happen. We cannot compare different types
                return false;
            }

            template <typename T>
            bool operator()(T const& a, T const& b) const
            {
                return a < b;
            }

            bool operator()(object_t const& a, object_t const& b) const
            {
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
            }

            bool operator()(array_t const& a, array_t const& b) const
            {
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
            }
        };
    }

    inline bool operator<(value_t const& a, value_t const& b)
    {
        return boost::apply_visitor(detail::value_compare(), a.get(), b.get());
    }

    namespace detail
    {
        struct json_printer
        {
            typedef void result_type;
            static int const spaces = 2;

            std::ostream& out;
            mutable int indent_spaces;

            json_printer(std::ostream& out)
                : out(out), indent_spaces(0) {}

            void operator()(null_t) const
            {
                indent();
                out << "null";
            }

            void operator()(bool b) const
            {
                indent();
                out << (b ? "true" : "false");
            }

            void operator()(std::string const& utf) const
            {
                indent();
                out << '"';
                BOOST_FOREACH(char c, utf)
                {
                    out << c;
                }
                out << "\"";
            }

            template <typename T>
            void operator()(T const& val) const
            {
                indent();
                out << val;
            }

            void operator()(object_t const& obj) const
            {
                indent();
                out << '{';
                indent_spaces += spaces;
                typedef std::pair<value_t, value_t> pair;
                bool first = true;

                BOOST_FOREACH(pair const& val, obj)
                {
                    if (first)
                    {
                        first = false;
                        out << std::endl;
                    }
                    else
                    {
                        out << ",\n";
                    }
                    boost::apply_visitor(*this, val.first.get());
                    out << " :\n";
                    indent_spaces += spaces;
                    boost::apply_visitor(*this, val.second.get());
                    indent_spaces -= spaces;
                }

                indent_spaces -= spaces;
                out << std::endl;
                indent();
                out << '}';
            }

            void operator()(array_t const& arr) const
            {
                indent();
                out << '[';
                indent_spaces += spaces;
                bool first = true;

                BOOST_FOREACH(value_t const& val, arr)
                {
                    if (first)
                    {
                        first = false;
                        out << std::endl;
                    }
                    else
                    {
                        out << ",\n";
                    }
                    boost::apply_visitor(*this, val.get());
                }

                indent_spaces -= spaces;
                out << std::endl;
                indent();
                out << ']';
            }

            void indent() const
            {
                for (int i = 0; i != indent_spaces; ++i)
                    out << ' ';
            }
        };
    }

    inline std::ostream& print_json(std::ostream& out, value_t const& val)
    {
        detail::json_printer f(out);
        boost::apply_visitor(f, val.get());
        return out;
    }
}}

#endif
