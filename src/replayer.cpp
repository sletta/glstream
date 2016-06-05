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
            case CommandBuffer::CMD_glClearColor: {
                float r = cmd.pop<float>();
                float g = cmd.pop<float>();
                float b = cmd.pop<float>();
                float a = cmd.pop<float>();
                logd(" - glClearColor(%f, %f, %f, %f)\n", r, g, b, a);
                glClearColor(r, g, b, a);
            } break;

            case CommandBuffer::CMD_glClear: {
                GLbitfield mask = cmd.pop<GLbitfield>();
                logd(" - glClear(%x)\n", mask);
                glClear(mask);
            } break;

            case CommandBuffer::CMD_SwapBuffers: {
                logde(" - swap\n");
                swap();
            } break;

            default:
                logd(" - unknown command: %d\n", command);
                break;
        }
    }
}