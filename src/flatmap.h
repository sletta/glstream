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
#include <algorithm>

#include <cassert>

template <typename Key, typename Value>
class FlatMap
{

public:
    struct Entry {
        Key key;
        Value value;

        bool operator<(Entry e) const { return key < e.key; }
    };

    typedef typename std::vector<Entry>::const_iterator const_iterator;

    void clear() { m_data.clear(); }

    void insert(Key key, Value value) {
        Entry entry = { key, value };
        insert(entry);
    }

    void insert(Entry entry) {
        auto end = m_data.end();
        auto pos = std::lower_bound(m_data.begin(), end, entry);
        m_data.insert(pos, entry);
    }

    bool contains(Key key) {
        Entry entry = { key, Value() };
        auto end = m_data.end();
        auto pos = std::lower_bound(m_data.begin(), end, entry);
        return pos != end && pos->key == key;
    }

    void remove(Key key) {
        assert(contains(key));
        Entry entry = { key, Value() };
        auto end = m_data.end();
        auto pos = std::lower_bound(m_data.begin(), end, entry);
        if (pos != end && pos->key == key)
            m_data.erase(pos);
    }

    Value find(Key key, Value failure = Value()) {
        Entry entry = { key, Value() };
        auto end = m_data.end();
        auto pos = std::lower_bound(m_data.begin(), end, entry);
        return pos == end || pos->key != key ? failure : pos->value;
    }

    const_iterator begin() const { return m_data.begin(); }
    const_iterator end() const { return m_data.end(); }

    size_t size() const { return m_data.size(); }

private:
    std::vector<Entry> m_data;
};

