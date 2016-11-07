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

#define GLSTREAM_LOGGING_CONTEXT "GLES2:cl"

#include "egls.h"
#include "logging.h"

#define BEGIN_GLES2_FUNCTION                                         \
    EGLSThreadState *threadState = egls_getThreadState();            \
    EGLSContextImpl *context = threadState->context;                 \
    if (!context) {                                                  \
        logw("No current context (%s)", __PRETTY_FUNCTION__);        \
        exit(-1);                                                    \
    }                                                                \
    auto &cmd = context->cmds;

#define END_GLES2_FUNCTION



extern "C" GL_APICALL void GL_APIENTRY glActiveTexture (GLenum texture)
{
    logd("glActiveTexture(%x)", texture);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glActiveTexture);
    cmd.push(texture);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glAttachShader (GLuint program, GLuint shader)
{
    logd("glAttachShader(%d, %d)", program, shader);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glAttachShader);
    cmd.push(program);
    cmd.push(shader);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar *name)
{
    logd("glBindAttribLocation(%d, %d, %s)", program, index, name);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glBindAttribLocation);
    cmd.push(program);
    cmd.push(index);
    cmd.push((const char *) name, strlen(name));

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer)
{
    logd("glBindBuffer(%x, %d)", target, buffer);

    BEGIN_GLES2_FUNCTION;

    // Also update the local state because we need that to handle
    // glVertexAttribPointer and glDrawXxx
    switch (target) {
        case GL_ARRAY_BUFFER: context->arrayBuffer = buffer; break;
        case GL_ELEMENT_ARRAY_BUFFER: context->elementArrayBuffer = buffer; break;
        default: break;
    }

    cmd.push(CommandBuffer::CMD_glBindBuffer);
    cmd.push(target);
    cmd.push(buffer);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer)
{
    logd("%s(%d, %d)", __func__, target, framebuffer);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glBindFramebuffer);
    cmd.push(target);
    cmd.push(framebuffer);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBindRenderbuffer);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBindTexture (GLenum target, GLuint texture)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBindTexture);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBlendColor);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBlendEquation (GLenum mode)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBlendEquation);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBlendEquationSeparate);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor)
{
    logd("glBlendFunc(%x, %x)", sfactor, dfactor);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBlendFunc);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBlendFuncSeparate (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    logd("glBlendFuncSeparate(%x, %x, %x, %x)", sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBlendFuncSeparate);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
    logd("glBufferData(%x, %d, %p, %x)", target, (int) size, data, usage);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBufferData);
    cmd.push(target);
    cmd.push((const char *) data, size);
    cmd.push(usage);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glBufferSubData);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL GLenum GL_APIENTRY glCheckFramebufferStatus (GLenum target)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCheckFramebufferStatus);
    END_GLES2_FUNCTION;
    return GL_FRAMEBUFFER_UNSUPPORTED;
}

extern "C" GL_APICALL void GL_APIENTRY glClear (GLbitfield mask)
{
    logd("glClear(%x)", mask);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glClear);
    cmd.push(mask);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    logd("glClearColor(%f, %f, %f, %f)", r, g, b, a);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glClearColor);
    cmd.push(r);
    cmd.push(g);
    cmd.push(b);
    cmd.push(a);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glClearDepthf (GLfloat d)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glClearDepthf);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glClearStencil (GLint s)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glClearStencil);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glColorMask);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glCompileShader (GLuint shader)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCompileShader);
    cmd.push(shader);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCompressedTexImage2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCompressedTexSubImage2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCopyTexImage2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCopyTexSubImage2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL GLuint GL_APIENTRY glCreateProgram (void)
{
    logd("%s()", __func__);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glCreateProgram);

    GLuint id;
    context->syncServerReply(CommandBuffer::CMD_Reply_glCreateProgram, &id);
    logd(" -> id=%d", id);

    END_GLES2_FUNCTION;

    return id;
}

extern "C" GL_APICALL GLuint GL_APIENTRY glCreateShader(GLenum type)
{
    logd("%s(%x)", __func__, type);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glCreateShader);
    cmd.push(type);

    GLuint id;
    context->syncServerReply(CommandBuffer::CMD_Reply_glCreateShader, &id);
    logd(" -> id=%d", id);

    END_GLES2_FUNCTION;

    return id;
}

