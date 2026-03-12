// Copyright (c) 2026 James Hayden
// SPDX-License-Identifier: MIT

#pragma once

#ifdef OPENGEDCOM_BUILD_TESTS
    #define OPENGEDCOM_TEST_FRIEND(ClassName) \
        friend class ClassName;
#else
    #define OPENGEDCOM_TEST_FRIEND(ClassName)
#endif