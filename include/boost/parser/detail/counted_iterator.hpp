#ifndef BOOST_PARSER_DETAIL_COUNTED_ITERATOR_HPP
#define BOOST_PARSER_DETAIL_COUNTED_ITERATOR_HPP

#include <boost/parser/detail/stl_interfaces/iterator_interface.hpp>


namespace boost::parser::detail {

    template<typename I, typename S>
    struct counted_iterator
        : stl_interfaces::iterator_interface<
              counted_iterator<I, S>,
              std::forward_iterator_tag,
              std::remove_cv_t<
                  std::remove_reference_t<decltype(*std::declval<I>())>>,
              decltype(*std::declval<I>())>
    {
        constexpr counted_iterator() = default;
        constexpr explicit counted_iterator(I & it) : it_(it) {}

        constexpr size_t count() const { return count_; }
        constexpr bool operator==(S last) const { return it_ == last; }
        constexpr I base() const { return it_; }

        constexpr counted_iterator & operator++()
        {
            ++it_;
            ++count_;
            return this;
        }

    private:
        friend stl_interfaces::access;

        constexpr I & base_reference() { return it_; }
        constexpr I base_reference() const { return it_; }

        I it_ = I();
        size_t count_ = 0;
    };
    //
}

#endif
