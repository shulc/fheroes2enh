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

#ifndef WIN32

#include <sys/time.h>

#endif // !WINDOWS

#include "SDL_thread.h"
#include "types.h"

namespace SDL
{

    class Thread
    {
    public:
        Thread();

        ~Thread();

        Thread(const Thread &);

        Thread &operator=(const Thread &);

        void Create(int (*)(void *), void *param = nullptr);

        int Wait();

        void Kill();

        bool IsRun() const;

        uint32_t GetID() const;

    private:
        SDL_Thread *thread;
    };

    class Mutex
    {
    public:
        explicit Mutex(bool init = false);

        Mutex(const Mutex &);

        ~Mutex();

        Mutex &operator=(const Mutex &);

        void Create();

        bool Lock() const;

        bool Unlock() const;

    private:

        SDL_mutex *mutex;
    };

    class Timer
    {
    public:
        Timer();

        bool IsValid() const;

        void Run(uint32_t, uint32_t (*)(uint32_t, void *), void *param = nullptr);

        void Remove();

    private:
        SDL_TimerID id;
    };

    class Time
    {
    public:
        Time();

        void Start();

        void Stop();

        uint32_t Get() const;

        void Print(const char *header = nullptr) const;

    private:
        uint32_t tick1;
        uint32_t tick2;
    };

}

