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

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include <cstring>


class CommandBuffer
{
public:

    enum Command {
        CMD_EndOfStream                           = 0,

        CMD_glActiveTexture                       = 1,
        CMD_glAttachShader                        = 2,
        CMD_glBindAttribLocation                  = 3,
        CMD_glBindBuffer                          = 4,
        CMD_glBindFramebuffer                     = 5,
        CMD_glBindRenderbuffer                    = 6,
        CMD_glBindTexture                         = 7,
        CMD_glBlendColor                          = 8,
        CMD_glBlendEquation                       = 9,
        CMD_glBlendEquationSeparate               = 10,
        CMD_glBlendFunc                           = 11,
        CMD_glBlendFuncSeparate                   = 12,
        CMD_glBufferData                          = 13,
        CMD_glBufferSubData                       = 14,
        CMD_glCheckFramebufferStatus              = 15,
        CMD_glClear                               = 16,
        CMD_glClearColor                          = 17,
        CMD_glClearDepthf                         = 18,
        CMD_glClearStencil                        = 19,
        CMD_glColorMask                           = 20,
        CMD_glCompileShader                       = 21,
        CMD_glCompressedTexImage2D                = 22,
        CMD_glCompressedTexSubImage2D             = 23,
        CMD_glCopyTexImage2D                      = 24,
        CMD_glCopyTexSubImage2D                   = 25,
        CMD_glCreateProgram                       = 26,
        CMD_glCreateShader                        = 27,
        CMD_glCullFace                            = 28,
        CMD_glDeleteBuffers                       = 29,
        CMD_glDeleteFramebuffers                  = 30,
        CMD_glDeleteProgram                       = 31,
        CMD_glDeleteRenderbuffers                 = 32,
        CMD_glDeleteShader                        = 33,
        CMD_glDeleteTextures                      = 34,
        CMD_glDepthFunc                           = 35,
        CMD_glDepthMask                           = 36,
        CMD_glDepthRangef                         = 37,
        CMD_glDetachShader                        = 38,
        CMD_glDisable                             = 39,
        CMD_glDisableVertexAttribArray            = 40,
        CMD_glDrawArrays_VBO                      = 41,
        CMD_glDrawArrays                          = 42,
        CMD_glDrawElements_IBO                    = 43,
        CMD_glDrawElements                        = 44,
        CMD_glEnable                              = 45,
        CMD_glEnableVertexAttribArray             = 46,
        CMD_glFinish                              = 47,
        CMD_glFlush                               = 48,
        CMD_glFramebufferRenderbuffer             = 49,
        CMD_glFramebufferTexture2D                = 50,
        CMD_glFrontFace                           = 51,
        CMD_glGenBuffers                          = 52,
        CMD_glGenerateMipmap                      = 53,
        CMD_glGenFramebuffers                     = 54,
        CMD_glGenRenderbuffers                    = 55,
        CMD_glGenTextures                         = 56,
        CMD_glGetActiveAttrib                     = 57,
        CMD_glGetActiveUniform                    = 58,
        CMD_glGetAttachedShaders                  = 59,
        CMD_glGetAttribLocation                   = 60,
        CMD_glGetBooleanv                         = 61,
        CMD_glGetBufferParameteriv                = 62,
        CMD_glGetError                            = 63,
        CMD_glGetFloatv                           = 64,
        CMD_glGetFramebufferAttachmentParameteriv = 65,
        CMD_glGetIntegerv                         = 66,
        CMD_glGetProgramiv                        = 67,
        CMD_glGetProgramInfoLog                   = 68,
        CMD_glGetRenderbufferParameteriv          = 69,
        CMD_glGetShaderiv                         = 70,
        CMD_glGetShaderInfoLog                    = 71,
        CMD_glGetShaderPrecisionFormat            = 72,
        CMD_glGetShaderSource                     = 73,
        CMD_glGetString                           = 74,
        CMD_glGetTexParameterfv                   = 75,
        CMD_glGetTexParameteriv                   = 76,
        CMD_glGetUniformfv                        = 77,
        CMD_glGetUniformiv                        = 78,
        CMD_glGetUniformLocation                  = 79,
        CMD_glGetVertexAttribfv                   = 80,
        CMD_glGetVertexAttribiv                   = 81,
        CMD_glGetVertexAttribPointerv             = 82,
        CMD_glHint                                = 83,
        CMD_glIsBuffer                            = 84,
        CMD_glIsEnabled                           = 85,
        CMD_glIsFramebuffer                       = 86,
        CMD_glIsProgram                           = 87,
        CMD_glIsRenderbuffer                      = 88,
        CMD_glIsShader                            = 89,
        CMD_glIsTexture                           = 90,
        CMD_glLineWidth                           = 91,
        CMD_glLinkProgram                         = 92,
        CMD_glPixelStorei                         = 93,
        CMD_glPolygonOffset                       = 94,
        CMD_glReadPixels                          = 95,
        CMD_glReleaseShaderCompiler               = 96,
        CMD_glRenderbufferStorage                 = 97,
        CMD_glSampleCoverage                      = 98,
        CMD_glScissor                             = 99,
        CMD_glShaderBinary                        = 100,
        CMD_glShaderSource                        = 101,
        CMD_glStencilFunc                         = 102,
        CMD_glStencilFuncSeparate                 = 103,
        CMD_glStencilMask                         = 104,
        CMD_glStencilMaskSeparate                 = 105,
        CMD_glStencilOp                           = 106,
        CMD_glStencilOpSeparate                   = 107,
        CMD_glTexImage2D                          = 108,
        CMD_glTexParameterf                       = 109,
        CMD_glTexParameterfv                      = 110,
        CMD_glTexParameteri                       = 111,
        CMD_glTexParameteriv                      = 112,
        CMD_glTexSubImage2D                       = 113,
        CMD_glUniform1f                           = 114,
        CMD_glUniform1fv                          = 115,
        CMD_glUniform1i                           = 116,
        CMD_glUniform1iv                          = 117,
        CMD_glUniform2f                           = 118,
        CMD_glUniform2fv                          = 119,
        CMD_glUniform2i                           = 120,
        CMD_glUniform2iv                          = 121,
        CMD_glUniform3f                           = 122,
        CMD_glUniform3fv                          = 123,
        CMD_glUniform3i                           = 124,
        CMD_glUniform3iv                          = 125,
        CMD_glUniform4f                           = 126,
        CMD_glUniform4fv                          = 127,
        CMD_glUniform4i                           = 128,
        CMD_glUniform4iv                          = 129,
        CMD_glUniformMatrix2fv                    = 130,
        CMD_glUniformMatrix3fv                    = 131,
        CMD_glUniformMatrix4fv                    = 132,
        CMD_glUseProgram                          = 133,
        CMD_glValidateProgram                     = 134,
        CMD_glVertexAttrib1f                      = 135,
        CMD_glVertexAttrib1fv                     = 136,
        CMD_glVertexAttrib2f                      = 137,
        CMD_glVertexAttrib2fv                     = 138,
        CMD_glVertexAttrib3f                      = 139,
        CMD_glVertexAttrib3fv                     = 140,
        CMD_glVertexAttrib4f                      = 141,
        CMD_glVertexAttrib4fv                     = 142,
        CMD_glVertexAttribPointer_VBO             = 143,
        CMD_glVertexAttribPointer                 = 144,
        CMD_glViewport                            = 145,

