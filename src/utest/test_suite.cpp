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
 * @file utest/test_suite.cpp
 *
 * @brief Test suite implementation
 */

#include <utest/test.hpp>
#include <utest/test_suite.hpp>
#include <utest/test_case.hpp>
#include <utest/test_reporter.hpp>
#include <utest/test_exception.hpp>

#include <utest/test_message/test_suite.hpp>

using utest::TestSuite;

TestSuite::TestSuite(const Test& test) noexcept :
    m_thread{test.m_thread},
    m_reporters{test.m_reporters},
    m_file{}
{ }

void TestSuite::report(const TestMessage& test_message) noexcept {
    for (auto reporter : m_reporters) {
        if (reporter) {
            reporter->report(test_message);
        }
    }
}

TestSuite& TestSuite::run(TestRun test_run) noexcept {
    report(test_message::TestSuiteBegin{*this});
    TestSize test_cases_passed{0};
    TestSize test_cases_failed{0};

    if (test_run) {
        TestCase test_case{*this};
#if defined(UTEST_USE_EXCEPTIONS)
        try {
            test_run(test_case);
            m_status = test_case.status();
        }
        catch (const std::exception& e) {
            m_status = TestStatus::FAIL;
            report(test_message::TestSuiteException{*this, e.what()});
        }
        catch (...) {
            m_status = TestStatus::FAIL;
            report(test_message::TestSuiteException{*this});
        }
#else
        test_run(test_case);
        m_status = test_case.status();
#endif
        test_cases_passed = test_case.passed();
        test_cases_failed = test_case.failed();
    }
    else {
        m_status = TestStatus::PASS;
    }

    m_test_cases_passed += test_cases_passed;
    m_test_cases_failed += test_cases_failed;

    if (TestStatus::PASS == m_status) {
        ++m_passed;
    }
    else {
        ++m_failed;
    }

    report(test_message::TestSuiteEnd{*this,
            test_cases_passed, test_cases_failed});

    return *this;
}
