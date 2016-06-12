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

#include <EGL/egl.h>

#include "commandbuffer.h"
#include "globjectpool.h"

#include <mutex>

class Transport;
class EGLSDisplayImpl;

struct EGLSContextImpl
{
    void flush();

    template <typename T> void syncServerReply(CommandBuffer::Command replyCommand, T *value);
    void syncServerReply(CommandBuffer::Command replyCommand, GLsizei bufSize, GLsizei *length, GLchar *string);

    EGLConfig config = 0;
    EGLSDisplayImpl *display = 0;

    CommandBuffer cmds;
};

struct EGLSWindowSurface
{
    EGLConfig config = 0;
    EGLDisplay display = 0;
};

struct EGLSThreadState
{
    EGLint error = EGL_SUCCESS;
    EGLSContextImpl *context = 0;
    EGLSurface drawSurface = 0;
    EGLSurface readSurface = 0;
};

class EGLSDisplayImpl
{
public:
    void setInitialized(bool i) { m_initialized = i; }
    bool isInitialized() const { return m_initialized; }

    bool connectToServer();

    bool flush(EGLSContextImpl *context);

private:

    std::mutex m_transportMutex;
    Transport *m_transport = 0;
    bool m_initialized = false;
};

inline void EGLSContextImpl::flush()
{
    display->flush(this);
}

template <typename T>
inline void EGLSContextImpl::syncServerReply(CommandBuffer::Command replyCommand, T *value)
{
    flush();
    CommandBuffer::Command reply = cmds.popCommand();
    assert(reply == replyCommand);
    *value = cmds.pop<T>();
    cmds.reset();
}

inline void EGLSContextImpl::syncServerReply(CommandBuffer::Command replyCommand, GLsizei maxSize, GLsizei *length, GLchar *string)
{
    flush();
    CommandBuffer::Command reply = cmds.popCommand();
    assert(reply == replyCommand);
    *length = std::min(cmds.pop<GLsizei>(), maxSize);
    memcpy(string, cmds.rawAtPosition(), *length);
    cmds.reset();
}


EGLSThreadState *egls_getThreadState();
