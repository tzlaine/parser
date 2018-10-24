#ifndef BOOST_YAML_EXCEPTION_HPP
#define BOOST_YAML_EXCEPTION_HPP

#include <stdexcept>


namespace boost { namespace yaml {

    template<typename Iter>
    struct excessive_nesting : std::runtime_error
    {
        excessive_nesting(Iter it) :
            runtime_error("excessive_nesting"),
            iter(it)
        {}
        Iter iter;
    };

}}

#endif
