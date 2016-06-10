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

#include "transport.h"
#include "commandbuffer.h"
#include "replayer.h"

#include <unistd.h>

#include <GLFW/glfw3.h>

#include "logging.h"

class Server : public Replayer
{
public:
    Server();
    ~Server();

    void swap();
    void run();
    void reply(const CommandBuffer &cmd);

    Transport *transport() const { return m_transport; }

private:
    GLFWwindow *m_window = 0;
    Transport *m_transport = 0;
    CommandBuffer m_cmds;
    CommandBuffer m_ackBuffer;
};



int main(int argc, char **argv)
{
    if (!glfwInit()) {
        logw("GLFW init failed..\n");
        return 0;
    }

    Server server;
    if (!server.transport()) {
        logw("failed to set up connections...\n");
        return 0;
    }

    server.run();

    glfwTerminate();

    return 0;
}


Server::Server()
{
    logd("Creating GLFW Window..\n");
    m_window = glfwCreateWindow(640, 480, "ExampleServer", nullptr, nullptr);

    logd("Server setting up socket..\n");
    m_transport = Transport::createServer(".glstream.socket");

    m_ackBuffer.add(CommandBuffer::CMD_SwapBuffers);

}

Server::~Server()
{
    glfwDestroyWindow(m_window);
}

void Server::run()
{
    logd("Server is now running\n");
    glfwMakeContextCurrent(m_window);

    while (!glfwWindowShouldClose(m_window))
    {
        logd(" - read another command buffer...\n");
        m_cmds.reset();
        int bytesRead = m_transport->read(&m_cmds);
        if (bytesRead == 0) {
            logw("failed to read a blob...\n");
            return;
        }

        printf("Command buffer is %d bytes\n", bytesRead);
        int counter = 0;
        for (int i=0; i<bytesRead; ++i) {
            printf(" 0x%02x", m_cmds.rawAtStart()[i]);
            if ((++counter) % 16 == 0 || i == bytesRead - 1)
                printf("\n");
        }

        logd(" - processing command buffer\n");
        process(m_cmds);

        glfwPollEvents();
    }
}

void Server::swap()
{
    // send back that we consumed the buffer..
    m_transport->write(m_ackBuffer);
    glfwSwapBuffers(m_window);
}

void Server::reply(const CommandBuffer &cmd)
{
    logd(" - sending reply in the middle of rendering, %d bytes\n", cmd.position());
    m_transport->write(cmd);
}