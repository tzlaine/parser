/**
 *   Copyright (C) 2010, 2011 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *
 */
#ifndef OMD_AST_VALUE_IMPL_HPP
#define OMD_AST_VALUE_IMPL_HPP

#include "../ast.hpp"
#include <algorithm>

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
                BOOST_ASSERT(false); // this should not happen. We cannot compare different types
                return false;
            }

            template <typename T>
            bool operator()(T const& a, T const& b) const
            {
                return a == b;
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

            bool operator()(object_t const& a, object_t const& b)
            {
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
            }

            bool operator()(array_t const& a, array_t const& b)
            {
                return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
            }
        };
      }

    inline bool operator<(value_t const& a, value_t const& b)
    {
        return boost::apply_visitor(detail::value_compare(), a.get(), b.get());
    }
}}

#endif
