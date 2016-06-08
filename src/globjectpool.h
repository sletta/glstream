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
#include <cassert>

#include <GLES2/gl2.h>


class GLObjectPool
{
public:
    typedef std::vector<GLuint>::const_iterator const_iterator;

    GLuint allocate();
    void release(GLuint id);

    const_iterator begin() const { return m_ids.begin(); }
    const_iterator end() const { return m_ids.end(); }


private:
    std::vector<GLuint> m_ids;
};


inline GLuint GLObjectPool::allocate()
{
    int pos = 0;
    while (m_ids.size() > pos && m_ids[pos] == pos + 1)
        ++pos;
    m_ids.insert(m_ids.begin() + pos, pos + 1);
    return pos + 1;
}


inline void GLObjectPool::release(GLuint id)
{
    auto end = m_ids.end();
    auto pos = std::find(m_ids.begin(), end, id);
    if (*pos == id) {
        m_ids.erase(pos);
        assert(std::is_sorted(m_ids.begin(), m_ids.end()));
    }
}


