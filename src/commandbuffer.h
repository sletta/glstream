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

#include <GLES2/gl2.h>

#include <vector>
#include <assert.h>
#include <cstring>
#include <iostream>
// #include <stdlib.h>
// #include <stdio.h>

class CommandBuffer
{
public:

    enum Command {
        CMD_EndOfStream,
        CMD_glClearColor,
        CMD_glClear,

        CMD_LastCommand
    };

    void reset() {
        m_pos = 0;
    }

    const std::vector<unsigned char> &buffer() const { return m_data; }
    int size() const { return m_pos; }

    std::vector<unsigned char> *writeBuffer() { return &m_data; }

    void glClearColor(float r, float g, float b, float a) {
        ensureCapacity(sizeof(float) * 4 + sizeof(Command));
        push(CMD_glClearColor);
        push(r);
        push(g);
        push(b);
        push(a);
    }

    void glClear(GLbitfield mask) {
        ensureCapacity(sizeof(GLbitfield) + sizeof(Command));
        push(CMD_glClear);
        push(mask);
    }

    bool atEnd() const { return m_pos >= m_data.size(); }

    template <typename T> T pop() {
        assert(!atEnd());
        T t;
        memcpy(&t, m_data.data() + m_pos, sizeof(T));
        m_pos += sizeof(T);
        return t;
    }

private:
    void ensureCapacity(int toAdd) {
        int totalSize = m_pos + toAdd;
        if (m_data.size() < totalSize) {
            m_data.resize(totalSize);
        }
    }

    template <typename T> void push(T x) {
        assert(m_data.size() >= m_pos + sizeof(T));
        memcpy(m_data.data() + m_pos, (void *) &x, sizeof(T));
        m_pos += sizeof(T);
    }

    int m_pos = 0;
    std::vector<unsigned char> m_data;
};