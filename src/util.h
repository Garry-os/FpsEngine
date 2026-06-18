#pragma once
#include <utility>
#include <cassert>

// C++ utilities macros
// Check optional type
// Similar to ? in rust, make sure the function returns an optional.
#define TRY_OPT(name, expr)             \
    auto _tmp_##name = (expr);          \
    if (!_tmp_##name)                   \
        return std::nullopt;            \
    auto name = std::move(*_tmp_##name)

// Check optional type
// Similar to .unwrap() in rust
#define TRY_ASSERT(name, expr, msg)     \
    auto _tmp_##name = (expr);          \
    assert(!_tmp_##name && msg);        \
    auto name = std::move(*_tmp_##name)

