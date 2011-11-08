/**
 *   Copyright (C) 2010, 2011 Michael Caisse, Object Modeling Designs
 *   consultomd.com
 *
 */
#ifndef OMD_JSON_VALUE_HPP
#define OMD_JSON_VALUE_HPP

#include <string>
#include <map>
#include <vector>
#include <boost/variant.hpp>


namespace omd{ namespace json
{

   // ------------------- json types --------------------
   //
   typedef std::string                         string_t;
   typedef double                              number_t;
   typedef bool                                bool_t;
   struct                                      null_t
   {
      // nulls always compare
      bool operator==(const null_t&) const{ return true;  }
      bool operator!=(const null_t&) const{ return false; }
   };

   typedef boost::make_recursive_variant<
      null_t,
      bool_t,
      string_t,     
      number_t,
      std::map<string_t,
               boost::recursive_variant_>,
      std::vector<boost::recursive_variant_>
      >::type                                  value_t;

   typedef std::map<std::string, value_t>      object_t;
   typedef std::vector<value_t>                array_t;

   // ---------------------------------------------------

}}
