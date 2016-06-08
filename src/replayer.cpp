#define GL_GLEXT_PROTOTYPES

#include "replayer.h"
#include "logging.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>

Replayer::Replayer()
{
}

void Replayer::process(const CommandBuffer &cmd)
{
    while (!cmd.atEnd()) {
        CommandBuffer::Command command = cmd.popCommand();
        switch (command) {
            case CommandBuffer::CMD_SwapBuffers: {
                logd(" - swap\n");
                swap();
            } break;

            case CommandBuffer::CMD_glActiveTexture: {
                logd(" - glActiveTexture\n");
            } break;

            case CommandBuffer::CMD_glAttachShader: {
                logd(" - glAttachShader\n");
            } break;

            case CommandBuffer::CMD_glBindAttribLocation: {
                logd(" - glBindAttribLocation\n");
            } break;

            case CommandBuffer::CMD_glBindBuffer: {
                logd(" - glBindBuffer\n");
            } break;

            case CommandBuffer::CMD_glBindFramebuffer: {
                logd(" - glBindFramebuffer\n");
            } break;

            case CommandBuffer::CMD_glBindRenderbuffer: {
                logd(" - glBindRenderbuffer\n");
            } break;

            case CommandBuffer::CMD_glBindTexture: {
                logd(" - glBindTexture\n");
            } break;

            case CommandBuffer::CMD_glBlendColor: {
                logd(" - glBlendColor\n");
            } break;

            case CommandBuffer::CMD_glBlendEquation: {
                logd(" - glBlendEquation\n");
            } break;

            case CommandBuffer::CMD_glBlendEquationSeparate: {
                logd(" - glBlendEquationSeparate\n");
            } break;

            case CommandBuffer::CMD_glBlendFunc: {
                logd(" - glBlendFunc\n");
            } break;

            case CommandBuffer::CMD_glBlendFuncSeparate: {
                logd(" - glBlendFuncSeparate\n");
            } break;

            case CommandBuffer::CMD_glBufferData: {
                logd(" - glBufferData\n");
            } break;

            case CommandBuffer::CMD_glBufferSubData: {
                logd(" - glBufferSubData\n");
            } break;

            case CommandBuffer::CMD_glCheckFramebufferStatus: {
                logd(" - glCheckFramebufferStatus\n");
            } break;

            case CommandBuffer::CMD_glClear: {
                GLbitfield mask = cmd.pop<GLbitfield>();
                logd(" - glClear(%x)\n", mask);
                glClear(mask);
            } break;

            case CommandBuffer::CMD_glClearColor: {
                float r = cmd.pop<float>();
                float g = cmd.pop<float>();
                float b = cmd.pop<float>();
                float a = cmd.pop<float>();
                logd(" - glClearColor(%f, %f, %f, %f)\n", r, g, b, a);
                glClearColor(r, g, b, a);
            } break;

            case CommandBuffer::CMD_glClearDepthf: {
                logd(" - glClearDepthf\n");
            } break;

            case CommandBuffer::CMD_glClearStencil: {
                logd(" - glClearStencil\n");
            } break;

            case CommandBuffer::CMD_glColorMask: {
                logd(" - glColorMask\n");
            } break;

            case CommandBuffer::CMD_glCompileShader: {
                GLuint cid = cmd.pop<GLuint>();
                GLuint id = m_shaders.find(cid, -1);
                logd(" - glCompileShader(%d->%d)\n", cid, id);
                glCompileShader(id);
            } break;

            case CommandBuffer::CMD_glCompressedTexImage2D: {
                logd(" - glCompressedTexImage2D\n");
            } break;

            case CommandBuffer::CMD_glCompressedTexSubImage2D: {
                logd(" - glCompressedTexSubImage2D\n");
            } break;

            case CommandBuffer::CMD_glCopyTexImage2D: {
                logd(" - glCopyTexImage2D\n");
            } break;

            case CommandBuffer::CMD_glCopyTexSubImage2D: {
                logd(" - glCopyTexSubImage2D\n");
            } break;

            case CommandBuffer::CMD_glCreateProgram: {
                logd(" - glCreateProgram\n");
            } break;

            case CommandBuffer::CMD_glCreateShader: {
                GLenum type = cmd.pop<GLenum>();
                GLuint cid = cmd.pop<GLuint>();
                GLuint sid = glCreateShader(type);
                m_shaders.insert(cid, sid);
                logd(" - glCreateShader(%x) -> clientId=%d, serverId=%d\n", type, cid, sid);

            } break;

            case CommandBuffer::CMD_glCullFace: {
                logd(" - glCullFace\n");
            } break;

            case CommandBuffer::CMD_glDeleteBuffers: {
                logd(" - glDeleteBuffers\n");
            } break;

            case CommandBuffer::CMD_glDeleteFramebuffers: {
                logd(" - glDeleteFramebuffers\n");
            } break;

            case CommandBuffer::CMD_glDeleteProgram: {
                logd(" - glDeleteProgram\n");
            } break;

            case CommandBuffer::CMD_glDeleteRenderbuffers: {
                logd(" - glDeleteRenderbuffers\n");
            } break;

            case CommandBuffer::CMD_glDeleteShader: {
                logd(" - glDeleteShader\n");
            } break;

            case CommandBuffer::CMD_glDeleteTextures: {
                logd(" - glDeleteTextures\n");
            } break;

            case CommandBuffer::CMD_glDepthFunc: {
                logd(" - glDepthFunc\n");
            } break;

            case CommandBuffer::CMD_glDepthMask: {
                logd(" - glDepthMask\n");
            } break;

            case CommandBuffer::CMD_glDepthRangef: {
                logd(" - glDepthRangef\n");
            } break;

            case CommandBuffer::CMD_glDetachShader: {
                logd(" - glDetachShader\n");
            } break;

            case CommandBuffer::CMD_glDisable: {
                logd(" - glDisable\n");
            } break;

            case CommandBuffer::CMD_glDisableVertexAttribArray: {
                logd(" - glDisableVertexAttribArray\n");
            } break;

            case CommandBuffer::CMD_glDrawArrays: {
                logd(" - glDrawArrays\n");
            } break;

            case CommandBuffer::CMD_glDrawElements: {
                logd(" - glDrawElements\n");
            } break;

            case CommandBuffer::CMD_glEnable: {
                logd(" - glEnable\n");
            } break;

            case CommandBuffer::CMD_glEnableVertexAttribArray: {
                logd(" - glEnableVertexAttribArray\n");
            } break;

            case CommandBuffer::CMD_glFinish: {
                logd(" - glFinish\n");
            } break;

            case CommandBuffer::CMD_glFlush: {
                logd(" - glFlush\n");
            } break;

            case CommandBuffer::CMD_glFramebufferRenderbuffer: {
                logd(" - glFramebufferRenderbuffer\n");
            } break;

            case CommandBuffer::CMD_glFramebufferTexture2D: {
                logd(" - glFramebufferTexture2D\n");
            } break;

            case CommandBuffer::CMD_glFrontFace: {
                logd(" - glFrontFace\n");
            } break;

            case CommandBuffer::CMD_glGenBuffers: {
                logd(" - glGenBuffers\n");
            } break;

            case CommandBuffer::CMD_glGenerateMipmap: {
                logd(" - glGenerateMipmap\n");
            } break;

            case CommandBuffer::CMD_glGenFramebuffers: {
                logd(" - glGenFramebuffers\n");
            } break;

            case CommandBuffer::CMD_glGenRenderbuffers: {
                logd(" - glGenRenderbuffers\n");
            } break;

            case CommandBuffer::CMD_glGenTextures: {
                logd(" - glGenTextures\n");
            } break;

            case CommandBuffer::CMD_glGetActiveAttrib: {
                logd(" - glGetActiveAttrib\n");
            } break;

            case CommandBuffer::CMD_glGetActiveUniform: {
                logd(" - glGetActiveUniform\n");
            } break;

            case CommandBuffer::CMD_glGetAttachedShaders: {
                logd(" - glGetAttachedShaders\n");
            } break;

            case CommandBuffer::CMD_glGetAttribLocation: {
                logd(" - glGetAttribLocation\n");
            } break;

            case CommandBuffer::CMD_glGetBooleanv: {
                logd(" - glGetBooleanv\n");
            } break;

            case CommandBuffer::CMD_glGetBufferParameteriv: {
                logd(" - glGetBufferParameteriv\n");
            } break;

            case CommandBuffer::CMD_glGetError: {
                logd(" - glGetError\n");
            } break;

            case CommandBuffer::CMD_glGetFloatv: {
                logd(" - glGetFloatv\n");
            } break;

            case CommandBuffer::CMD_glGetFramebufferAttachmentParameteriv: {
                logd(" - glGetFramebufferAttachmentParameteriv\n");
            } break;

            case CommandBuffer::CMD_glGetIntegerv: {
                logd(" - glGetIntegerv\n");
            } break;

            case CommandBuffer::CMD_glGetProgramiv: {
                logd(" - glGetProgramiv\n");
            } break;

            case CommandBuffer::CMD_glGetProgramInfoLog: {
                logd(" - glGetProgramInfoLog\n");
            } break;

            case CommandBuffer::CMD_glGetRenderbufferParameteriv: {
                logd(" - glGetRenderbufferParameteriv\n");
            } break;

            case CommandBuffer::CMD_glGetShaderiv: {
                GLuint cid = cmd.pop<GLuint>();
                GLuint id = m_shaders.find(cid, -1);
                GLenum param = cmd.pop<GLenum>();
                GLint result = 0;
                glGetShaderiv(id, param, &result);
                logd(" - glGetShaderiv(%d->%d, %x, %x)\n", cid, id, param, result);

                m_reply.add(CommandBuffer::CMD_Reply_glGetShaderiv, sizeof(GLint));
                m_reply.push(result);
                reply(m_reply);
                m_reply.reset();

            } break;

            case CommandBuffer::CMD_glGetShaderInfoLog: {
                logd(" - glGetShaderInfoLog\n");
            } break;

            case CommandBuffer::CMD_glGetShaderPrecisionFormat: {
                logd(" - glGetShaderPrecisionFormat\n");
            } break;

            case CommandBuffer::CMD_glGetShaderSource: {
                logd(" - glGetShaderSource\n");
            } break;

            case CommandBuffer::CMD_glGetString: {
                logd(" - glGetString\n");
            } break;

            case CommandBuffer::CMD_glGetTexParameterfv: {
                logd(" - glGetTexParameterfv\n");
            } break;

            case CommandBuffer::CMD_glGetTexParameteriv: {
                logd(" - glGetTexParameteriv\n");
            } break;

            case CommandBuffer::CMD_glGetUniformfv: {
                logd(" - glGetUniformfv\n");
            } break;

            case CommandBuffer::CMD_glGetUniformiv: {
                logd(" - glGetUniformiv\n");
            } break;

            case CommandBuffer::CMD_glGetUniformLocation: {
                logd(" - glGetUniformLocation\n");
            } break;

            case CommandBuffer::CMD_glGetVertexAttribfv: {
                logd(" - glGetVertexAttribfv\n");
            } break;

            case CommandBuffer::CMD_glGetVertexAttribiv: {
                logd(" - glGetVertexAttribiv\n");
            } break;

            case CommandBuffer::CMD_glGetVertexAttribPointerv: {
                logd(" - glGetVertexAttribPointerv\n");
            } break;

            case CommandBuffer::CMD_glHint: {
                logd(" - glHint\n");
            } break;

            case CommandBuffer::CMD_glIsBuffer: {
                logd(" - glIsBuffer\n");
            } break;

            case CommandBuffer::CMD_glIsEnabled: {
                logd(" - glIsEnabled\n");
            } break;

            case CommandBuffer::CMD_glIsFramebuffer: {
                logd(" - glIsFramebuffer\n");
            } break;

            case CommandBuffer::CMD_glIsProgram: {
                logd(" - glIsProgram\n");
            } break;

            case CommandBuffer::CMD_glIsRenderbuffer: {
                logd(" - glIsRenderbuffer\n");
            } break;

            case CommandBuffer::CMD_glIsShader: {
                logd(" - glIsShader\n");
            } break;

            case CommandBuffer::CMD_glIsTexture: {
                logd(" - glIsTexture\n");
            } break;

            case CommandBuffer::CMD_glLineWidth: {
                logd(" - glLineWidth\n");
            } break;

            case CommandBuffer::CMD_glLinkProgram: {
                logd(" - glLinkProgram\n");
            } break;

            case CommandBuffer::CMD_glPixelStorei: {
                logd(" - glPixelStorei\n");
            } break;

            case CommandBuffer::CMD_glPolygonOffset: {
                logd(" - glPolygonOffset\n");
            } break;

            case CommandBuffer::CMD_glReadPixels: {
                logd(" - glReadPixels\n");
            } break;

            case CommandBuffer::CMD_glReleaseShaderCompiler: {
                logd(" - glReleaseShaderCompiler\n");
            } break;

            case CommandBuffer::CMD_glRenderbufferStorage: {
                logd(" - glRenderbufferStorage\n");
            } break;

            case CommandBuffer::CMD_glSampleCoverage: {
                logd(" - glSampleCoverage\n");
            } break;

            case CommandBuffer::CMD_glScissor: {
                logd(" - glScissor\n");
            } break;

            case CommandBuffer::CMD_glShaderBinary: {
                logd(" - glShaderBinary\n");
            } break;

            case CommandBuffer::CMD_glShaderSource: {
                GLuint cid = cmd.pop<GLuint>();
                GLuint id = m_shaders.find(cid, -1);
                GLsizei count = cmd.pop<GLsizei>();
                logd(" - glShaderSource(%d->%d, count=%d)\n", cid, id, count);
                std::vector<const GLchar *> strings;
                std::vector<GLint> lengths;
                for (int i=0; i<count; ++i) {
                    int l = cmd.pop<GLint>();
                    strings.push_back((const GLchar *) cmd.raw());
                    logd("\n%s\n", strings.back());
                    cmd.advance(l);
                }
                glShaderSource(id, count, strings.data(), lengths.data());
            } break;

            case CommandBuffer::CMD_glStencilFunc: {
                logd(" - glStencilFunc\n");
            } break;

            case CommandBuffer::CMD_glStencilFuncSeparate: {
                logd(" - glStencilFuncSeparate\n");
            } break;

            case CommandBuffer::CMD_glStencilMask: {
                logd(" - glStencilMask\n");
            } break;

            case CommandBuffer::CMD_glStencilMaskSeparate: {
                logd(" - glStencilMaskSeparate\n");
            } break;

            case CommandBuffer::CMD_glStencilOp: {
                logd(" - glStencilOp\n");
            } break;

            case CommandBuffer::CMD_glStencilOpSeparate: {
                logd(" - glStencilOpSeparate\n");
            } break;

            case CommandBuffer::CMD_glTexImage2D: {
                logd(" - glTexImage2D\n");
            } break;

            case CommandBuffer::CMD_glTexParameterf: {
                logd(" - glTexParameterf\n");
            } break;

            case CommandBuffer::CMD_glTexParameterfv: {
                logd(" - glTexParameterfv\n");
            } break;

            case CommandBuffer::CMD_glTexParameteri: {
                logd(" - glTexParameteri\n");
            } break;

            case CommandBuffer::CMD_glTexParameteriv: {
                logd(" - glTexParameteriv\n");
            } break;

            case CommandBuffer::CMD_glTexSubImage2D: {
                logd(" - glTexSubImage2D\n");
            } break;

            case CommandBuffer::CMD_glUniform1f: {
                logd(" - glUniform1f\n");
            } break;

            case CommandBuffer::CMD_glUniform1fv: {
                logd(" - glUniform1fv\n");
            } break;

            case CommandBuffer::CMD_glUniform1i: {
                logd(" - glUniform1i\n");
            } break;

            case CommandBuffer::CMD_glUniform1iv: {
                logd(" - glUniform1iv\n");
            } break;

            case CommandBuffer::CMD_glUniform2f: {
                logd(" - glUniform2f\n");
            } break;

            case CommandBuffer::CMD_glUniform2fv: {
                logd(" - glUniform2fv\n");
            } break;

            case CommandBuffer::CMD_glUniform2i: {
                logd(" - glUniform2i\n");
            } break;

            case CommandBuffer::CMD_glUniform2iv: {
                logd(" - glUniform2iv\n");
            } break;

            case CommandBuffer::CMD_glUniform3f: {
                logd(" - glUniform3f\n");
            } break;

            case CommandBuffer::CMD_glUniform3fv: {
                logd(" - glUniform3fv\n");
            } break;

            case CommandBuffer::CMD_glUniform3i: {
                logd(" - glUniform3i\n");
            } break;

            case CommandBuffer::CMD_glUniform3iv: {
                logd(" - glUniform3iv\n");
            } break;

            case CommandBuffer::CMD_glUniform4f: {
                logd(" - glUniform4f\n");
            } break;

            case CommandBuffer::CMD_glUniform4fv: {
                logd(" - glUniform4fv\n");
            } break;

            case CommandBuffer::CMD_glUniform4i: {
                logd(" - glUniform4i\n");
            } break;

            case CommandBuffer::CMD_glUniform4iv: {
                logd(" - glUniform4iv\n");
            } break;

            case CommandBuffer::CMD_glUniformMatrix2fv: {
                logd(" - glUniformMatrix2fv\n");
            } break;

            case CommandBuffer::CMD_glUniformMatrix3fv: {
                logd(" - glUniformMatrix3fv\n");
            } break;

            case CommandBuffer::CMD_glUniformMatrix4fv: {
                logd(" - glUniformMatrix4fv\n");
            } break;

            case CommandBuffer::CMD_glUseProgram: {
                logd(" - glUseProgram\n");
            } break;

            case CommandBuffer::CMD_glValidateProgram: {
                logd(" - glValidateProgram\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib1f: {
                logd(" - glVertexAttrib1f\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib1fv: {
                logd(" - glVertexAttrib1fv\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib2f: {
                logd(" - glVertexAttrib2f\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib2fv: {
                logd(" - glVertexAttrib2fv\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib3f: {
                logd(" - glVertexAttrib3f\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib3fv: {
                logd(" - glVertexAttrib3fv\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib4f: {
                logd(" - glVertexAttrib4f\n");
            } break;

            case CommandBuffer::CMD_glVertexAttrib4fv: {
                logd(" - glVertexAttrib4fv\n");
            } break;

            case CommandBuffer::CMD_glVertexAttribPointer: {
                logd(" - glVertexAttribPointer\n");
            } break;

            case CommandBuffer::CMD_glViewport: {
                logd(" - glViewport\n");
            } break;

            default:
                logd(" - unknown command: %d\n", command);
                break;
        }
    }
}