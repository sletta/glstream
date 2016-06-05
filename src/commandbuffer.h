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

        CMD_SwapBuffers,

        CMD_Ack,

        CMD_LastCommand
    };

    void reset() {
        m_pos = 0;
    }

    const std::vector<unsigned char> &buffer() const { return m_data; }
    int size() const { return m_pos; }

    std::vector<unsigned char> *writableBuffer() { return &m_data; }

    bool atEnd() const { return m_pos >= m_data.size(); }

    template <typename T> T pop() const {
        assert(!atEnd());
        T t;
        memcpy(&t, m_data.data() + m_pos, sizeof(T));
        m_pos += sizeof(T);
        return t;
    }

    Command popCommand() const { return pop<Command>(); }


    // GL Commands
    void glClearColor(float r, float g, float b, float a);
    void glClear(GLbitfield mask);

    // EGL Commands
    void swapBuffers();

    // Other commands
    void ack();

private:
    void ensureCapacityForCommand(int toAdd) {
        int totalSize = m_pos + toAdd + sizeof(Command);
        if (m_data.size() < totalSize) {
            m_data.resize(totalSize);
        }
    }

    template <typename T> void push(T x) {
        assert(m_data.size() >= m_pos + sizeof(T));
        memcpy(m_data.data() + m_pos, (void *) &x, sizeof(T));
        m_pos += sizeof(T);
    }

    mutable int m_pos = 0;
    std::vector<unsigned char> m_data;
};

inline void CommandBuffer::glClearColor(float r, float g, float b, float a)
{
    ensureCapacityForCommand(sizeof(float) * 4);
    push(CMD_glClearColor);
    push(r);
    push(g);
    push(b);
    push(a);
}

inline void CommandBuffer::glClear(GLbitfield mask)
{
    ensureCapacityForCommand(sizeof(GLbitfield));
    push(CMD_glClear);
    push(mask);
}

inline void CommandBuffer::swapBuffers()
{
    ensureCapacityForCommand(0);
    push(CMD_SwapBuffers);
}

inline void CommandBuffer::ack()
{
    ensureCapacityForCommand(0);
    push(CMD_Ack);
}
