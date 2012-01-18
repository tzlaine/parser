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
#include <boost/regex/pending/unicode_iterator.hpp>

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

            int operator()(anchored_object_t const& anchored) const
            {
                return boost::apply_visitor(*this, anchored.second.get());
            }

            int operator()(alias_t const& alias) const
            {
                BOOST_ASSERT(alias.second); // This alias is unlinked! If this assertion
                                            // fired, then you are trying to traverse an
                                            // unlinked yaml object.
                return boost::apply_visitor(*this, alias.second->get());
            }

            int operator()(object_t const& obj) const
            {
                int max_depth = 0;
                BOOST_FOREACH(object_element_t const& val, obj)
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

        template <int Spaces, bool ExpandAliases>
        struct yaml_printer
        {
            typedef void result_type;
            static int const spaces = Spaces;
            static int const primary_level = 0;
            static bool const expand_aliases = ExpandAliases;

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

                typedef ::boost::uint32_t ucs4_char;
                typedef boost::u8_to_u32_iterator<std::string::const_iterator> iter_t;
                iter_t f = utf.begin();
                iter_t l = utf.end();

                for (iter_t i = f; i != l; ++i)
                {
                    ucs4_char c = *i;
                    switch (c)
                    {
                        case 0:       out << "\\0"; break;
                        case 0x7:     out << "\\a"; break;
                        case 0x8:     out << "\\b"; break;
                        case 0x9:     out << "\\t"; break;
                        case 0xA:     out << "\\n"; break;
                        case 0xB:     out << "\\v"; break;
                        case 0xC:     out << "\\f"; break;
                        case 0xD:     out << "\\r"; break;
                        case 0x1B:    out << "\\e"; break;
                        case '"':     out << "\\\""; break;
                        case '\\':    out << "\\\\"; break;
                        case 0xA0:    out << "\\_"; break;
                        case 0x85:    out << "\\N"; break;
                        case 0x2028:  out << "\\L"; break;
                        case 0x2029:  out << "\\P"; break;
                        default:      out << boost::spirit::to_utf8(c);
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

            void operator()(anchored_object_t const& anchored) const
            {
                if (!expand_aliases)
                    out << '&' << anchored.first << ' ';
                boost::apply_visitor(*this, anchored.second.get());
            }

            void operator()(alias_t const& alias) const
            {
                if (!expand_aliases)
                {
                    out << '*' << alias.first << ' ';
                }
                else
                {
                    BOOST_ASSERT(alias.second); // This alias is unlinked! If this assertion
                                                // fired, then you are trying to traverse an
                                                // unlinked yaml object.
                    boost::apply_visitor(*this, alias.second->get());
                }
            }

            template <typename T>
            void operator()(T const& val) const
            {
                out << val;
            }

            void print_json_object(object_t const& obj) const
            {
                out << '{';
                bool first = true;

                BOOST_FOREACH(object_element_t const& val, obj)
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
                current_indent += spaces;
                bool first = true;

                BOOST_FOREACH(object_element_t const& val, obj)
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

        struct yaml_linker
        {
            typedef void result_type;
            std::map<std::string, value_t*> symbol_table;
            int phase;

            yaml_linker() : phase(1) {}

            template <typename T>
            void operator()(T& val)
            {
            }

            void operator()(anchored_object_t& anchored)
            {
                if (phase == 2)
                    return;

                // Note: it is possuble to re-define an alias as per yaml specs.
                symbol_table[anchored.first] = &anchored.second;
            }

            void operator()(alias_t& alias)
            {
                if (phase == 1)
                    return;

                std::map<std::string, value_t*>::iterator
                    iter = symbol_table.find(alias.first);

                // This cannot happen. The parser makes sure that there is an anchor
                // for each alias in the yaml document.
                BOOST_ASSERT(iter != symbol_table.end());
                alias.second = iter->second;
            }

            void operator()(alias_t const& alias)
            {
                // Don't worry, this (const_cast) is safe. We are just going to link
                // the key. The key itself will remain stable for the map's purpose.
                (*this)(const_cast<alias_t&>(alias));
            }

            void operator()(object_t& obj)
            {
                typedef std::pair<value_t const, value_t> pair;
                BOOST_FOREACH(pair& val, obj)
                {
                    boost::apply_visitor(*this, val.first.get());
                    boost::apply_visitor(*this, val.second.get());
                }
            }

            void operator()(array_t& arr)
            {
                BOOST_FOREACH(value_t& val, arr)
                {
                    boost::apply_visitor(*this, val.get());
                }
            }
        };

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

            bool operator()(anchored_object_t const& a, anchored_object_t const& b) const
            {
                // anchors are compared using their names (IDs)
                return a.first < b.first;
            }

            bool operator()(anchored_object_t const& a, string_t const& b) const
            {
                // anchors are compared using their names (IDs)
                return a.first < b;
            }

            bool operator()(string_t const& a, anchored_object_t const& b) const
            {
                // anchors are compared using their names (IDs)
                return a < b.first;
            }

            bool operator()(alias_t const& a, alias_t const& b) const
            {
                // aliases are compared using their names (IDs)
                return a.first < b.first;
            }

            bool operator()(alias_t const& a, string_t const& b) const
            {
                // aliases are compared using their names (IDs)
                return a.first < b;
            }

            bool operator()(string_t const& a, alias_t const& b) const
            {
                // aliases are compared using their names (IDs)
                return a < b.first;
            }

            bool operator()(anchored_object_t const& a, alias_t const& b) const
            {
                // anchors and aliases are compared using their names (IDs)
                return a.first < b.first;
            }

            bool operator()(alias_t const& a, anchored_object_t const& b) const
            {
                // anchors and aliases are compared using their names (IDs)
                return a.first < b.first;
            }

            bool operator()(object_t const& a, object_t const& b)
            {
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
            }

            bool operator()(array_t const& a, array_t const& b)
            {
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
            }
        };

        struct value_equal
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
                return a == b;
            }

            bool operator()(anchored_object_t const& a, anchored_object_t const& b) const
            {
                // anchors are compared using their names (IDs)
                return a.first == b.first;
            }

            bool operator()(anchored_object_t const& a, string_t const& b) const
            {
                // anchors are compared using their names (IDs)
                return a.first == b;
            }

            bool operator()(string_t const& a, anchored_object_t const& b) const
            {
                // anchors are compared using their names (IDs)
                return a == b.first;
            }

            bool operator()(alias_t const& a, alias_t const& b) const
            {
                // aliases are compared using their names (IDs)
                return a.first == b.first;
            }

            bool operator()(alias_t const& a, string_t const& b) const
            {
                // aliases are compared using their names (IDs)
                return a.first == b;
            }

            bool operator()(string_t const& a, alias_t const& b) const
            {
                // aliases are compared using their names (IDs)
                return a == b.first;
            }

            bool operator()(anchored_object_t const& a, alias_t const& b) const
            {
                // anchors and aliases are compared using their names (IDs)
                return a.first == b.first;
            }

            bool operator()(alias_t const& a, anchored_object_t const& b) const
            {
                // anchors and aliases are compared using their names (IDs)
                return a.first == b.first;
            }

            bool operator()(object_t const& a, object_t const& b)
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

            bool operator()(array_t const& a, array_t const& b)
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

    inline bool operator<(value_t const& a, value_t const& b)
    {
        return boost::apply_visitor(detail::value_compare(), a.get(), b.get());
    }

    inline void link_yaml(value_t& val)
    {
        detail::yaml_linker f;

        // phase 1: collect all anchors
        boost::apply_visitor(f, val.get());

        // phase 2: link all aliases
        f.phase = 2;
        boost::apply_visitor(f, val.get());
    }

    template <int Spaces, bool ExpandAliases>
    inline std::ostream& print_yaml(std::ostream& out, value_t const& val)
    {
        detail::yaml_printer<Spaces, ExpandAliases> f(out);
        boost::apply_visitor(f, val.get());
        return out;
    }
}}

#endif
