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

#define GLSTREAM_LOGGING_CONTEXT "netw:uds"


#include "transport.h"
#include "logging.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

#include <memory>



class UnixDomainSocket : public Transport
{
public:
    UnixDomainSocket();

    static sockaddr_un transport_sockaddrForAddress(const char *address)
    {
        sockaddr_un addr;
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, address, sizeof(addr.sun_path)-1);
        return addr;
    }

    int read(CommandBuffer *buffer);
    int write(const CommandBuffer &buffer);

    int socket() const { return m_socket; }

    int m_socket = 0;
};



class ServerSocket : public UnixDomainSocket
{
public:
    ServerSocket();

    bool connect(const char *address);

    int m_serverSocket = 0;
};



class ClientSocket : public UnixDomainSocket
{
public:
    ClientSocket();

    bool connect(const char *address);
};



Transport *Transport::createServer(const char *address)
{
    std::unique_ptr<ServerSocket> server(new ServerSocket());
    unlink(address);

    if (!server->connect(address)) {
        logw("Transport: server failed to connect, socket=%d, serverSocket=%d, address=%s, error=%s",
             server->m_socket,
             server->m_serverSocket,
             address,
             strerror(errno));
        return nullptr;
    }

    logi("Transport: connection established with client, address=%s, socket=%d, serverSocket=%d",
         address,
         server->m_socket,
         server->m_serverSocket);

    return server.release();
}


Transport *Transport::createClient(const char *address)
{
    std::unique_ptr<ClientSocket> client(new ClientSocket());

    if (!client->connect(address)) {
        logw("Transport: cient failed to connect, socket=%d, address=%s, error=%s",
             client->socket(),
             address,
             strerror(errno));
        return nullptr;
    }

    logi("Transport: connection established to server, address=%s, socket=%d",
         address,
         client->socket());

    return client.release();
}



UnixDomainSocket::UnixDomainSocket()
{
}

int UnixDomainSocket::read(CommandBuffer *buffer)
{
    assert(buffer->position() == 0);

    int size = 0;
    if (::read(m_socket, &size, sizeof(int)) != sizeof(int)) {
        logw("Transport: failed to read size from socket");
        buffer->reset();
        return 0;
    }

    logd("Transport: read pending=%d", size);
    buffer->growTo(size);

    int count = ::read(m_socket, buffer->rawAtStart(), size);
    if (count != size) {
        logw("Transport: read failed, read=%d, expected=%d", count, size);
        buffer->reset();
        return 0;
    }
    buffer->setLastCommand(size);

    return size;
}

int UnixDomainSocket::write(const CommandBuffer &buffer)
{
    int size = buffer.position();

    if (::write(m_socket, &size, sizeof(int)) != sizeof(int)) {
        logw("Transport: failed to write size to socket");
        return 0;
    }

    if (::write(m_socket, buffer.rawAtStart(), size) != size) {
        logw("Transport: failed to write buffer to socket..");
        return 0;
    }

    logd("Transport: wrote %d bytes...", size);

    return size;
}



ServerSocket::ServerSocket()
{
    m_serverSocket = ::socket(AF_UNIX, SOCK_STREAM, 0);
}

bool ServerSocket::connect(const char *address)
{
    sockaddr_un addr = transport_sockaddrForAddress(address);

    if (bind(m_serverSocket, (sockaddr *) &addr, sizeof(addr)) != 0) {
        logd(" - failed to bind..");
        return false;
    }

    if (listen(m_serverSocket, 0) != 0) {
        logd(" - failed to listen..");
        return false;
    }

    logi("Transport: awaiting connection on address=%s, socket=%d", address, m_socket);
    m_socket = accept(m_serverSocket, 0, 0);
    if (m_socket <= 0) {
        logd(" - failed to accept");
        return false;
    }

    return true;
}



ClientSocket::ClientSocket()
{
    m_socket = ::socket(AF_UNIX, SOCK_STREAM, 0);
}

bool ClientSocket::connect(const char *address)
{
    sockaddr_un addr = transport_sockaddrForAddress(address);
    if (::connect(m_socket, (sockaddr *) &addr, sizeof(addr)) != 0) {
        logd(" - connection failed..");
        return false;
    }

    return true;
}

