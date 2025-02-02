/*!
 * @copright
 * Copyright (c) 2017, Tymoteusz Blazejczyk
 * All rights reserved.
 *
 * @copright
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * @copright
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * @copright
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * @copright
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * @copright
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file utest/test_value.hpp
 *
 * @brief Test value interface
 */

#ifndef UTEST_TEST_VALUE_HPP
#define UTEST_TEST_VALUE_HPP

#include <utest/test_string.hpp>
#include <utest/test_number.hpp>

#include <type_traits>

namespace utest {

class TestValue {
public:
    template<typename T>
    using enable_object = typename std::enable_if<
            !std::is_convertible<typename T::pointer, char*>::value
        , int>::type;

    enum Type {
        NUMBER,
        STRING,
        OBJECT
    };

    Type type() const noexcept {
        return m_type;
    }

    template<typename T>
    const T& get() const noexcept;

    TestValue(const TestNumber& value) noexcept;

    TestValue(const TestString& value) noexcept;

    template<TestSize N>
    TestValue(const char (&str)[N]) noexcept;

    template<typename T, enable_object<T> = 0>
    TestValue(const T& value) noexcept;
private:
    TestValue(const void* value) noexcept;

    Type m_type;

    union {
        const TestNumber m_number;
        const TestString m_string;
        const void* m_object;
    };
};

template<typename T, TestValue::enable_object<T>> inline
TestValue::TestValue(const T& value) noexcept :
    TestValue{static_cast<const void*>(&value)}
{ }

template<TestSize N> inline
TestValue::TestValue(const char (&str)[N]) noexcept :
    TestValue{TestString{str}}
{ }

template<> inline auto
TestValue::get<TestString>() const noexcept -> const TestString& {
    return m_string;
}

template<> inline auto
TestValue::get<TestNumber>() const noexcept -> const TestNumber& {
    return m_number;
}

template<> inline auto
TestValue::get<const void*>() const noexcept ->
        const void* const& {
    return m_object;
}

}

#endif /* UTEST_TEST_VALUE_HPP */