extern "C" GL_APICALL void GL_APIENTRY glCullFace (GLenum mode)
{
    logd("%s", __PRETTY_FUNCTION__);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glCullFace);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint *buffers)
{
    logd("%s", __PRETTY_FUNCTION__);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDeleteBuffers);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers)
{
    logd("%s", __PRETTY_FUNCTION__);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDeleteFramebuffers);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDeleteProgram (GLuint program)
{
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDeleteProgram);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDeleteRenderbuffers);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDeleteShader (GLuint shader)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDeleteShader);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDeleteTextures);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDepthFunc (GLenum func)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDepthFunc);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDepthMask (GLboolean flag)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDepthMask);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDepthRangef (GLfloat n, GLfloat f)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDepthRangef);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDetachShader (GLuint program, GLuint shader)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDetachShader);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDisable (GLenum cap)
{
    logd("glDisable(%x)", cap);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDisable);
    cmd.push(cap);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDisableVertexAttribArray (GLuint index)
{
    logd("glDisableVertexAttribArray(%d)", index);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDisableVertexAttribArray);
    cmd.push(index);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glDrawArrays);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const void *indices)
{
    logd("glDrawElements(%x, %d, %x, %p)", mode, count, type, indices);

    BEGIN_GLES2_FUNCTION;
    if (context->elementArrayBuffer > 0) {
        cmd.push(CommandBuffer::CMD_glDrawElements_IBO);
        cmd.push(mode);
        cmd.push(count);
        cmd.push(type);
        cmd.push(uint64_t(indices));
    } else {
        assert(false);
    }
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glEnable (GLenum cap)
{
    logd("glEnable(%x)", cap);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glEnable);
    cmd.push(cap);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glEnableVertexAttribArray (GLuint index)
{
    logd("glEnableVertexAttribArray(%d)", index);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glEnableVertexAttribArray);
    cmd.push(index);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glFinish (void)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glFinish);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glFlush (void)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glFlush);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glFramebufferRenderbuffer);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glFramebufferTexture2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glFrontFace (GLenum mode)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glFrontFace);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers)
{
    logd("%s(%d, ..)", __func__, n);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glGenBuffers);
    cmd.push(n);
    context->syncServerReply(CommandBuffer::CMD_Reply_glGenBuffers, n, buffers);

    logd(" -> [0]: %d", *buffers);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGenerateMipmap (GLenum target)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGenerateMipmap);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGenFramebuffers);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGenRenderbuffers);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGenTextures);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetActiveAttrib);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetActiveUniform);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetAttachedShaders);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL GLint GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar *name)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetAttribLocation);
    END_GLES2_FUNCTION;
    return 0;
}

extern "C" GL_APICALL void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *data)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetBooleanv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetBufferParameteriv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL GLenum GL_APIENTRY glGetError (void)
{
    logd("glGetError()");

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glGetError);

    GLenum reply;
    context->syncServerReply(CommandBuffer::CMD_Reply_glGetError, &reply);
    logd(" -> %x", reply);

    END_GLES2_FUNCTION;

    return reply;
}

extern "C" GL_APICALL void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *data)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetFloatv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetFramebufferAttachmentParameteriv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetIntegerv (GLenum pname, GLint *data)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetIntegerv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params)
{
    logd("glGetProgramiv(%d, %x, ..)", program, pname);
    assert(params);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glGetProgramiv);
    cmd.push(program);
    cmd.push(pname);

    context->syncServerReply(CommandBuffer::CMD_Reply_glGetProgramiv, params);
    logd(" -> reply: %d", *params);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    logd("glGetProgramInfoLog(%d, %d, %p, %p)", program, bufSize, length, infoLog);
    assert(length);
    assert(infoLog);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glGetProgramInfoLog);
    cmd.push(program);
    cmd.push(bufSize);

    context->syncServerReply(CommandBuffer::CMD_Reply_glGetProgramInfoLog, bufSize, length, infoLog);
    logd(" -> string of length: %d\n%s", *length, infoLog);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params)
{
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetRenderbufferParameteriv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint *params)
{
    logd("glGetShaderiv(%d, %x, ..)", shader, pname);
    assert(params);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glGetShaderiv);
    cmd.push(shader);
    cmd.push(pname);

    context->syncServerReply(CommandBuffer::CMD_Reply_glGetShaderiv, params);
    logd(" -> reply: %d", *params);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    logd("glGetShaderInfoLog(%d, %d, %p, %p)", shader, bufSize, length, infoLog);
    assert(length);
    assert(infoLog);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glGetShaderInfoLog);
    cmd.push(shader);
    cmd.push(bufSize);

    context->syncServerReply(CommandBuffer::CMD_Reply_glGetShaderInfoLog, bufSize, length, infoLog);
    logd(" -> string of length: %d\n%s", *length, infoLog);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetShaderPrecisionFormat);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetShaderSource);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL const GLubyte *GL_APIENTRY glGetString (GLenum name)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetString);
    END_GLES2_FUNCTION;
    return 0;
}

