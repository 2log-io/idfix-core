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

#include "TaskManager.h"

extern "C"
{
	#include <esp_log.h>
	#include <string.h>
}

#include "auxiliary.h"

namespace
{
	const char* LOG_TAG = "IDFix::TaskManager";
}

namespace IDFix
{

	TaskManager::TaskManager()
	{

	}

	TaskManager::~TaskManager()
	{

	}

	void TaskManager::printTaskList()
	{
		volatile UBaseType_t numberOfTasks;

        // Take a snapshot of the number of tasks in case it changes while this function is executing.
        numberOfTasks = uxTaskGetNumberOfTasks();

        // Allocate a TaskStatus_t structure for each task.  An array could be allocated statically at compile time.
        TaskStatus_t *pxTaskStatusArray = static_cast<TaskStatus_t*>(pvPortMalloc( numberOfTasks * sizeof( TaskStatus_t ) ) );

        if( pxTaskStatusArray != NULL )
        {
            uint32_t ulTotalRunTime, ulStatsAsPercentage;

            // Generate raw status information about each task.
            numberOfTasks = uxTaskGetSystemState( pxTaskStatusArray, numberOfTasks, &ulTotalRunTime );

            // For percentage calculations.
            ulTotalRunTime /= 100UL;

            // Avoid divide by zero errors.
            if( ulTotalRunTime > 0 )
            {
                //      NAM ID ST  PR  CP CO ST
                printf("%20s%6s%11s%11s%10s%8s%17s\n", "NAME", "ID", "STATE", "PRIOITY", "CPU", "CORE", "STACK-MINIMUM");

                // For each populated position in the pxTaskStatusArray array,
                // format the raw data as human readable ASCII data
                for(UBaseType_t taskNumber = 0; taskNumber < numberOfTasks; taskNumber++ )
                {
                    // What percentage of the total run time has the task used?
                    // This will always be rounded down to the nearest integer.
                    // ulTotalRunTimeDiv100 has already been divided by 100.
                    ulStatsAsPercentage = pxTaskStatusArray[ taskNumber ].ulRunTimeCounter / ulTotalRunTime;

                    printf("%20s", pxTaskStatusArray[ taskNumber ].pcTaskName );

                    printf("%6u",  pxTaskStatusArray[ taskNumber ].xTaskNumber );

                    switch ( pxTaskStatusArray[ taskNumber ].eCurrentState )
                    {
                        case eRunning:      printf("%11s", "running"); break;
                        case eReady:        printf("%11s", "ready"); break;
                        case eBlocked:      printf("%11s", "blocked"); break;
                        case eSuspended:    printf("%11s", "suspended"); break;
                        case eDeleted:      printf("%11s", "deleted"); break;
                        default:            printf("%11s", "unknown"); break;
                    }

                    printf("%11u",  pxTaskStatusArray[ taskNumber ].uxCurrentPriority );

                    if( ulStatsAsPercentage > 0UL )
                    {
                        printf("%8u %%", ulStatsAsPercentage);
                    }
                    else
                    {
                        printf("%8s %%", "<1");
                    }

                    int coreID = 0;

                    #ifdef CONFIG_IDF_TARGET_ESP32
                    /*    if ( pxTaskStatusArray[ taskNumber ].xCoreID == 2147483647 )
                        {
                            coreID = -1;
                        }
                        else
                        {
                            coreID = pxTaskStatusArray[ taskNumber ].xCoreID;
                        }*/
                    #endif

                    printf("%8u", coreID);

                    printf("%17d", pxTaskStatusArray[ taskNumber ].usStackHighWaterMark);

                    printf("\n");
                }
            }

            // The array is no longer needed, free the memory it consumes.
            vPortFree( pxTaskStatusArray );
        }

	}

}


