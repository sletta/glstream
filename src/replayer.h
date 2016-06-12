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

#include "commandbuffer.h"
#include "flatmap.h"

class Replayer
{
public:
    Replayer();

    virtual ~Replayer() { }

    void process(const CommandBuffer &buffer);

    virtual void swap() { }
    virtual void reply(const CommandBuffer &buffer) { };

protected:
    template <typename T> void sendReply(CommandBuffer::Command cmd, T value);
    void sendReply(CommandBuffer::Command cmd, const char *string, int length);

    CommandBuffer m_reply;
};

template <typename T> void Replayer::sendReply(CommandBuffer::Command cmd, T value)
{
    m_reply.push(cmd);
    m_reply.push(value);
    reply(m_reply);
    m_reply.reset();
}

inline void Replayer::sendReply(CommandBuffer::Command cmd, const char *string, int length)
{
    m_reply.push(cmd);
    m_reply.push(string, length);
    reply(m_reply);
    m_reply.reset();
}

