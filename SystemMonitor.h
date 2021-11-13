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

#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include "IDFixTask.h"

extern "C"
{
    #include <stdint.h>
}

namespace IDFix
{
    /**
     * @brief The SystemMonitor class is a utility class to periodically output the task stats.
     */
	class SystemMonitor : public Task
	{
		public:

                            SystemMonitor();

            /**
             * @brief Set the interval at which the output occurs
             * @param interval the periodic interval in miliseconds
             */
            void            setOutputInterval(uint32_t interval);

            /**
             * @brief Start the monitoring
             */
            void            start();

            /**
             * @brief Stop the monitoring
             */
            void            stop();

        protected:

            /**
             * @brief Periodically print the FreeRTOS task list
             */
            virtual void    run() override;

		protected:

            uint32_t        _outputInterval = { 1000 };
	};
}

#endif
