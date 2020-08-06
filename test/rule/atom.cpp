// Copyright (C) 2020 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <lexy/dsl/base.hpp>

#include "verify.hpp"

TEST_CASE("rule: atom")
{
    constexpr auto rule = LEXY_LIT("abc");
    CHECK(lexy::is_dsl<decltype(rule)>);

    struct callback
    {
        const char* str;

        constexpr int success(const char* cur)
        {
            assert(cur - str == 3);
            return 0;
        }

        constexpr int error(test_error<lexy::expected_literal> e)
        {
            assert(e.string() == "abc");
            return -1;
        }
    };

    constexpr auto empty = rule_matches<callback>(rule, "");
    CHECK(empty == -1);

    constexpr auto success = rule_matches<callback>(rule, "abc");
    CHECK(success == 0);
}

