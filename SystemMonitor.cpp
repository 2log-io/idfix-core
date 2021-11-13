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

#include "SystemMonitor.h"
#include "TaskManager.h"

extern "C"
{
	#include <esp_log.h>
	#include <stdio.h>
	#include <esp_system.h>
}

namespace
{
	const char*	LOG_TAG	= "IDFix::SystemMonitor";
}

namespace IDFix
{
    SystemMonitor::SystemMonitor()  :   Task("system_monitor")
    {

    }

    void SystemMonitor::setOutputInterval(uint32_t interval)
    {
        _outputInterval = interval;
    }

    void SystemMonitor::start()
    {
        startTask();
    }

    void SystemMonitor::stop()
    {
        stopTask();
    }

    void SystemMonitor::run()
    {
        printf("\x1b[2J");

        while ( true )
        {
            printf("\x1b[H####### System Monitor #######\n\n");

            printf("freeHeapSize:     %d \n", esp_get_free_heap_size() );
            printf("minFreeHeapSize:  %d \n", esp_get_minimum_free_heap_size() );
            printf("\nTasklist:\n\n");

            TaskManager::printTaskList();

            Task::delay(_outputInterval);
        }
    }
}

