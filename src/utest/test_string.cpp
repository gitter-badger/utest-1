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
 * @file utest/test_string.cpp
 *
 * @brief Test string implementation
 */

#include <utest/test_string.hpp>
#include <cctype>

using utest::TestSize;
using utest::TestString;

TestSize TestString::length(const_pointer str) noexcept {
    TestSize size{0};

    if (str) {
        while (('\0' != *str) && (size < MAX_LENGTH)) {
            ++str;
            ++size;
        }
    }

    return size;
}

bool utest::operator==(const TestString& str1,
        const TestString& str2) noexcept {
    bool status{false};

    if (str1.size() == str2.size()) {
        if (str1.ignoring_case()) {
            status = std::equal(str1.cbegin(), str1.cend(), str2.cbegin(),
                [] (const TestString::value_type& ch1,
                        const TestString::value_type& ch2) {
                    return std::tolower(ch1) == std::tolower(ch2);
                }
            );
        }
        else {
            status = std::equal(str1.cbegin(), str1.cend(), str2.cbegin());
        }
    }

    return status;
}