        CMD_SwapBuffers                           = 1000,

        CMD_Reply_FirstReply                      = 1001,
        CMD_Reply_glGenBuffers                    = 1002,
        CMD_Reply_glCreateProgram                 = 1003,
        CMD_Reply_glCreateShader                  = 1004,
        CMD_Reply_glGetError                      = 1005,
        CMD_Reply_glGetProgramiv                  = 1006,
        CMD_Reply_glGetProgramInfoLog             = 1007,
        CMD_Reply_glGetShaderiv                   = 1008,
        CMD_Reply_glGetShaderInfoLog              = 1009,
        CMD_Reply_glGetUniformLocation            = 1010,

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

    void setLastCommand(int lastCommand) { m_lastCommand = lastCommand; }

    int position() const { return m_pos; }

    int capacity() const { return m_data.size(); }

    // Expand the command buffer to contain 'bytes' more bytes
    void growTo(int totalSize) {
        if (m_data.size() < totalSize) {
            totalSize = ((totalSize >> 12) + 1) << 12;
            m_data.resize(totalSize);
        }
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

    Command popCommand() const {
        Command cmd = pop<Command>();
        assert(cmd < CMD_LastCommand);
        return cmd;
    }

    std::string popStdString() const {
        unsigned int size = pop<unsigned int>();
        std::string s((const char *) rawAtPosition(), size);
        advance(size);
        return s;
    }

    template <typename T> unsigned int popArray(T **array) const {
        unsigned int size = pop<unsigned int>();
        std::cout << " - array size: " << size << std::endl;
        *array = (T *) rawAtPosition();
        advance(sizeof(T) * size);
        return size;
    }

    template <typename T> void push(const T *array, unsigned int size) {
        growBy(size + sizeof(unsigned int));
        push(size);
        memcpy(m_data.data() + m_pos, array, size);
        m_pos += size;
    }

    template <typename T> void push(T x) {
        growBy(sizeof(T));
        memcpy(m_data.data() + m_pos, (void *) &x, sizeof(T));
        m_pos += sizeof(T);
    }

    void advance(int bytes) const {
        m_pos += bytes;
        assert(m_pos < capacity());
    }

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

