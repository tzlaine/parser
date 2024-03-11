#ifndef BOOST_PARSER_DETAIL_MEMOS_HPP
#define BOOST_PARSER_DETAIL_MEMOS_HPP

#if __has_include(<boost/unordered/unordered_flat_map.hpp>)
#include <boost/unordered/unordered_flat_map.hpp>
#define BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP 1
#define BOOST_PARSER_MEMO_NS boost_unordered_flat_map
#else
#define BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP 0
#define BOOST_PARSER_MEMO_NS std_containers
#endif

#include <algorithm>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <variant> // monostate
#include <vector>


namespace boost::parser::detail {

    inline constexpr unsigned int next_pot(unsigned int i)
    {
        --i;
        i |= i >> 1;
        i |= i >> 2;
        i |= i >> 4;
        i |= i >> 8;
        i |= i >> 16;
        return ++i;
    }

    template<int Size, int Align>
    struct trivial_type
    {};
    template<typename T>
    using trivial_type_for = trivial_type<sizeof(T), alignof(T)>;

    template<typename T, int N>
    struct list_node
    {
        list_node() = default;
        list_node(list_node * n) : next(n) {}
        ~list_node()
        {
            for (int i = 0; i < size; ++i) {
                void * pos = buf + i * sizeof(T);
                T * obj = static_cast<T *>(pos);
                obj->~T();
            }
        }
        void * push() { return buf + size++ * sizeof(T); }
        void * get(int n) { return buf + n * sizeof(T); }
        alignas(T[N]) std::byte buf[sizeof(T[N])];
        list_node * next = nullptr;
        int size = 0;
    };

    template<int Size, int Align, int N>
    struct list_node<trivial_type<Size, Align>, N>
    {
        list_node() = default;
        list_node(list_node * n) : next(n) {}
        ~list_node() {}
        void * push() { return buf + size++ * Size; }
        void * get(int n) { return buf + n * Size; }
        alignas(Align) std::byte buf[Size * N];
        list_node * next = nullptr;
        int size = 0;
    };

    template<typename T, int N>
    struct linked_list
    {
        using list_node_type = list_node<T, N>;

        linked_list() = default;
        linked_list(linked_list const &) = delete;
        linked_list & operator=(linked_list const &) = delete;
        ~linked_list()
        {
            while (head_) {
                auto * node = head_;
                head_ = head_->next;
                delete node;
            }
        }

        // The bool indicates whether placement new is required.
        std::pair<void *, bool> push()
        {
            if (next_.node) {
                if (next_.idx == next_.node->size) {
                    next_.node = next_.node->next;
                    next_.idx = 0;
                }
                if (next_.node && next_.idx < next_.node->size)
                    return {next_.node->get(next_.idx++), false};
            }

            if (!head_)
                head_ = new list_node_type();
            else if (head_->size == N)
                head_ = new list_node_type(head_);
            return {head_->push(), true};
        }

        void reclaim() { next_ = {head_, 0}; }

    private:
        struct position
        {
            list_node_type * node = nullptr;
            int idx = 0;
        };
        list_node_type * head_ = nullptr;
        position next_{};
    };

    // http://jonkagstrom.com/mx3/mx3_rev2.html
    inline size_t hash_mix(size_t x)
    {
        size_t const m = 0xe9846af9b1a615d;
        x ^= x >> 32;
        x *= m;
        x ^= x >> 32;
        x *= m;
        x ^= x >> 28;
        return x;
    }

    inline size_t hash_combine(size_t seed) { return seed; }
    template<typename T, typename... Ts>
    size_t hash_combine(size_t seed, T const & x, Ts const &... xs)
    {
        auto next_seed =
            detail::hash_mix(seed + 0x9e3779b9 + std::hash<T>{}(x));
        return detail::hash_combine(next_seed, xs...);
    }

    struct memo_items_base
    {
        memo_items_base(size_t id_token)
#if !BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP
            :
            id_token_(id_token)
#endif
        {}
        virtual ~memo_items_base() = 0;
        virtual std::pair<void *, bool> new_item() = 0;
        virtual void reclaim() = 0;
#if !BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP
        size_t const id_token_ = 0;
#endif
    };

