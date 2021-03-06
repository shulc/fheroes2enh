/***************************************************************************
 *   Copyright (C) 2009 by Andrey Afletdinov <fheroes2@gmail.com>          *
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
#pragma once

#include <vector>
#include <utility>
#include "types.h"

struct Point
{
    s16 x, y;

    Point() : x(0), y(0)
    {}

    Point(int, int);

    bool operator==(const Point &) const;

    bool operator!=(const Point &) const;

    bool inABC(const Point &, const Point &, const Point &) const;

    Point &operator+=(const Point &);

    Point &operator-=(const Point &);

    Point operator+(const Point &) const;

    Point operator-(const Point &) const;
};


struct Size
{
    u16 w, h;

    Size();

    Size(u16, u16);

    explicit Size(const Point &);

    bool isEmpty() const;

    bool operator==(const Size &) const;

    bool operator!=(const Size &) const;

    Size &operator+=(const Size &);

    Size &operator-=(const Size &);

    Size operator+(const Size &) const;

    Size operator-(const Size &) const;
};

struct Rect : Point, Size
{
    Rect();

    Rect(int x, int y, int w, int h)

        : Point(static_cast<s16>(x), static_cast<s16>(y)), Size(static_cast<u16>(w), static_cast<u16>(h))
    {
        
    }

    Rect(const Point &, u16, u16);

    Rect(const Point &, const Size &);

    explicit Rect(const SDL_Rect &);

    Rect &operator=(const Point &);

    bool operator==(const Rect &) const;

    bool operator!=(const Rect &) const;

    // rect include point
    bool operator&(const Point &) const;

    // rect intersects rect
    bool operator&(const Rect &) const;

    //
    static Rect Get(const Point &, const Point &);

    static Rect Get(const Rect &, const Rect &, bool intersect);

    static std::pair<Rect, Point> Fixed4Blit(const Rect &, const Rect &);
};

void SDLRect(s32, s32, uint32_t, uint32_t, SDL_Rect &writeTo);

void SDLRect(const Rect &, SDL_Rect &writeTo);

struct Points : std::vector<Point>
{
    Rect GetRect() const;
};

struct Rects : std::vector<Rect>
{
    s32 GetIndex(const Point &) const;

    Rect GetRect() const;
};
