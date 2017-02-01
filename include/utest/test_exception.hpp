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
 * @file utest/test_exception.hpp
 *
 * @brief Test exception interface
 */

#ifndef UTEST_TEST_EXCEPTION_HPP
#define UTEST_TEST_EXCEPTION_HPP

#if defined(__clang__)
    #if !defined(UTEST_USE_EXCEPTIONS) && __has_feature(cxx_exceptions)
        #define UTEST_USE_EXCEPTIONS
    #endif
#elif defined(__GNUG__)
    #if !defined(UTEST_USE_EXCEPTIONS) && defined(__EXCEPTIONS)
        #define UTEST_USE_EXCEPTIONS
    #endif
#endif

#if defined(UTEST_USE_EXCEPTIONS)
#include <exception>
#include <stdexcept>
#endif

#include <utest/test_string.hpp>

namespace utest {

class TestException {
public:
    const TestString& what() const noexcept;
protected:
    TestException() noexcept;

    TestException(const TestString& message) noexcept;

    TestString m_message{};
};

inline
TestException::TestException(const TestString& message) noexcept
    : m_message{message}
{ }

inline auto
TestException::what() const noexcept -> const TestString& {
    return m_message;
}

}

#endif /* UTEST_TEST_EXCEPTION_HPP */