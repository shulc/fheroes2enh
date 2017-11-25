/***************************************************************************
 *   Copyright (C) 2012 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   Part of the Free Heroes2 Engine:                                      *
 *   http://sourceforge.net/projects/fheroes2                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef H2SERIALIZE_H
#define H2SERIALIZE_H

#include <map>
#include <list>
#include <string>
#include <vector>

#include "types.h"

struct Point;
struct Rect;
struct Size;

using namespace std;

class StreamBase
{
protected:
    size_t flags;

    virtual int get8() = 0;

    virtual void put8(char) = 0;

    virtual size_t sizeg() const = 0;

    virtual size_t sizep() const = 0;

    virtual size_t tellg() const = 0;

    virtual size_t tellp() const = 0;

    void setconstbuf(bool);

    void setfail(bool);

public:
    StreamBase() : flags(0)
    {}

    virtual ~StreamBase()
    {}

    void setbigendian(bool);

    bool isconstbuf() const;

    bool fail() const;

    bool bigendian() const;

    virtual void skip(size_t) = 0;

    virtual int getBE16() = 0;

    virtual int getLE16() = 0;

    virtual int getBE32() = 0;

    virtual int getLE32() = 0;

    virtual void putBE32(u32) = 0;

    virtual void putLE32(u32) = 0;

    virtual void putBE16(u16) = 0;

    virtual void putLE16(u16) = 0;

    virtual vector<u8>
    getRaw(size_t = 0 /* all data */) = 0;

    virtual void putRaw(const char *, size_t) = 0;

    int get16();

    int get32();

    void put16(u16);

    void put32(u32);

    int get()
    { return get8(); } // get char
    void put(int ch)
    { put8(ch); }

    StreamBase &operator>>(bool &);

    StreamBase &operator>>(char &);

    StreamBase &operator>>(u8 &);

    StreamBase &operator>>(s8 &);

    StreamBase &operator>>(u16 &);

    StreamBase &operator>>(s16 &);

    StreamBase &operator>>(u32 &);

    StreamBase &operator>>(s32 &);

    StreamBase &operator>>(float &);

    StreamBase &operator>>(string &);

    StreamBase &operator>>(Rect &);

    StreamBase &operator>>(Point &);

    StreamBase &operator>>(Size &);

    StreamBase &operator<<(const bool &);

    StreamBase &operator<<(const char &);

    StreamBase &operator<<(const u8 &);

    StreamBase &operator<<(const s8 &);

    StreamBase &operator<<(const u16 &);

    StreamBase &operator<<(const s16 &);

    StreamBase &operator<<(const u32 &);

    StreamBase &operator<<(const s32 &);

    StreamBase &operator<<(const float &);

    StreamBase &operator<<(const string &);

    StreamBase &operator<<(const Rect &);

    StreamBase &operator<<(const Point &);

    StreamBase &operator<<(const Size &);

    template<class Type1, class Type2>
    StreamBase &operator>>(pair<Type1, Type2> &p)
    {
        return *this >> p.first >> p.second;
    }

    template<class Type>
    StreamBase &operator>>(vector<Type> &v)
    {
        const u32 size = get32();
        v.resize(size);
        for (typename vector<Type>::iterator
                     it = v.begin(); it != v.end(); ++it)
            *this >> *it;
        return *this;
    }

    template<class Type>
    StreamBase &operator>>(list<Type> &v)
    {
        const u32 size = get32();
        v.resize(size);
        for (typename list<Type>::iterator
                     it = v.begin(); it != v.end(); ++it)
            *this >> *it;
        return *this;
    }

    template<class Type1, class Type2>
    StreamBase &operator>>(map<Type1, Type2> &v)
    {
        const u32 size = get32();
        v.clear();
        for (u32 ii = 0; ii < size; ++ii)
        {
            pair<Type1, Type2> pr;
            *this >> pr;
            v.insert(pr);
        }
        return *this;
    }

    template<class Type1, class Type2>
    StreamBase &operator<<(const pair<Type1, Type2> &p)
    {
        return *this << p.first << p.second;
    }

    template<class Type>
    StreamBase &operator<<(const vector<Type> &v)
    {
        put32(static_cast<u32>(v.size()));
        for (typename vector<Type>::const_iterator
                     it = v.begin(); it != v.end(); ++it)
            *this << *it;
        return *this;
    }

    template<class Type>
    StreamBase &operator<<(const list<Type> &v)
    {
        put32(static_cast<u32>(v.size()));
        for (typename list<Type>::const_iterator
                     it = v.begin(); it != v.end(); ++it)
            *this << *it;
        return *this;
    }

    template<class Type1, class Type2>
    StreamBase &operator<<(const map<Type1, Type2> &v)
    {
        put32(static_cast<u32>(v.size()));
        for (typename map<Type1, Type2>::const_iterator
                     it = v.begin(); it != v.end(); ++it)
            *this << *it;
        return *this;
    }
};

#ifdef WITH_ZLIB

class ZStreamBuf;

#endif

class StreamBuf : public StreamBase
{
public:
    StreamBuf(size_t = 0);

    StreamBuf(const StreamBuf &);

    StreamBuf(const vector<u8> &);

    StreamBuf(const u8 *, size_t);

    ~StreamBuf();

    StreamBuf &operator=(const StreamBuf &);

    const u8 *data() const;

    size_t size() const;

    size_t capacity() const;

    void seek(size_t);

    void skip(size_t);

    int getBE16();

    int getLE16();

    int getBE32();

    int getLE32();

    void putBE32(u32);

    void putLE32(u32);

    void putBE16(u16);

    void putLE16(u16);

    vector<u8> getRaw(size_t = 0 /* all data */);

    void putRaw(const char *, size_t);

    string toString(size_t = 0 /* all data */);

protected:
    void reset();

    size_t tellg() const;

    size_t tellp() const;

    size_t sizeg() const;

    size_t sizep() const;

    void copy(const StreamBuf &);

    void realloc(size_t);

    void setfail();

    int get8();

    void put8(char);

#ifdef WITH_ZLIB

    friend class ZStreamBuf;

#endif

    u8 *itbeg;
    u8 *itget;
    u8 *itput;
    u8 *itend;
};

class StreamFile : public StreamBase
{
    SDL_RWops *rw;

public:
    StreamFile()
    {}

    StreamFile(const string &, const char *mode);

    ~StreamFile();

    size_t size() const;

    size_t tell() const;

    bool open(const string &, const char *mode);

    void close();

    StreamBuf toStreamBuf(size_t = 0 /* all data */);

    void seek(size_t);

    void skip(size_t);

    int getBE16();

    int getLE16();

    int getBE32();

    int getLE32();

    void putBE32(u32);

    void putLE32(u32);

    void putBE16(u16);

    void putLE16(u16);

    vector<u8> getRaw(size_t = 0 /* all data */);

    void putRaw(const char *, size_t);

    string toString(size_t = 0 /* all data */);

protected:
    StreamFile &operator=(const StreamFile &)
    { return *this; }

    size_t sizeg() const;

    size_t sizep() const;

    size_t tellg() const;

    size_t tellp() const;

    int get8();

    void put8(char);
};

#endif
