/**
 *   Copyright (C) 2024 T. Zachary Laine
 *
 *   Distributed under the Boost Software License, Version 1.0. (See
 *   accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/parser/detail/memos.hpp>

#include <variant> // for monostate

#include <gtest/gtest.h>


using namespace boost::parser;

TEST(memos, linked_list_1)
{
    {
        detail::linked_list<std::string, 1> list;
    }
    {
        detail::linked_list<std::string, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
    }
    {
        detail::linked_list<int, 1> list;
    }
    {
        detail::linked_list<int, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
    }

    // reclaim, no reuse
    {
        detail::linked_list<std::string, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
        list.reclaim();
    }
    {
        detail::linked_list<int, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
        list.reclaim();
    }

    // reclaim, partial reuse
    {
        detail::linked_list<std::string, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
        list.reclaim();

        for (int i = 0; i < 9; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            char const expected[] = {char('a' + (16 - 1) - i), 0};
            EXPECT_EQ(*str, expected);
            *str = "reused";
        }
    }
    {
        detail::linked_list<int, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
        list.reclaim();

        for (int i = 0; i < 9; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            EXPECT_EQ(*j, (16 - 1) - i);
            *j = -1;
        }
    }

    // reclaim, full reuse
    {
        detail::linked_list<std::string, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
        list.reclaim();

        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            char const expected[] = {char('a' + (16 - 1) - i), 0};
            EXPECT_EQ(*str, expected);
            *str = "reused";
        }
    }
    {
        detail::linked_list<int, 1> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
        list.reclaim();

        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            EXPECT_EQ(*j, (16 - 1) - i);
            *j = -1;
        }
    }
}

TEST(memos, linked_list_8)
{
    {
        detail::linked_list<std::string, 8> list;
    }
    {
        detail::linked_list<std::string, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
    }
    {
        detail::linked_list<int, 8> list;
    }
    {
        detail::linked_list<int, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
    }

    // reclaim, no reuse
    {
        detail::linked_list<std::string, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
        list.reclaim();
    }
    {
        detail::linked_list<int, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
        list.reclaim();
    }

    // reclaim, partial reuse
    {
        detail::linked_list<std::string, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
        list.reclaim();

        for (int i = 0; i < 9; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            char c = i < 8 ? char('a' + i + 8) : char('a' + i - 8);
            char const expected[] = {c, 0};
            EXPECT_EQ(*str, expected);
            *str = "reused";
        }
    }
    {
        detail::linked_list<int, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
        list.reclaim();

        for (int i = 0; i < 9; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            if (i < 8)
                EXPECT_EQ(*j, i + 8);
            else
                EXPECT_EQ(*j, i - 8);
            *j = -1;
        }
    }

    // reclaim, full reuse
    {
        detail::linked_list<std::string, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            *str = 'a' + i;
        }
        list.reclaim();

        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            std::string * str = needs_new ? new (pos) std::string()
                                          : static_cast<std::string *>(pos);
            char c = i < 8 ? char('a' + i + 8) : char('a' + i - 8);
            char const expected[] = {c, 0};
            EXPECT_EQ(*str, expected);
            *str = "reused";
        }
    }
    {
        detail::linked_list<int, 8> list;
        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            *j = i;
        }
        list.reclaim();

        for (int i = 0; i < 16; ++i) {
            auto [pos, needs_new] = list.push();
            int * j = needs_new ? new (pos) int() : static_cast<int *>(pos);
            if (i < 8)
                EXPECT_EQ(*j, i + 8);
            else
                EXPECT_EQ(*j, i - 8);
            *j = -1;
        }
    }
}

struct one
{};
struct two
{};

TEST(memos, basic)
{
    constexpr auto failure = detail::memos<size_t, size_t>::failure;
    constexpr auto success = detail::memos<size_t, size_t>::success;

    {
        detail::memos<size_t, size_t> memos;
    }
    {
        detail::memos<size_t, size_t> memos;
        detail::memos<size_t, size_t>::const_ref<int> ref = memos.find<one, int>(13);
        EXPECT_FALSE(ref);
        EXPECT_EQ(ref.valid, false);
        EXPECT_EQ(ref.value, nullptr);
        EXPECT_EQ(ref.datum, nullptr);
    }
    {
        detail::memos<size_t, size_t> memos;
        detail::memos<size_t, size_t>::ref<int> ref =
            memos.insert<one, int>(failure, 13);
        EXPECT_TRUE(ref);
        EXPECT_EQ(ref.get_kind(), failure);
        EXPECT_EQ(ref.valid, true);
        EXPECT_EQ(ref.value, nullptr);
        EXPECT_NE(ref.datum, nullptr);
        EXPECT_EQ(*ref.datum, 0);

        EXPECT_FALSE((memos.find<one, int>(12)));
        EXPECT_FALSE((memos.find<one, int>(13, 42)));
        EXPECT_FALSE((memos.find<two, int>(13)));
        EXPECT_FALSE((memos.find<one, double>(13)));

        detail::memos<size_t, size_t>::const_ref<int> cref = memos.find<one, int>(13);
        EXPECT_TRUE(cref);
        EXPECT_EQ(cref.get_kind(), failure);
        EXPECT_EQ(cref.valid, true);
        EXPECT_EQ(cref.value, nullptr);
        EXPECT_NE(cref.datum, nullptr);
        EXPECT_EQ(*cref.datum, 0);
    }
    {
        detail::memos<size_t, size_t> memos;
        detail::memos<size_t, size_t>::ref<int> ref =
            memos.insert<one, int>(success, 13);
        EXPECT_TRUE(ref);
        EXPECT_EQ(ref.get_kind(), success);
        EXPECT_EQ(ref.valid, true);
        EXPECT_NE(ref.value, nullptr);
        EXPECT_NE(ref.datum, nullptr);
        EXPECT_EQ(*ref.datum, 0);

        EXPECT_FALSE((memos.find<one, int>(12)));
        EXPECT_FALSE((memos.find<one, int>(13, 42)));
        EXPECT_FALSE((memos.find<two, int>(13)));
        EXPECT_FALSE((memos.find<one, double>(13)));

        detail::memos<size_t, size_t>::const_ref<int> cref = memos.find<one, int>(13);
        EXPECT_TRUE(cref);
        EXPECT_EQ(cref.get_kind(), success);
        EXPECT_EQ(cref.valid, true);
        EXPECT_NE(cref.value, nullptr);
        EXPECT_NE(cref.datum, nullptr);
        EXPECT_EQ(*cref.datum, 0);
    }

    // types sharing the same trivial_type<size, align>
    {
        detail::memos<size_t, size_t> memos;
        detail::memos<size_t, size_t>::ref<int> ref =
            memos.insert<one, int>(success, 13);
        EXPECT_TRUE(ref);
        EXPECT_EQ(ref.get_kind(), success);
        EXPECT_EQ(ref.valid, true);
        EXPECT_NE(ref.value, nullptr);
        EXPECT_NE(ref.datum, nullptr);
        EXPECT_EQ(*ref.datum, 0);

        *ref.value = 42;

        EXPECT_FALSE((memos.find<one, int>(12)));
        EXPECT_FALSE((memos.find<one, int>(13, 42)));
        EXPECT_FALSE((memos.find<two, int>(13)));
        EXPECT_FALSE((memos.find<one, float>(13)));

        detail::memos<size_t, size_t>::const_ref<int> cref = memos.find<one, int>(13);
        EXPECT_TRUE(cref);
        EXPECT_EQ(cref.get_kind(), success);
        EXPECT_EQ(cref.valid, true);
        EXPECT_NE(cref.value, nullptr);
        EXPECT_EQ(*cref.value, 42);
        EXPECT_NE(cref.datum, nullptr);
        EXPECT_EQ(*cref.datum, 0);

        detail::memos<size_t, size_t>::ref<float> ref2 =
            memos.insert<one, float>(success, 18);
        EXPECT_TRUE(ref2);
        EXPECT_EQ(ref2.get_kind(), success);
        EXPECT_EQ(ref2.valid, true);
        EXPECT_NE(ref2.value, nullptr);
        EXPECT_NE(ref2.datum, nullptr);
        EXPECT_EQ(*ref2.datum, 0);

        *ref2.value = 13.0f;

        EXPECT_FALSE((memos.find<one, float>(17)));
        EXPECT_FALSE((memos.find<one, float>(18, 42)));
        EXPECT_FALSE((memos.find<two, float>(18)));
        EXPECT_FALSE((memos.find<one, char32_t>(18)));

        detail::memos<size_t, size_t>::const_ref<float> cref2 = memos.find<one, float>(18);
        EXPECT_TRUE(cref2);
        EXPECT_EQ(cref2.get_kind(), success);
        EXPECT_EQ(cref2.valid, true);
        EXPECT_NE(cref2.value, nullptr);
        EXPECT_EQ(*cref2.value, 13.0f);
        EXPECT_NE(cref2.datum, nullptr);
        EXPECT_EQ(*cref2.datum, 0);

        detail::memos<size_t, size_t>::ref<char32_t> ref3 =
            memos.insert<two, char32_t>(success, 21);
        EXPECT_TRUE(ref3);
        EXPECT_EQ(ref3.get_kind(), success);
        EXPECT_EQ(ref3.valid, true);
        EXPECT_TRUE(ref3.value);
        EXPECT_NE(ref3.datum, nullptr);
        EXPECT_EQ(*ref3.datum, 0);

        *ref3.value = U'c';

        EXPECT_FALSE((memos.find<two, char32_t>(20)));
        EXPECT_FALSE((memos.find<two, char32_t>(21, 42)));
        EXPECT_FALSE((memos.find<one, char32_t>(21)));
        EXPECT_FALSE((memos.find<two, int>(21)));

        detail::memos<size_t, size_t>::const_ref<char32_t> cref3 =
            memos.find<two, char32_t>(21);
        EXPECT_TRUE(cref3);
        EXPECT_EQ(cref3.get_kind(), success);
        EXPECT_EQ(cref3.valid, true);
        EXPECT_TRUE(cref3.value);
        EXPECT_EQ((unsigned int)*cref3.value, (unsigned int)U'c');
        EXPECT_NE(cref3.datum, nullptr);
        EXPECT_EQ(*cref3.datum, 0);

        // three items
        EXPECT_EQ(memos.items(), 3u);
        // all three items use the same liked list for storage
        EXPECT_EQ(memos.item_stores(), 1u);
    }

    // empty types
    {
        detail::memos<size_t, size_t> memos;
        detail::memos<size_t, size_t>::ref<std::monostate> ref =
            memos.insert<one, std::monostate>(success, 13);
        EXPECT_TRUE(ref);
        EXPECT_EQ(ref.get_kind(), success);
        EXPECT_EQ(ref.valid, true);
        EXPECT_EQ(*ref.value, std::monostate{});
        *ref.value = std::monostate{};
        EXPECT_NE(ref.datum, nullptr);
        EXPECT_EQ(*ref.datum, 0);

        EXPECT_FALSE((memos.find<one, std::monostate>(12)));
        EXPECT_FALSE((memos.find<one, std::monostate>(13, 42)));
        EXPECT_FALSE((memos.find<two, std::monostate>(13)));
        EXPECT_FALSE((memos.find<one, double>(13)));

        detail::memos<size_t, size_t>::const_ref<std::monostate> cref =
            memos.find<one, std::monostate>(13);
        EXPECT_TRUE(cref);
        EXPECT_EQ(cref.get_kind(), success);
        EXPECT_EQ(cref.valid, true);
        EXPECT_EQ(*cref.value, std::monostate{});
        EXPECT_NE(cref.datum, nullptr);
        EXPECT_EQ(*cref.datum, 0);
    }
}