    inline memo_items_base::~memo_items_base() {}

    inline constexpr size_t max_tidy_bytes = 16; // TODO: Tune.

    template<typename T>
    constexpr bool tidy = std::is_trivially_copyable_v<T> &&
                              std::is_trivially_destructible_v<T> &&
                          sizeof(T) < max_tidy_bytes;
    template<typename T>
    constexpr bool fat = 256 < sizeof(T);

    template<typename T, bool Fat = fat<T>>
    struct memo_items_impl : memo_items_base
    {
        memo_items_impl() : memo_items_base(typeid(T).hash_code()) {}

        virtual ~memo_items_impl() = default;

        virtual std::pair<void *, bool> new_item() { return list_.push(); }
        virtual void reclaim() { list_.reclaim(); }

    private:
        linked_list<T, 16> list_; // TODO: Try with other values of N too.
    };

    template<int Size, int Align, bool Fat>
    struct memo_items_impl<trivial_type<Size, Align>, Fat> : memo_items_base
    {
        memo_items_impl() :
            memo_items_base(typeid(trivial_type<Size, Align>).hash_code())
        {}

        virtual ~memo_items_impl() = default;

        virtual std::pair<void *, bool> new_item() { return list_.push(); }
        virtual void reclaim() { list_.reclaim(); }

    private:
        linked_list<trivial_type<Size, Align>, 64> list_;
    };

    template<typename T>
    struct memo_items_impl<T, true> : memo_items_base
    {
        memo_items_impl() : memo_items_base(typeid(T).hash_code()) {}

        virtual ~memo_items_impl() = default;

        virtual std::pair<void *, bool> new_item() { return list_.push(); }
        virtual void reclaim() { list_.reclaim(); }

    private:
        linked_list<T, 1> list_;
    };

    struct identity
    {
        template<typename T>
        constexpr decltype(auto) operator()(T && x) const
        {
            return (T &&) x;
        }
    };

