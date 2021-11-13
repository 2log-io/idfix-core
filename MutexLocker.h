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

#ifndef MUTEXLOCKER_H
#define MUTEXLOCKER_H

#include "Mutex.h"

namespace IDFix
{
    /**
     * @brief The MutexLocker class is a convenient wrapper for a mutex.
     *
     * When a MutexLocker is created it locks the wrapped mutex and ensures unlocking it,
     * if the MutexLocker gets out of scope. The mutex can still be unlocked() and relocked()
     * during the lifetime of the MutexLocker.
     */
	class MutexLocker
	{
		public:

            /**
             * @brief Constructs a MutexLocker and locks the given mutex
             * @param mutex the mutex to be managed
             */
            MutexLocker(Mutex &mutex);

            /**
            * @brief Destroys the MutexLocker and unlocks the managed mutex
            */
            ~MutexLocker();

            /**
             * @brief Access the managed mutex
             * @return the managed mutex
             */
			Mutex&	mutex(void) const;

            /**
             * @brief Unlocks the managed mutex.
             *
             * To lock the mutex again, relock() can be used.
             */
			void	unlock(void);

            /**
             * @brief Relocks an unlocked mutex
             * @return true if mutex was locked; otherwise false
             */
			bool	relock(void);

		protected:

			Mutex	&_mutex;
			bool	_locked = {false};
	};
}

#endif
