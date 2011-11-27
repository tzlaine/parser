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
                    // $$$ JDG $$$ Fixme: this is a hack.
                    switch (c)
                    {
                        case '\t':
                            out << "\\t";
                            break;
                        case '\n':
                            out << "\\n";
                            break;
                        default:
                            out << c;
                    }
                }
                out << "\"";
            }

            void operator()(double d) const
            {
                indent();
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