    inline namespace BOOST_PARSER_MEMO_NS {

        template<
            typename Key,
            typename OtherDatum = std::monostate,
            typename Proj = identity>
        struct memos
        {
            memos() = default;
            explicit memos(Proj proj) : proj_(std::move(proj)) {}
            ~memos()
            {
#if BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP
                for (auto [key, value] : memo_items_) {
                    delete value;
                }
#else
                for (auto value : memo_items_) {
                    delete value;
                }
#endif
            }

            enum kind { success, failure };

            template<typename A>
            struct monostate_ptr_like
            {
                monostate_ptr_like() : valid(false) {}
                explicit monostate_ptr_like(bool v) : valid(v) {}
                explicit operator bool() const { return valid; }
                bool operator==(nullptr_t) const { return !valid; }
                A & operator*() { return value; }
                A const & operator*() const { return value; }
                A value = A();
                bool valid = false;
                static_assert(std::is_empty_v<A>);
            };

            template<typename A, bool Empty = std::is_empty_v<A>>
            struct ref
            {
                ref() = default;
                ref(A * v, OtherDatum * od) : valid(true), value(v), datum(od)
                {}
                explicit operator bool() const { return valid; }
                kind get_kind() const
                {
                    return value == nullptr ? failure : success;
                }

                bool valid = false;
                A * value = nullptr;
                OtherDatum * datum = 0;
            };
            template<typename A>
            struct ref<A, true>
            {
                ref() = default;
                ref(A *, OtherDatum * od) : valid(true), value(true), datum(od)
                {}
                explicit operator bool() const { return valid; }
                kind get_kind() const
                {
                    return value == nullptr ? failure : success;
                }

                bool valid = false;
                monostate_ptr_like<A> value;
                OtherDatum * datum = 0;
            };

            template<typename A, bool Empty = std::is_empty_v<A>>
            struct const_ref
            {
                const_ref() = default;
                const_ref(A const * v, OtherDatum const * od) :
                    valid(true), value(v), datum(od)
                {}
                explicit operator bool() const { return valid; }
                kind get_kind() const
                {
                    return value == nullptr ? failure : success;
                }

                bool valid = false;
                A const * value = nullptr;
                OtherDatum const * datum = 0;
            };
            template<typename A>
            struct const_ref<A, true>
            {
                const_ref() = default;
                const_ref(A const *, OtherDatum const * od) :
                    valid(true), value(true), datum(od)
                {}
                explicit operator bool() const { return valid; }
                kind get_kind() const
                {
                    return value == nullptr ? failure : success;
                }

                bool valid = false;
                monostate_ptr_like<A> value;
                OtherDatum const * datum = 0;
            };

            template<typename P, typename A, typename... Params>
            ref<A> insert(kind k, Key key, Params const &... params)
            {
                if constexpr (!(std::is_constructible_v<std::hash<Params>> &&
                                ...)) {
                    return {};
                } else {
                    auto const hash = detail::hash_combine(
                        proj_(key),
                        typeid(P).hash_code(),
                        typeid(A).hash_code(),
                        std::hash<Params>{}(params)...);
                    entry & obj_and_other = table_[hash];
                    if (!obj_and_other.obj && k == success) {
                        auto const id =
                            tidy<A> ? typeid(trivial_type_for<A>).hash_code()
                                    : typeid(A).hash_code();
                        if (std::is_empty_v<A>) {
                            obj_and_other = {nullptr, OtherDatum()};
                        } else {
#if BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP
                            memo_items_base *& items = memo_items_[id];
                            if (!items) {
                                if (tidy<A>) {
                                    items = new memo_items_impl<
                                        trivial_type_for<A>>;
                                } else {
                                    items = new memo_items_impl<A>;
                                }
                            }
                            auto [pos, needs_construction] = items->new_item();
                            A * obj = needs_construction
                                          ? new (pos) A()
                                          : static_cast<A *>(pos);
                            obj_and_other = {obj, OtherDatum()};
#else
                            auto it = std::lower_bound(
                                memo_items_.begin(),
                                memo_items_.end(),
                                id,
                                [](memo_items_base * base, size_t id) {
                                    return base->id_token_ < id;
                                });
                            if (it == memo_items_.end() ||
                                (*it)->id_token_ != id) {
                                if (tidy<A>) {
                                    it = memo_items_.insert(
                                        it,
                                        new memo_items_impl<
                                            trivial_type_for<A>>);
                                } else {
                                    it = memo_items_.insert(
                                        it, new memo_items_impl<A>);
                                }
                            }
                            auto [pos, needs_construction] = (*it)->new_item();
                            A * obj = needs_construction
                                          ? new (pos) A()
                                          : static_cast<A *>(pos);
                            obj_and_other = {obj, OtherDatum()};
#endif
                        }
                    }
                    return {
                        static_cast<A *>(obj_and_other.obj),
                        &obj_and_other.datum};
                }
            }

            template<typename P, typename A, typename... Params>
            const_ref<A> find(Key key, Params const &... params) const
            {
                if constexpr (!(std::is_constructible_v<std::hash<Params>> &&
                                ...)) {
                    return {};
                } else {
                    auto const hash = detail::hash_combine(
                        proj_(key),
                        typeid(P).hash_code(),
                        typeid(A).hash_code(),
                        std::hash<Params>{}(params)...);
                    auto it = table_.find(hash);
                    if (it == table_.end()) {
                        return {};
                    } else {
                        return {
                            static_cast<A const *>(it->second.obj),
                            &it->second.datum};
                    }
                }
            }

            void reclaim()
            {
#if BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP
                for (auto [key, items] : memo_items_) {
                    items->reclaim();
                }
#else
                for (auto items : memo_items_) {
                    items->reclaim();
                }
#endif
                table_.clear();
            }

            // For testing.
            size_t item_stores() const { return memo_items_.size(); }
            size_t items() const { return table_.size(); }

        private:
            struct entry
            {
                void * obj;
                [[maybe_unused]] OtherDatum datum;
            };

#if BOOST_PARSER_HAVE_BOOST_UNORDERED_FLAT_MAP
            boost::unordered_flat_map<size_t, memo_items_base *> memo_items_;
            boost::unordered_flat_map<size_t, entry> table_;
#else
            std::vector<memo_items_base *> memo_items_;
            std::unordered_map<size_t, entry> table_;
#endif
            Proj proj_;
        };
    }
}

#endif
