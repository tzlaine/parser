/**
 *   Copyright (C) 2011, 2012 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *   Copyright (C) 2017 Zach Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See accompanying
 *   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef AST_VALUE_IMPL_HPP
#define AST_VALUE_IMPL_HPP

#include <yaml/ast.hpp>

#include <boost/spirit/include/qi.hpp>  // boost::spirit::to_utf8
#include <boost/functional/hash.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>

#include <algorithm>
#include <map>


namespace yaml { namespace ast {

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

            int operator()(properties_node_t const& pn) const
            {
                return boost::apply_visitor(*this, pn.second.get());
            }

            int operator()(alias_t const& alias) const
            {
                BOOST_ASSERT(alias.second); // This alias is unlinked! If this assertion
                                            // fired, then you are trying to traverse an
                                            // unlinked yaml object.
                return boost::apply_visitor(*this, alias.second->get());
            }

            int operator()(map_t const& obj) const
            {
                int max_depth = 0;
                for (map_element_t const& val : obj)
                {
                    int element_depth = boost::apply_visitor(*this, val.second.get());
                    max_depth = (std::max)(max_depth, element_depth);
                }
                return max_depth + 1;
            }

            int operator()(seq_t const& arr) const
            {
                int max_depth = 0;
                for (value_t const& val : arr)
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

        inline int depth(seq_t const& arr)
        {
            depth_f f;
            return f(arr);
        }

        inline int depth(map_t const& obj)
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

            yaml_printer(std::ostream& out_)
                : out(out_), current_indent(-spaces), is_key(false), level(-1)
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

            void operator()(properties_node_t const& pn) const
            {
                if (pn.first.anchor_ != "" && !expand_aliases)
                    out << '&' << pn.first.anchor_ << ' ';
                boost::apply_visitor(*this, pn.second.get());
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

            void print_json_object(map_t const& obj) const
            {
                out << '{';
                bool first = true;

                for (map_element_t const& val : obj)
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

            void print_yaml_object(map_t const& obj) const
            {
                current_indent += spaces;
                bool first = true;

                for (map_element_t const& val : obj)
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

            void operator()(map_t const& obj) const
            {
                ++level;
                if (dont_print_inline(obj))
                    print_yaml_object(obj);
                else
                    print_json_object(obj);
                --level;
            }

            void print_json_array(seq_t const& arr) const
            {
                out << '[';
                bool first = true;

                for (value_t const& val : arr)
                {
                    if (first)
                        first = false;
                    else
                        out << ", ";
                    boost::apply_visitor(*this, val.get());
                }

                out << ']';
            }

            void print_yaml_array(seq_t const& arr) const
            {
                bool first = true;

                for (value_t const& val : arr)
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

            void operator()(seq_t const& arr) const
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

        struct value_equal
        {
            typedef bool result_type;

            template <typename A, typename B>
            bool operator()(A const& a, B const& b) const
            {
                return false;
            }

            template <typename T>
            bool operator()(T const& a, T const& b) const
            {
                return a == b;
            }

            bool operator()(properties_node_t const& a, properties_node_t const& b) const
            {
                return a.second == b.second;
            }

            bool operator()(alias_t const& a, alias_t const& b) const
            {
                // aliases are compared using their referents
                return a.second == b.second;
            }

            bool operator()(map_t const& a, map_t const& b)
            {
                if (a.size() != b.size())
                    return false;
                map_t::const_iterator ii = b.begin();
                for (map_t::const_iterator i = a.begin(); i != a.end(); ++i)
                {
                    if (*i != *ii++)
                        return false;
                }
                return true;
            }

            bool operator()(seq_t const& a, seq_t const& b)
            {
                if (a.size() != b.size())
                    return false;
                seq_t::const_iterator ii = b.begin();
                for (seq_t::const_iterator i = a.begin(); i != a.end(); ++i)
                {
                    if (*i != *ii++)
                        return false;
                }
                return true;
            }
        };

        struct spirit_variant_hasher
            : boost::static_visitor<std::size_t>
        {
            template <typename T>
            std::size_t operator() (T const & val) const
            {
                boost::hash<T> hasher;
                return hasher(val);
            }

            std::size_t operator()(seq_t const & seq) const
            {
                std::size_t seed = 0;
                for (auto const & e : seq) {
                    boost::hash_combine(seed, (*this)(e));
                }
                return seed;
            }

            std::size_t operator()(map_t const & map) const
            {
                std::size_t seed = 0;
                for (auto const & e : map) {
                    boost::hash_combine(seed, (*this)(e.first));
                    boost::hash_combine(seed, (*this)(e.second));
                }
                return seed;
            }

            std::size_t operator()(null_t const &) const
            {
                boost::hash<int> hasher;
                return hasher(0);
            }
        };
    }

    inline std::size_t hash_value (properties_t const & p)
    {
        boost::hash<std::string> hasher;
        std::size_t seed = hasher(p.tag_);
        boost::hash_combine(seed, p.anchor_);
        return seed;
    }

    inline std::size_t hash_value (value_t const & val)
    {
        std::size_t seed = boost::apply_visitor(detail::spirit_variant_hasher(), val);
        boost::hash_combine(seed, val.get().which());
        return seed;
    }

    inline bool operator==(value_t const& a, value_t const& b)
    {
        return boost::apply_visitor(detail::value_equal(), a.get(), b.get());
    }

    inline bool operator!=(value_t const& a, value_t const& b)
    {
        return !(a == b);
    }

    struct map_t::index_t
    {
        std::unordered_map<value_t, element_iterator_t, boost::hash<value_t>> map_;
    };

    inline map_t::map_t ()
        : index_ (new index_t)
    {}

    inline map_t::map_t (map_t const & o)
        : elements_ (o.elements_)
        , index_ (o.index_ ? new index_t(*o.index_.get()) : nullptr)
    {}

    inline map_t & map_t::operator= (map_t const & rhs)
    {
        map_t tmp(rhs);
        *this = std::move(tmp);
        return *this;
    }

    inline std::pair<map_t::iterator, bool> map_t::insert (map_element_t const & e)
    {
        auto const index_it = index_->map_.find(e.first);
        if (index_it == index_->map_.end()) {
            iterator const it = elements_.insert(elements_.end(), e);
            index_->map_[e.first] = it;
            return std::pair<map_t::iterator, bool>{it, true};
        } else {
            return std::pair<map_t::iterator, bool>{index_it->second, false};
        }
    }

    inline map_t::iterator map_t::insert (const_iterator at, map_element_t const & e)
    {
        BOOST_ASSERT(index_->map_.find(e.first) == index_->map_.end());
        iterator const it = elements_.insert(at, e);
        index_->map_[e.first] = it;
        return it;
    }

    template <int Spaces, bool ExpandAliases>
    inline std::ostream& print_yaml(std::ostream& out, value_t const& val)
    {
        detail::yaml_printer<Spaces, ExpandAliases> f(out);
        boost::apply_visitor(f, val.get());
        return out;
    }

} }

#endif
