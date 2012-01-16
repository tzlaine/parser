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
#include <boost/math/special_functions/fpclassify.hpp>

namespace omd { namespace ast
{
    namespace detail
    {
        struct depth_f
        {
            typedef int result_type;

            template <typename T>
            int operator()(T const& val) const
            {
                return 0;
            }

            int operator()(object_t const& obj) const
            {
                typedef std::pair<value_t, value_t> pair;
                int max_depth = 0;
                BOOST_FOREACH(pair const& val, obj)
                {
                    int element_depth = boost::apply_visitor(*this, val.second.get());
                    max_depth = (std::max)(max_depth, element_depth);
                }
                return max_depth + 1;
            }

            int operator()(array_t const& arr) const
            {
                int max_depth = 0;
                BOOST_FOREACH(value_t const& val, arr)
                {
                    int element_depth = boost::apply_visitor(*this, val.get());
                    max_depth = (std::max)(max_depth, element_depth);
                }
                return max_depth + 1;
            }
        };

        inline int depth(value_t const& val)
        {
            depth_f f;
            return boost::apply_visitor(f, val.get());
        }

        inline int depth(array_t const& arr)
        {
            depth_f f;
            return f(arr);
        }

        inline int depth(object_t const& obj)
        {
            depth_f f;
            return f(obj);
        }

        struct yaml_printer
        {
            typedef void result_type;
            static int const spaces = 2;
            static int const primary_level = 0;

            std::ostream& out;
            mutable int current_indent;
            mutable bool is_key;
            mutable int level;

            yaml_printer(std::ostream& out)
                : out(out), current_indent(-spaces), is_key(false), level(-1)
            {
                BOOST_ASSERT(spaces >= 2);
            }

            void operator()(null_t) const
            {
                out << "null";
            }

            void operator()(bool b) const
            {
                out << (b ? "true" : "false");
            }

            void operator()(std::string const& utf) const
            {
                if (!is_key)
                    out << '"';
                BOOST_FOREACH(char c, utf)
                {
                    // $$$ JDG $$$ Fixme: Add more escapes (e.g. unicode, unprintables, etc)
                    switch (c)
                    {
                        case '\t':
                            out << "\\t";
                            break;
                        case '\n':
                            out << "\\n";
                            break;
                        case '\r':
                            out << "\\r";
                            break;
                        case '\\':
                            out << "\\\\";
                            break;
                        case '"':
                            out << "\\\"";
                            break;
                        default:
                            out << c;
                    }
                }

                if (!is_key)
                    out << "\"";
            }

            void operator()(double d) const
            {
                if (boost::math::isnan(d))
                {
                    out << ".NaN";
                    return;
                }
                if (boost::math::isinf(d))
                {
                    if (d < 0.0)
                        out << '-';
                    out << ".inf";
                    return;
                }
                out << d;
            }

            template <typename T>
            void operator()(T const& val) const
            {
                out << val;
            }

            void print_json_object(object_t const& obj) const
            {
                out << '{';
                typedef std::pair<value_t, value_t> pair;
                bool first = true;

                BOOST_FOREACH(pair const& val, obj)
                {
                    if (first)
                    {
                        first = false;
                    }
                    else
                    {
                        out << ", ";
                    }
                    is_key = true;
                    boost::apply_visitor(*this, val.first.get());
                    is_key = false;
                    out << " : ";
                    boost::apply_visitor(*this, val.second.get());
                }

                out << '}';
            }

            template <typename T>
            bool dont_print_inline(T const& val) const
            {
                return (level <= primary_level) || (depth(val) > 1);
            }

            void print_yaml_object(object_t const& obj) const
            {
                typedef std::pair<value_t, value_t> pair;
                current_indent += spaces;
                bool first = true;

                BOOST_FOREACH(pair const& val, obj)
                {
                    if (first)
                    {
                        first = false;
                    }
                    else
                    {
                        out << std::endl;
                        indent(current_indent);
                    }

                    is_key = true;
                    boost::apply_visitor(*this, val.first.get());
                    is_key = false;

                    if (depth(val.second) > 1)
                    {
                        out << " :\n";
                        indent(current_indent + spaces);
                        boost::apply_visitor(*this, val.second.get());
                    }
                    else
                    {
                        out << " : ";
                        boost::apply_visitor(*this, val.second.get());
                    }
                }
                current_indent -= spaces;
            }

            void operator()(object_t const& obj) const
            {
                ++level;
                if (dont_print_inline(obj))
                    print_yaml_object(obj);
                else
                    print_json_object(obj);
                --level;
            }

            void print_json_array(array_t const& arr) const
            {
                out << '[';
                bool first = true;

                BOOST_FOREACH(value_t const& val, arr)
                {
                    if (first)
                        first = false;
                    else
                        out << ", ";
                    boost::apply_visitor(*this, val.get());
                }

                out << ']';
            }

            void print_yaml_array(array_t const& arr) const
            {
                bool first = true;

                BOOST_FOREACH(value_t const& val, arr)
                {
                    if (first)
                    {
                        first = false;
                        indent(spaces - 2);
                        out << "- "; // print the indicator
                        current_indent += spaces;
                    }
                    else
                    {
                        out << std::endl;
                        indent(current_indent + spaces - 2);
                        out << "- "; // print the indicator
                    }

                    boost::apply_visitor(*this, val.get());
                }

                current_indent -= spaces;
            }

            void operator()(array_t const& arr) const
            {
                ++level;
                if (dont_print_inline(arr))
                    print_yaml_array(arr);
                else
                    print_json_array(arr);
                --level;
            }

            void indent(int indent_spaces) const
            {
                for (int i = 0; i < indent_spaces; ++i)
                    out << ' ';
            }
        };
    }

    inline std::ostream& print_yaml(std::ostream& out, value_t const& val)
    {
        detail::yaml_printer f(out);
        boost::apply_visitor(f, val.get());
        return out;
    }
}}

#endif
