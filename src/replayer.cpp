#define GL_GLEXT_PROTOTYPES

#define GLSTREAM_LOGGING_CONTEXT "glreplay"

#include "replayer.h"
#include "logging.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <cstring>

#include <alloca.h>

#define CMDPOP(Type, Name) Type Name = cmd.pop<Type>()

Replayer::Replayer()
{
}

void Replayer::process(const CommandBuffer &cmd)
{
    while (!cmd.atEnd()) {
        CommandBuffer::Command command = cmd.popCommand();
        switch (command) {
            case CommandBuffer::CMD_SwapBuffers: {
                logd("swap");
                swap();
            } break;

            case CommandBuffer::CMD_glActiveTexture: {
                logd("glActiveTexture");
            } break;

            case CommandBuffer::CMD_glAttachShader: {
                GLuint program = cmd.pop<GLuint>();
                GLuint shader = cmd.pop<GLuint>();
                logd("glAttachShader(%d, %d)", program, shader);
                glAttachShader(program, shader);
            } break;

            case CommandBuffer::CMD_glBindAttribLocation: {
                GLuint program = cmd.pop<GLuint>();
                GLuint index = cmd.pop<GLuint>();
                std::string name = cmd.popStdString();
                logd("glBindAttribLocation(%d, %d, \"%s\")", program, index, name.c_str());
                glBindAttribLocation(program, index, name.c_str());
            } break;

            case CommandBuffer::CMD_glBindBuffer: {
                GLenum type = cmd.pop<GLenum>();
                GLuint id = cmd.pop<GLuint>();
                logd("glBindBuffer(%x, %d)", type, id);

                glBindBuffer(type, id);

            } break;

            case CommandBuffer::CMD_glBindFramebuffer: {
                logd("glBindFramebuffer");
            } break;

            case CommandBuffer::CMD_glBindRenderbuffer: {
                logd("glBindRenderbuffer");
            } break;

            case CommandBuffer::CMD_glBindTexture: {
                logd("glBindTexture");
            } break;

            case CommandBuffer::CMD_glBlendColor: {
                logd("glBlendColor");
            } break;

            case CommandBuffer::CMD_glBlendEquation: {
                logd("glBlendEquation");
            } break;

            case CommandBuffer::CMD_glBlendEquationSeparate: {
                logd("glBlendEquationSeparate");
            } break;

            case CommandBuffer::CMD_glBlendFunc: {
                logd("glBlendFunc");
            } break;

            case CommandBuffer::CMD_glBlendFuncSeparate: {
                logd("glBlendFuncSeparate");
            } break;

            case CommandBuffer::CMD_glBufferData: {
                GLenum type = cmd.pop<GLenum>();
                char *data;
                GLsizei size = cmd.popArray(&data);
                GLenum usage = cmd.pop<GLenum>();
                logd("glBufferData(%x, %d, .., %x)", type, size, usage);

                if (type == GL_ELEMENT_ARRAY_BUFFER)
                    for (int i=0; i<4; ++i)
                        printf(" - [%d]: %d\n", i, ((GLushort *) data)[i]);
                else
                    for (int i=0; i<8; ++i)
                        printf(" - [%d]: %f\n", i, ((GLfloat *) data)[i]);


                glBufferData(type, size, data, usage);
            } break;

            case CommandBuffer::CMD_glBufferSubData: {
                logd("glBufferSubData");
            } break;

            case CommandBuffer::CMD_glCheckFramebufferStatus: {
                logd("glCheckFramebufferStatus");
            } break;

            case CommandBuffer::CMD_glClear: {
                GLbitfield mask = cmd.pop<GLbitfield>();
                logd("glClear(%x)", mask);
                glClear(mask);
            } break;

            case CommandBuffer::CMD_glClearColor: {
                float r = cmd.pop<float>();
                float g = cmd.pop<float>();
                float b = cmd.pop<float>();
                float a = cmd.pop<float>();
                logd("glClearColor(%f, %f, %f, %f)", r, g, b, a);
                glClearColor(r, g, b, a);
            } break;

            case CommandBuffer::CMD_glClearDepthf: {
                logd("glClearDepthf");
            } break;

            case CommandBuffer::CMD_glClearStencil: {
                logd("glClearStencil");
            } break;

            case CommandBuffer::CMD_glColorMask: {
                logd("glColorMask");
            } break;

            case CommandBuffer::CMD_glCompileShader: {
                GLuint shader = cmd.pop<GLuint>();
                logd("glCompileShader(%d)", shader);
                glCompileShader(shader);
            } break;

            case CommandBuffer::CMD_glCompressedTexImage2D: {
                logd("glCompressedTexImage2D");
            } break;

            case CommandBuffer::CMD_glCompressedTexSubImage2D: {
                logd("glCompressedTexSubImage2D");
            } break;

            case CommandBuffer::CMD_glCopyTexImage2D: {
                logd("glCopyTexImage2D");
            } break;

            case CommandBuffer::CMD_glCopyTexSubImage2D: {
                logd("glCopyTexSubImage2D");
            } break;

            case CommandBuffer::CMD_glCreateProgram: {
                logd("glCreateProgram()");
                GLuint id = glCreateProgram();
                logd("   -> %d", id);
                sendReply(CommandBuffer::CMD_Reply_glCreateProgram, id);

            } break;

            case CommandBuffer::CMD_glCreateShader: {
                GLenum type = cmd.pop<GLenum>();
                logd("glCreateShader(%x)", type);
                GLuint id = glCreateShader(type);
                logd("   -> %d", id);
                sendReply(CommandBuffer::CMD_Reply_glCreateShader, id);

            } break;

            case CommandBuffer::CMD_glCullFace: {
                logd("glCullFace");
            } break;

            case CommandBuffer::CMD_glDeleteBuffers: {
                logd("glDeleteBuffers");
            } break;

            case CommandBuffer::CMD_glDeleteFramebuffers: {
                logd("glDeleteFramebuffers");
            } break;

            case CommandBuffer::CMD_glDeleteProgram: {
                logd("glDeleteProgram");
            } break;

            case CommandBuffer::CMD_glDeleteRenderbuffers: {
                logd("glDeleteRenderbuffers");
            } break;

            case CommandBuffer::CMD_glDeleteShader: {
                logd("glDeleteShader");
            } break;

            case CommandBuffer::CMD_glDeleteTextures: {
                logd("glDeleteTextures");
            } break;

            case CommandBuffer::CMD_glDepthFunc: {
                logd("glDepthFunc");
            } break;

            case CommandBuffer::CMD_glDepthMask: {
                logd("glDepthMask");
            } break;

            case CommandBuffer::CMD_glDepthRangef: {
                logd("glDepthRangef");
            } break;

            case CommandBuffer::CMD_glDetachShader: {
                logd("glDetachShader");
            } break;

            case CommandBuffer::CMD_glDisable: {
                GLenum cap = cmd.pop<GLenum>();
                logd("glDisable(%x)", cap);
                glDisable(cap);
            } break;

            case CommandBuffer::CMD_glDisableVertexAttribArray: {
                GLuint id = cmd.pop<GLuint>();
                logd("glDisableVertexAttribArray(%d)", id);
                glDisableVertexAttribArray(id);
            } break;

            case CommandBuffer::CMD_glDrawArrays: {
                logd("glDrawArrays");
            } break;

            case CommandBuffer::CMD_glDrawElements_IBO: {

                CMDPOP(GLenum, mode);
                CMDPOP(GLsizei, count);
                CMDPOP(GLenum, type);
                CMDPOP(uint64_t, indices);

                logd("glDrawElements(%x, %d, %x, %p) (IBO)", mode, count, type, (void *) indices);

                glDrawElements(mode, count, type, (void *) indices);

            } break;

            case CommandBuffer::CMD_glDrawElements: {
                logd("glDrawElements");
            } break;

            case CommandBuffer::CMD_glEnable: {
                GLenum cap = cmd.pop<GLenum>();
                logd("glEnable(%x)", cap);
                glEnable(cap);
            } break;

            case CommandBuffer::CMD_glEnableVertexAttribArray: {
                GLuint id = cmd.pop<GLuint>();
                logd("glEnableVertexAttribArray(%d)", id);
                glEnableVertexAttribArray(id);
            } break;

            case CommandBuffer::CMD_glFinish: {
                logd("glFinish");
                glFinish();
            } break;

            case CommandBuffer::CMD_glFlush: {
                logd("glFlush");
                glFlush();
            } break;

            case CommandBuffer::CMD_glFramebufferRenderbuffer: {
                logd("glFramebufferRenderbuffer");
            } break;

            case CommandBuffer::CMD_glFramebufferTexture2D: {
                logd("glFramebufferTexture2D");
            } break;

            case CommandBuffer::CMD_glFrontFace: {
                logd("glFrontFace");
            } break;

            case CommandBuffer::CMD_glGenBuffers: {
                GLsizei count = cmd.pop<GLsizei>();
                logd("glGenBuffers(%d)", count);

                GLuint *buffers = (GLuint *) alloca(count * sizeof(GLuint));
                glGenBuffers(count, buffers);

#ifdef GLSTREAM_LOGGING
                for (int i=0; i<count; ++i)
                    logd(" -> %d", buffers[i]);
#endif

                sendReply(CommandBuffer::CMD_Reply_glGenBuffers, buffers, count);
            } break;

            case CommandBuffer::CMD_glGenerateMipmap: {
                logd("glGenerateMipmap");
            } break;

            case CommandBuffer::CMD_glGenFramebuffers: {
                logd("glGenFramebuffers");
            } break;

            case CommandBuffer::CMD_glGenRenderbuffers: {
                logd("glGenRenderbuffers");
            } break;

            case CommandBuffer::CMD_glGenTextures: {
                logd("glGenTextures");
            } break;

            case CommandBuffer::CMD_glGetActiveAttrib: {
                logd("glGetActiveAttrib");
            } break;

            case CommandBuffer::CMD_glGetActiveUniform: {
                logd("glGetActiveUniform");
            } break;

            case CommandBuffer::CMD_glGetAttachedShaders: {
                logd("glGetAttachedShaders");
            } break;

            case CommandBuffer::CMD_glGetAttribLocation: {
                logd("glGetAttribLocation");
            } break;

            case CommandBuffer::CMD_glGetBooleanv: {
                logd("glGetBooleanv");
            } break;

            case CommandBuffer::CMD_glGetBufferParameteriv: {
                logd("glGetBufferParameteriv");
            } break;

            case CommandBuffer::CMD_glGetError: {
                logd("glGetError()");

                GLenum error = glGetError();
                logd(" -> %x", error);

                sendReply(CommandBuffer::CMD_Reply_glGetError, error);

            } break;

            case CommandBuffer::CMD_glGetFloatv: {
                logd("glGetFloatv");
            } break;

            case CommandBuffer::CMD_glGetFramebufferAttachmentParameteriv: {
                logd("glGetFramebufferAttachmentParameteriv");
            } break;

            case CommandBuffer::CMD_glGetIntegerv: {
                logd("glGetIntegerv");
            } break;

            case CommandBuffer::CMD_glGetProgramiv: {
                GLuint id = cmd.pop<GLuint>();
                GLenum param = cmd.pop<GLenum>();
                logd("glGetProgramiv(%d, %x, ..)", id, param);

                GLint result = 0;
                glGetProgramiv(id, param, &result);
                logd("   -> %d", result);

                sendReply(CommandBuffer::CMD_Reply_glGetProgramiv, result);
            } break;

            case CommandBuffer::CMD_glGetProgramInfoLog: {
                GLuint id = cmd.pop<GLuint>();
                GLsizei size = cmd.pop<GLsizei>();
                logd("glGetProgramInfoLog(%d, %d):", id, size);

                GLchar *str = size == 0 ? nullptr : (GLchar *) alloca(size);
                GLsizei actualSize = 0;
                if (str) {
                    glGetProgramInfoLog(id, size, &actualSize, str);
                    logd(" -> %s", str);
                }

                sendReply(CommandBuffer::CMD_Reply_glGetProgramInfoLog, str, actualSize);

            } break;

            case CommandBuffer::CMD_glGetRenderbufferParameteriv: {
                logd("glGetRenderbufferParameteriv");
            } break;

            case CommandBuffer::CMD_glGetShaderiv: {
                GLuint id = cmd.pop<GLuint>();
                GLenum param = cmd.pop<GLenum>();
                GLint result = 0;
                glGetShaderiv(id, param, &result);
                logd("glGetShaderiv(%d, %x, %x)", id, param, result);

                sendReply(CommandBuffer::CMD_Reply_glGetShaderiv, result);

            } break;

            case CommandBuffer::CMD_glGetShaderInfoLog: {
                GLuint id = cmd.pop<GLuint>();
                GLsizei size = cmd.pop<GLsizei>();
                logd("glGetShaderInfoLog(%d, %d)", id, size);

                GLchar *str = size == 0 ? nullptr : (GLchar *) alloca(size);
                GLsizei actualSize;
                if (str) {
                    glGetShaderInfoLog(id, size, &actualSize, str);
                    logd(" -> %s", str);
                }

                sendReply(CommandBuffer::CMD_Reply_glGetShaderInfoLog, str, actualSize);

            } break;

            case CommandBuffer::CMD_glGetShaderPrecisionFormat: {
                logd("glGetShaderPrecisionFormat");
            } break;

            case CommandBuffer::CMD_glGetShaderSource: {
                logd("glGetShaderSource");
            } break;

            case CommandBuffer::CMD_glGetString: {
                logd("glGetString");
            } break;

            case CommandBuffer::CMD_glGetTexParameterfv: {
                logd("glGetTexParameterfv");
            } break;

            case CommandBuffer::CMD_glGetTexParameteriv: {
                logd("glGetTexParameteriv");
            } break;

            case CommandBuffer::CMD_glGetUniformfv: {
                logd("glGetUniformfv");
            } break;

            case CommandBuffer::CMD_glGetUniformiv: {
                logd("glGetUniformiv");
            } break;

            case CommandBuffer::CMD_glGetUniformLocation: {
                CMDPOP(GLuint, program);
                std::string name = cmd.popStdString();
                logd("glGetUniformLocation(%d, '%s')", program, name.c_str());
                GLint location = glGetUniformLocation(program, name.c_str());
                sendReply(CommandBuffer::CMD_Reply_glGetUniformLocation, location);
            } break;

            case CommandBuffer::CMD_glGetVertexAttribfv: {
                logd("glGetVertexAttribfv");
            } break;

            case CommandBuffer::CMD_glGetVertexAttribiv: {
                logd("glGetVertexAttribiv");
            } break;

            case CommandBuffer::CMD_glGetVertexAttribPointerv: {
                logd("glGetVertexAttribPointerv");
            } break;

            case CommandBuffer::CMD_glHint: {
                logd("glHint");
            } break;

            case CommandBuffer::CMD_glIsBuffer: {
                logd("glIsBuffer");
            } break;

            case CommandBuffer::CMD_glIsEnabled: {
                logd("glIsEnabled");
            } break;

            case CommandBuffer::CMD_glIsFramebuffer: {
                logd("glIsFramebuffer");
            } break;

            case CommandBuffer::CMD_glIsProgram: {
                logd("glIsProgram");
            } break;

            case CommandBuffer::CMD_glIsRenderbuffer: {
                logd("glIsRenderbuffer");
            } break;

            case CommandBuffer::CMD_glIsShader: {
                logd("glIsShader");
            } break;

            case CommandBuffer::CMD_glIsTexture: {
                logd("glIsTexture");
            } break;

            case CommandBuffer::CMD_glLineWidth: {
                logd("glLineWidth");
            } break;

            case CommandBuffer::CMD_glLinkProgram: {
                GLuint id = cmd.pop<GLuint>();
                logd("glLinkProgram(%d)", id);
                glLinkProgram(id);
            } break;

            case CommandBuffer::CMD_glPixelStorei: {
                logd("glPixelStorei");
            } break;

            case CommandBuffer::CMD_glPolygonOffset: {
                logd("glPolygonOffset");
            } break;

            case CommandBuffer::CMD_glReadPixels: {
                logd("glReadPixels");
            } break;

            case CommandBuffer::CMD_glReleaseShaderCompiler: {
                logd("glReleaseShaderCompiler");
            } break;

            case CommandBuffer::CMD_glRenderbufferStorage: {
                logd("glRenderbufferStorage");
            } break;

            case CommandBuffer::CMD_glSampleCoverage: {
                logd("glSampleCoverage");
            } break;

            case CommandBuffer::CMD_glScissor: {
                logd("glScissor");
            } break;

            case CommandBuffer::CMD_glShaderBinary: {
                logd("glShaderBinary");
            } break;

            case CommandBuffer::CMD_glShaderSource: {
                GLuint id = cmd.pop<GLuint>();
                GLsizei count = cmd.pop<GLsizei>();
                logd("glShaderSource(%d, count=%d)", id, count);

                std::vector<const GLchar *> strings;
                std::vector<GLint> lengths;
                for (int i=0; i<count; ++i) {
                    int l = cmd.pop<GLint>();
                    lengths.push_back(l);
                    strings.push_back((const GLchar *) cmd.rawAtPosition());
                    logd("%s\n", strings.back());
                    cmd.advance(l);
                }

                glShaderSource(id, count, strings.data(), lengths.data());
            } break;

            case CommandBuffer::CMD_glStencilFunc: {
                logd("glStencilFunc");
            } break;

            case CommandBuffer::CMD_glStencilFuncSeparate: {
                logd("glStencilFuncSeparate");
            } break;

            case CommandBuffer::CMD_glStencilMask: {
                logd("glStencilMask");
            } break;

            case CommandBuffer::CMD_glStencilMaskSeparate: {
                logd("glStencilMaskSeparate");
            } break;

            case CommandBuffer::CMD_glStencilOp: {
                logd("glStencilOp");
            } break;

            case CommandBuffer::CMD_glStencilOpSeparate: {
                logd("glStencilOpSeparate");
            } break;

            case CommandBuffer::CMD_glTexImage2D: {
                logd("glTexImage2D");
            } break;

            case CommandBuffer::CMD_glTexParameterf: {
                logd("glTexParameterf");
            } break;

            case CommandBuffer::CMD_glTexParameterfv: {
                logd("glTexParameterfv");
            } break;

            case CommandBuffer::CMD_glTexParameteri: {
                logd("glTexParameteri");
            } break;

            case CommandBuffer::CMD_glTexParameteriv: {
                logd("glTexParameteriv");
            } break;

            case CommandBuffer::CMD_glTexSubImage2D: {
                logd("glTexSubImage2D");
            } break;

            case CommandBuffer::CMD_glUniform1f: {
                CMDPOP(GLint, location);
                CMDPOP(GLfloat, v0);
                logd("glUniform1f(%d, %f)", location, v0);
                glUniform1f(location, v0);
            } break;

            case CommandBuffer::CMD_glUniform1fv: {
                CMDPOP(GLint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform1fv(%d, %d, %p)", location, size, values);
                glUniform1fv(location, size, values);
            } break;

            case CommandBuffer::CMD_glUniform1i: {
                CMDPOP(GLint, location);
                CMDPOP(GLint, v0);
                logd("glUniform1i(%d, %d)", location, v0);
                glUniform1i(location, v0);
            } break;

            case CommandBuffer::CMD_glUniform1iv: {
                CMDPOP(GLint, location);
                GLint *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform1iv(%d, %d, %p)", location, size, values);
                glUniform1iv(location, size, values);
            } break;

            case CommandBuffer::CMD_glUniform2f: {
                CMDPOP(GLint, location);
                CMDPOP(GLfloat, v0);
                CMDPOP(GLfloat, v1);
                logd("glUniform2f(%d, %f, %f)", location, v0, v1);
                glUniform2f(location, v0, v1);
            } break;

            case CommandBuffer::CMD_glUniform2fv: {
                CMDPOP(GLint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform2fv(%d, %d, %p)", location, size / 2, values);
                glUniform2fv(location, size / 2, values);
            } break;

            case CommandBuffer::CMD_glUniform2i: {
                CMDPOP(GLint, location);
                CMDPOP(GLint, v0);
                CMDPOP(GLint, v1);
                logd("glUniform2i(%d, %d, %d)", location, v0, v1);
                glUniform2i(location, v0, v1);
            } break;

            case CommandBuffer::CMD_glUniform2iv: {
                CMDPOP(GLint, location);
                GLint *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform2iv(%d, %d, %p)", location, size / 2, values);
                glUniform2iv(location, size / 2, values);
            } break;

            case CommandBuffer::CMD_glUniform3f: {
                CMDPOP(GLint, location);
                CMDPOP(GLfloat, v0);
                CMDPOP(GLfloat, v1);
                CMDPOP(GLfloat, v2);
                logd("glUniform3f(%d, %f, %f, %f)", location, v0, v1, v2);
                glUniform3f(location, v0, v1, v2);
            } break;

            case CommandBuffer::CMD_glUniform3fv: {
                CMDPOP(GLint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform3fv(%d, %d, %p)", location, size / 3, values);
                glUniform3fv(location, size / 3, values);
            } break;

            case CommandBuffer::CMD_glUniform3i: {
                CMDPOP(GLint, location);
                CMDPOP(GLint, v0);
                CMDPOP(GLint, v1);
                CMDPOP(GLint, v2);
                logd("glUniform3i(%d, %d, %d, %d)", location, v0, v1, v2);
                glUniform3i(location, v0, v1, v2);
            } break;

            case CommandBuffer::CMD_glUniform3iv: {
                CMDPOP(GLint, location);
                GLint *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform3iv(%d, %d, %p)", location, size / 3, values);
                glUniform3iv(location, size / 3, values);
            } break;

            case CommandBuffer::CMD_glUniform4f: {
                CMDPOP(GLint, location);
                CMDPOP(GLfloat, v0);
                CMDPOP(GLfloat, v1);
                CMDPOP(GLfloat, v2);
                CMDPOP(GLfloat, v3);
                logd("glUniform4f(%d, %f, %f, %f, %f)", location, v0, v1, v2, v3);
                glUniform4f(location, v0, v1, v2, v3);
            } break;

            case CommandBuffer::CMD_glUniform4fv: {
                CMDPOP(GLint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform4fv(%d, %d, %p)", location, size / 4, values);
                glUniform4fv(location, size / 4, values);
            } break;

            case CommandBuffer::CMD_glUniform4i: {
                CMDPOP(GLint, location);
                CMDPOP(GLint, v0);
                CMDPOP(GLint, v1);
                CMDPOP(GLint, v2);
                CMDPOP(GLint, v3);
                logd("glUniform4i(%d, %d, %d, %d, %d)", location, v0, v1, v2, v3);
                glUniform4i(location, v0, v1, v2, v3);
            } break;

            case CommandBuffer::CMD_glUniform4iv: {
                CMDPOP(GLint, location);
                GLint *values;
                unsigned int size = cmd.popArray(&values);
                logd("glUniform4iv(%d, %d, %p)", location, size / 4, values);
                glUniform4iv(location, size / 4, values);
            } break;

            case CommandBuffer::CMD_glUniformMatrix2fv: {
                CMDPOP(GLuint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                CMDPOP(GLboolean, transpose);
                logd("glUniformMatrix2fv(%d, %d, %d, %p)", location, size / 4, transpose, values);
                glUniformMatrix2fv(location, size / 4, transpose, values);
            } break;

            case CommandBuffer::CMD_glUniformMatrix3fv: {
                CMDPOP(GLuint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                CMDPOP(GLboolean, transpose);
                logd("glUniformMatrix3fv(%d, %d, %d, %p)", location, size / 9, transpose, values);
                glUniformMatrix3fv(location, size / 9, transpose, values);
            } break;

            case CommandBuffer::CMD_glUniformMatrix4fv: {
                CMDPOP(GLuint, location);
                GLfloat *values;
                unsigned int size = cmd.popArray(&values);
                CMDPOP(GLboolean, transpose);
                logd("glUniformMatrix4fv(%d, %d, %d, %p)", location, size / 16, transpose, values);
                glUniformMatrix4fv(location, size / 16, transpose, values);
            } break;

            case CommandBuffer::CMD_glUseProgram: {
                CMDPOP(GLuint, program);
                logd("glUseProgram(%d)", program);
                glUseProgram(program);
            } break;

            case CommandBuffer::CMD_glValidateProgram: {
                logd("glValidateProgram");
            } break;

            case CommandBuffer::CMD_glVertexAttrib1f: {
                logd("glVertexAttrib1f");
            } break;

            case CommandBuffer::CMD_glVertexAttrib1fv: {
                logd("glVertexAttrib1fv");
            } break;

            case CommandBuffer::CMD_glVertexAttrib2f: {
                logd("glVertexAttrib2f");
            } break;

            case CommandBuffer::CMD_glVertexAttrib2fv: {
                logd("glVertexAttrib2fv");
            } break;

            case CommandBuffer::CMD_glVertexAttrib3f: {
                logd("glVertexAttrib3f");
            } break;

            case CommandBuffer::CMD_glVertexAttrib3fv: {
                logd("glVertexAttrib3fv");
            } break;

            case CommandBuffer::CMD_glVertexAttrib4f: {
                logd("glVertexAttrib4f");
            } break;

            case CommandBuffer::CMD_glVertexAttrib4fv: {
                logd("glVertexAttrib4fv");
            } break;

            case CommandBuffer::CMD_glVertexAttribPointer_VBO: {
                CMDPOP(GLuint, index);
                CMDPOP(GLint, size);
                CMDPOP(GLenum, type);
                CMDPOP(GLboolean, normalized);
                CMDPOP(GLsizei, stride);
                CMDPOP(uint64_t, pointer);
                logd("glVertexAttribPointer(%d, %d, %x, %d, %d, %p) (VBO)", index, size, type, normalized, stride, (void *) pointer);

                glVertexAttribPointer(index, size, type, normalized, stride, (void *) pointer);
            } break;

            case CommandBuffer::CMD_glViewport: {
                logd("glViewport");
            } break;

            default:
                logd("unknown command: %d", command);
                break;
        }
    }
}