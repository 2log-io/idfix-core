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

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

extern "C"
{
	#include <freertos/FreeRTOS.h>
	#include <freertos/task.h>
}

#include <string>

namespace IDFix
{
    /**
     * @brief The TaskManager class is a utility class to get an overview of the current existing tasks.
     */
	class TaskManager
	{
		public:

							TaskManager();
			virtual			~TaskManager();

             /**
             * @brief Prints the currently existing tasks and some of their stats.
             *
             * NOTE: This function is intended for debugging use only as its use results in the scheduler remaining
             * suspended for an extended period.
             */
			static void		printTaskList(void);
	};
}

#endif
