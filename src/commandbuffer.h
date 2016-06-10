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

        CMD_glActiveTexture,
        CMD_glAttachShader,
        CMD_glBindAttribLocation,
        CMD_glBindBuffer,
        CMD_glBindFramebuffer,
        CMD_glBindRenderbuffer,
        CMD_glBindTexture,
        CMD_glBlendColor,
        CMD_glBlendEquation,
        CMD_glBlendEquationSeparate,
        CMD_glBlendFunc,
        CMD_glBlendFuncSeparate,
        CMD_glBufferData,
        CMD_glBufferSubData,
        CMD_glCheckFramebufferStatus,
        CMD_glClear,
        CMD_glClearColor,
        CMD_glClearDepthf,
        CMD_glClearStencil,
        CMD_glColorMask,
        CMD_glCompileShader,
        CMD_glCompressedTexImage2D,
        CMD_glCompressedTexSubImage2D,
        CMD_glCopyTexImage2D,
        CMD_glCopyTexSubImage2D,
        CMD_glCreateProgram,
        CMD_glCreateShader,
        CMD_glCullFace,
        CMD_glDeleteBuffers,
        CMD_glDeleteFramebuffers,
        CMD_glDeleteProgram,
        CMD_glDeleteRenderbuffers,
        CMD_glDeleteShader,
        CMD_glDeleteTextures,
        CMD_glDepthFunc,
        CMD_glDepthMask,
        CMD_glDepthRangef,
        CMD_glDetachShader,
        CMD_glDisable,
        CMD_glDisableVertexAttribArray,
        CMD_glDrawArrays,
        CMD_glDrawElements,
        CMD_glEnable,
        CMD_glEnableVertexAttribArray,
        CMD_glFinish,
        CMD_glFlush,
        CMD_glFramebufferRenderbuffer,
        CMD_glFramebufferTexture2D,
        CMD_glFrontFace,
        CMD_glGenBuffers,
        CMD_glGenerateMipmap,
        CMD_glGenFramebuffers,
        CMD_glGenRenderbuffers,
        CMD_glGenTextures,
        CMD_glGetActiveAttrib,
        CMD_glGetActiveUniform,
        CMD_glGetAttachedShaders,
        CMD_glGetAttribLocation,
        CMD_glGetBooleanv,
        CMD_glGetBufferParameteriv,
        CMD_glGetError,
        CMD_glGetFloatv,
        CMD_glGetFramebufferAttachmentParameteriv,
        CMD_glGetIntegerv,
        CMD_glGetProgramiv,
        CMD_glGetProgramInfoLog,
        CMD_glGetRenderbufferParameteriv,
        CMD_glGetShaderiv,
        CMD_glGetShaderInfoLog,
        CMD_glGetShaderPrecisionFormat,
        CMD_glGetShaderSource,
        CMD_glGetString,
        CMD_glGetTexParameterfv,
        CMD_glGetTexParameteriv,
        CMD_glGetUniformfv,
        CMD_glGetUniformiv,
        CMD_glGetUniformLocation,
        CMD_glGetVertexAttribfv,
        CMD_glGetVertexAttribiv,
        CMD_glGetVertexAttribPointerv,
        CMD_glHint,
        CMD_glIsBuffer,
        CMD_glIsEnabled,
        CMD_glIsFramebuffer,
        CMD_glIsProgram,
        CMD_glIsRenderbuffer,
        CMD_glIsShader,
        CMD_glIsTexture,
        CMD_glLineWidth,
        CMD_glLinkProgram,
        CMD_glPixelStorei,
        CMD_glPolygonOffset,
        CMD_glReadPixels,
        CMD_glReleaseShaderCompiler,
        CMD_glRenderbufferStorage,
        CMD_glSampleCoverage,
        CMD_glScissor,
        CMD_glShaderBinary,
        CMD_glShaderSource,
        CMD_glStencilFunc,
        CMD_glStencilFuncSeparate,
        CMD_glStencilMask,
        CMD_glStencilMaskSeparate,
        CMD_glStencilOp,
        CMD_glStencilOpSeparate,
        CMD_glTexImage2D,
        CMD_glTexParameterf,
        CMD_glTexParameterfv,
        CMD_glTexParameteri,
        CMD_glTexParameteriv,
        CMD_glTexSubImage2D,
        CMD_glUniform1f,
        CMD_glUniform1fv,
        CMD_glUniform1i,
        CMD_glUniform1iv,
        CMD_glUniform2f,
        CMD_glUniform2fv,
        CMD_glUniform2i,
        CMD_glUniform2iv,
        CMD_glUniform3f,
        CMD_glUniform3fv,
        CMD_glUniform3i,
        CMD_glUniform3iv,
        CMD_glUniform4f,
        CMD_glUniform4fv,
        CMD_glUniform4i,
        CMD_glUniform4iv,
        CMD_glUniformMatrix2fv,
        CMD_glUniformMatrix3fv,
        CMD_glUniformMatrix4fv,
        CMD_glUseProgram,
        CMD_glValidateProgram,
        CMD_glVertexAttrib1f,
        CMD_glVertexAttrib1fv,
        CMD_glVertexAttrib2f,
        CMD_glVertexAttrib2fv,
        CMD_glVertexAttrib3f,
        CMD_glVertexAttrib3fv,
        CMD_glVertexAttrib4f,
        CMD_glVertexAttrib4fv,
        CMD_glVertexAttribPointer,
        CMD_glViewport,

        CMD_SwapBuffers = 1000,

        CMD_Reply_glGetShaderiv = 2000,
        CMD_Reply_glGetShaderInfoLog,

        CMD_Ack,

        CMD_LastCommand
    };

    void reset() {
        m_pos = 0;
        m_lastCommand = 0;

        // Just so we're not sitting on huge command buffers with textures and
        // such indefinitely, cap it to 64kb
        if (m_data.size() > 0xffff)
            m_data.clear();
    }

    int position() const { return m_pos; }

    int capacity() const { return m_data.size(); }

    // Expand the command buffer to contain 'bytes' more bytes
    void growTo(int totalSize) {
        m_lastCommand = totalSize;
        if (m_data.size() < totalSize)
            m_data.resize(totalSize);
    }

    void growBy(int bytes) {
        growTo(m_pos + bytes);
    }


    bool atEnd() const { return m_pos >= m_lastCommand; }

    template <typename T> T pop() const {
        assert(!atEnd());
        T t;
        memcpy(&t, m_data.data() + m_pos, sizeof(T));
        m_pos += sizeof(T);
        return t;
    }

    Command popCommand() const { return pop<Command>(); }

    // Expands the command buffer array to contain one command and however
    // many bytes are requested in 'additionalBytes'
    void add(Command cmd, int additionalBytes = 0) {
        growBy(m_pos + additionalBytes + sizeof(Command));
        push(cmd);
    }


    template <typename T> void push(T x) {
        assert(m_data.size() >= m_pos + sizeof(T));
        memcpy(m_data.data() + m_pos, (void *) &x, sizeof(T));
        m_pos += sizeof(T);
    }

    void push(const char *string, int length) {
        assert(m_data.size() >= m_pos + length + sizeof(int));
        push(length);
        memcpy(m_data.data() + m_pos, string, length);
        m_pos += length;
    }

    void advance(int bytes) const { m_pos += bytes; }

    unsigned char *rawAtPosition() { return m_data.data() + m_pos; }
    const unsigned char *rawAtPosition() const { return m_data.data() + m_pos; }

    unsigned char *rawAtStart() { return m_data.data(); }
    const unsigned char *rawAtStart() const { return m_data.data(); }

    void dump() {
        printf("Command buffer is %d bytes, pos=%d\n", m_lastCommand, m_pos);
        int counter = 0;
        for (int i=0; i<m_lastCommand; ++i) {
            printf(" 0x%02x", rawAtStart()[i]);
            if ((++counter) % 16 == 0 || i == m_lastCommand - 1)
                printf("\n");
        }
    }


private:
    mutable int m_pos = 0;
    int m_lastCommand = 0;
    std::vector<unsigned char> m_data;
};