extern "C" GL_APICALL void GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetTexParameterfv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetTexParameteriv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetUniformfv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetUniformiv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL GLint GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar *name)
{
    logd("glGetUniformLocation(%d, '%s')", program, name);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetUniformLocation);
    cmd.push(program);
    cmd.push(name, strlen(name));

    GLint location;
    context->syncServerReply(CommandBuffer::CMD_Reply_glGetUniformLocation, &location);

    END_GLES2_FUNCTION;

    return location;
}

extern "C" GL_APICALL void GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetVertexAttribfv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetVertexAttribiv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, void **pointer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glGetVertexAttribPointerv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glHint (GLenum target, GLenum mode)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glHint);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsBuffer (GLuint buffer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsBuffer);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsEnabled (GLenum cap)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsEnabled);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsFramebuffer (GLuint framebuffer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsFramebuffer);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsProgram (GLuint program)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsProgram);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsRenderbuffer);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsShader (GLuint shader)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsShader);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL GLboolean GL_APIENTRY glIsTexture (GLuint texture)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glIsTexture);
    END_GLES2_FUNCTION;
    return false;
}

extern "C" GL_APICALL void GL_APIENTRY glLineWidth (GLfloat width)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glLineWidth);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glLinkProgram (GLuint program)
{
    logd("%s(%d)", __func__, program);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glLinkProgram);
    cmd.push(program);

    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glPixelStorei (GLenum pname, GLint param)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glPixelStorei);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glPolygonOffset);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glReadPixels);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glReleaseShaderCompiler (void)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glReleaseShaderCompiler);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glRenderbufferStorage);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glSampleCoverage (GLfloat value, GLboolean invert)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glSampleCoverage);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glScissor);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glShaderBinary (GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glShaderBinary);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
{
    logd("glShaderSource(%d, %d, ..., %p)", shader, count, length);
    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glShaderSource);
    cmd.push(shader);
    cmd.push(count);
    for (int i=0; i<count; ++i)
        cmd.push(string[i], length ? length[i] : -1);
    END_GLES2_FUNCTION;
}


