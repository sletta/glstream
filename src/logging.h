/*
    Copyright (c) 2016, Gunnar Sletta <gunnar@sletta.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>

#ifndef GLSTREAM_LOGGING
#define logw(format, ...)
#define logwe(format)
#define logi(format, ...)
#define logie(format)
#define logd(format, ...)
#define logde(format)
#else

inline std::string log_timestring()
{
    auto time = std::chrono::system_clock::now().time_since_epoch();
    unsigned s = std::chrono::duration_cast<std::chrono::seconds>(time).count() % 1000;
    unsigned ms = std::chrono::duration_cast<std::chrono::milliseconds>(time).count() % 1000;
    unsigned us = std::chrono::duration_cast<std::chrono::microseconds>(time).count() % 1000;
    // ssss:mmm.uuu
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%4d:%03d.%03d", s, ms, us);
    return buffer;
}

#  if GLSTREAM_LOGGING >= 3
#     define logd(format, ...) { fprintf(stderr, "D [%s]: " format, log_timestring().c_str(), ##__VA_ARGS__); fflush(stderr); }
#  endif
#  if GLSTREAM_LOGGING >= 2
#     define logi(format, ...) { fprintf(stderr, "I [%s]: " format, log_timestring().c_str(), ##__VA_ARGS__); fflush(stderr); }
#  endif
#  if GLSTREAM_LOGGING >= 1
#     define logw(format, ...) { fprintf(stderr, "W [%s]: " format, log_timestring().c_str(), ##__VA_ARGS__); fflush(stderr); }
#  endif
#endif