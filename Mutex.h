/*   2log.io
 *   Copyright (C) 2021 - 2log.io | mail@2log.io,  sascha@2log.io
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTEX_H
#define MUTEX_H

extern "C"
{
	#include <freertos/FreeRTOS.h>
	#include <freertos/semphr.h>
}

namespace IDFix
{
    /**
     * @brief The Mutex class provides access serialization between tasks
     */
	class Mutex
	{
		public:

            /**
             * @brief The recursion mode
             */
            enum RecursionMode
            {
                Recursive,      /**< In this mode, a task can lock the same mutex multiple times and the
                                        mutex won't be unlocked until a corresponding number of
                                        unlock() calls have been made. */
                NonRecursive    /**< In this mode, a task may only lock a mutex once. */
            };

            /**
             * @brief Constructs a new mutex. The mutex is created in an unlocked state.
             *
             * If recursionMode is RecursionMode::Recursive, a task can lock the same mutex multiple times and the mutex won't be
             * unlocked until a corresponding number of unlock() calls have been made. Otherwise a task may only lock a mutex once.
             * The default is RecursionMode::NonRecursive.
             *
             * @param recursionMode
             */
            Mutex(RecursionMode recursionMode = NonRecursive);

            ~Mutex();

            /**
             * @brief   Locks the mutex. If another task has locked the mutex then this call will block until that task has unlocked it.
             *
             * Calling this function multiple times on the same mutex from the same thread is allowed if this mutex
             * is a recursive mutex. If this mutex is a non-recursive mutex, this function will dead-lock when the
             * mutex is locked recursively.
             *
             * @return  true if mutex was locked
             */
			bool	lock(void);

            /**
             * @brief Attempts to lock the mutex.
             *
             * If another task has locked the mutex, this function will wait for at most timeout milliseconds for
             * the mutex to become available.
             *
             * @param   timeout
             * @return  true if the lock was obtained, otherwise false
             */
			bool	tryLock(unsigned int timeout = 0);

            /**
             * @brief Unlocks the mutex
             *
             * Unlocks a previously locked mutex. Must not be used from an ISR.
             */
			void	unlock(void);

            /**
             * @brief   Returns true if the RecursionMode is Recursive.
             * @return  true if the RecursionMode is Recursive
             */
			bool	isRecursive(void) const;

		protected:

			SemaphoreHandle_t	_mutex;
			RecursionMode		_recursionMode;
	};
}

#endif