extern "C" GL_APICALL void GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glStencilFunc);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glStencilFuncSeparate);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glStencilMask (GLuint mask)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glStencilMask);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glStencilMaskSeparate);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glStencilOp);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glStencilOpSeparate);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glTexImage2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glTexParameterf);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glTexParameterfv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glTexParameteri);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glTexParameteriv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glTexSubImage2D);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform1f (GLint location, GLfloat v0)
{
    logd("glUniform1f(%d, %f)", location, v0);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform1f);
    cmd.push(location);
    cmd.push(v0);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform1fv (GLint location, GLsizei count, const GLfloat *value)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform1fv);
    cmd.push(location);
    cmd.push(value, count);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform1i (GLint location, GLint v0)
{
    logd("glUniform1i(%d, %d)", location, v0);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform1i);
    cmd.push(location);
    cmd.push(v0);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform1iv (GLint location, GLsizei count, const GLint *value)
{
    logd("glUniform1iv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform1iv);
    cmd.push(location);
    cmd.push(value, count);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform2f (GLint location, GLfloat v0, GLfloat v1)
{
    logd("glUniform2f(%d, %f, %f)", location, v0, v1);

    BEGIN_GLES2_FUNCTION;

    cmd.push(CommandBuffer::CMD_glUniform2f);
    cmd.push(location);
    cmd.push(v0);
    cmd.push(v1);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform2fv (GLint location, GLsizei count, const GLfloat *value)
{
    logd("glUniform2fv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform2fv);
    cmd.push(location);
    cmd.push(value, count * 2);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform2i (GLint location, GLint v0, GLint v1)
{
    logd("glUniform2i(%d, %d, %d)", location, v0, v1);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform2i);
    cmd.push(location);
    cmd.push(v0);
    cmd.push(v1);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform2iv (GLint location, GLsizei count, const GLint *value)
{
    logd("glUniform2iv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform2iv);
    cmd.push(location);
    cmd.push(value, count * 2);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    logd("glUniform3f(%d, %f, %f, %f)", location, v0, v1, v2);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform3f);
    cmd.push(location);
    cmd.push(v0);
    cmd.push(v1);
    cmd.push(v2);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform3fv (GLint location, GLsizei count, const GLfloat *value)
{
    logd("glUniform3fv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform3fv);
    cmd.push(location);
    cmd.push(value, count * 3);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform3i (GLint location, GLint v0, GLint v1, GLint v2)
{
    logd("glUniform3i(%d, %d, %d, %d)", location, v0, v1, v2);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform3i);
    cmd.push(location);
    cmd.push(v0);
    cmd.push(v1);
    cmd.push(v2);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform3iv (GLint location, GLsizei count, const GLint *value)
{
    logd("glUniform3iv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform3iv);
    cmd.push(location);
    cmd.push(value, count * 3);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    logd("glUniform4f(%d, %f, %f, %f, %f)", location, v0, v1, v2, v3);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform4f);
    cmd.push(location);
    cmd.push(v0);
    cmd.push(v1);
    cmd.push(v2);
    cmd.push(v3);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat *value)
{
    logd("glUniform4fv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform4fv);
    cmd.push(location);
    cmd.push(value, count * 4);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform4i (GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    logd("glUniform4i(%d, %d, %d, %d, %d)", location, v0, v1, v2, v3);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform4i);
    cmd.push(location);
    cmd.push(v0);
    cmd.push(v1);
    cmd.push(v2);
    cmd.push(v3);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniform4iv (GLint location, GLsizei count, const GLint *value)
{
    logd("glUniform4iv(%d, %d, %p)", location, count, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniform4iv);
    cmd.push(location);
    cmd.push(value, count * 4);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    logd("glUniformMatrix2fv(%d, %d, %d, %p)", location, count, transpose, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniformMatrix2fv);
    cmd.push(location);
    cmd.push(value, count * 4);
    cmd.push(transpose);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    logd("glUniformMatrix3fv(%d, %d, %d, %p)", location, count, transpose, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniformMatrix3fv);
    cmd.push(location);
    cmd.push(value, count * 9);
    cmd.push(transpose);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    logd("glUniformMatrix4fv(%d, %d, %d, %p)", location, count, transpose, value);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUniformMatrix4fv);
    cmd.push(location);
    cmd.push(value, count * 16);
    cmd.push(transpose);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glUseProgram (GLuint program)
{
    logd("glUseProgram(%d)", program);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glUseProgram);
    cmd.push(program);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glValidateProgram (GLuint program)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glValidateProgram);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib1f (GLuint index, GLfloat x)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib1f);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib1fv (GLuint index, const GLfloat *v)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib1fv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib2f (GLuint index, GLfloat x, GLfloat y)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib2f);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib2fv (GLuint index, const GLfloat *v)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib2fv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib3f (GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib3f);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib3fv (GLuint index, const GLfloat *v)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib3fv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib4f (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib4f);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttrib4fv (GLuint index, const GLfloat *v)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glVertexAttrib4fv);
    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glVertexAttribPointer (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;

    EGLSContextImpl::AttributePointer &p = context->attribPointers[index];
    p.size = size;
    p.type = type;
    p.normalized = normalized;
    p.stride = stride;
    p.pointer = pointer;

    // If we're in an array buffer,
    if (context->arrayBuffer) {
        cmd.push(CommandBuffer::CMD_glVertexAttribPointer_VBO);
        cmd.push(index);
        cmd.push(size);
        cmd.push(type);
        cmd.push(normalized);
        cmd.push(stride);
        cmd.push(uint64_t(pointer));
    }


    END_GLES2_FUNCTION;
}

extern "C" GL_APICALL void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
    logd("%s", __PRETTY_FUNCTION__);

    BEGIN_GLES2_FUNCTION;
    cmd.push(CommandBuffer::CMD_glViewport);
    END_GLES2_FUNCTION;
}


