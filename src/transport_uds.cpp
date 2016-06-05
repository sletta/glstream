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
#include "logging.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

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

    int socket() const { return m_socket; }

    int m_socket = 0;
};



class ServerSocket : public UnixDomainSocket
{
public:
    bool connect(const char *address);

    int m_readSocket = 0;
};



class ClientSocket : public UnixDomainSocket
{
public:
    bool connect(const char *address);
};



Transport *Transport::awaitConnection(const char *address)
{
    std::unique_ptr<ServerSocket> server(new ServerSocket());
    int unlinked = unlink(address);
    logd("Transport: awaiting connection, address=%s, socket=%d, unlink=%d\n",
         address,
         server->m_socket,
         unlinked);

    if (!server->connect(address)) {
        logw("Transport: server failed to connect, socket=%d, readSocket=%d, address=%s, error=%s\n",
             server->m_socket,
             server->m_readSocket,
             address,
             strerror(errno));
        return nullptr;
    }

    logi("Transport: connection established with client, address=%s, socket=%d, readSocket=%d\n",
         address,
         server->m_socket,
         server->m_readSocket);

    return server.release();
}


Transport *Transport::connect(const char *address)
{
    std::unique_ptr<ClientSocket> client(new ClientSocket());
    logd("Transport:(%s), using fd=%d\n", address, client->socket());

    if (!client->connect(address)) {
        logw("Transport: cient failed to connect, socket=%d, address=%s, error=%s\n",
             client->socket(),
             address,
             strerror(errno));
        return nullptr;
    }

    logi("Transport: connection established to server, address=%s, socket=%d\n",
         address,
         client->socket());

    return client.release();
}



UnixDomainSocket::UnixDomainSocket()
{
    m_socket = ::socket(AF_UNIX, SOCK_STREAM, 0);
}



bool ServerSocket::connect(const char *address)
{
    sockaddr_un addr = transport_sockaddrForAddress(address);

    if (bind(m_socket, (sockaddr *) &addr, sizeof(addr)) != 0) {
        logde(" - failed to bind..\n");
        return false;
    }

    if (listen(m_socket, 0) != 0) {
        logde(" - failed to listen..\n");
        return false;
    }

    logi("Transport: awaiting connection on address=%s, socket=%d\n", address, m_socket);
    m_readSocket = accept(m_socket, 0, 0);
    if (m_readSocket <= 0) {
        logde(" - failed to accept\n");
        return false;
    }

    return true;
}



bool ClientSocket::connect(const char *address)
{
    sockaddr_un addr = transport_sockaddrForAddress(address);
    if (::connect(m_socket, (sockaddr *) &addr, sizeof(addr)) != 0) {
        logde(" - connection failed..\n");
        return false;
    }

    return true;
}

