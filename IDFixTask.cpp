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

#include "IDFixTask.h"

extern "C"
{
	#include <esp_log.h>
}

#include "auxiliary.h"

namespace
{
	const char* LOG_TAG = "IDFix::Task";
}

namespace IDFix
{
	Task::Task(std::string taskName, uint16_t stackSize, uint8_t priority, BaseType_t coreID)
		: _taskName(taskName), _stackSize(stackSize), _priority(priority), _coreID(coreID)
	{

	}

	Task::~Task()
	{
		stopTask();
	}

	void Task::startTask()
	{
		if ( _taskHandle == nullptr)
		{
			ESP_LOGV(LOG_TAG, "create task %s", _taskName.c_str() );
			xTaskCreatePinnedToCore(Task::runTask, _taskName.c_str(), _stackSize, static_cast<void*>(this), _priority, &_taskHandle, _coreID);
		}
		else
		{
			ESP_LOGW(LOG_TAG, "Task %s already created!", _taskName.c_str() );
		}
	}

	void Task::stopTask()
	{
		if ( _taskHandle == nullptr )
		{
			// task not yet created
			return;
		}

		// if Task::stop is called from the task which is about to stop
		// no code after vTaskDelete will be executed anymore, so do all necessary work before
		xTaskHandle taskHandleToStop = _taskHandle;
		_taskHandle = nullptr;

		ESP_LOGI(LOG_TAG, "Task %s stopped", _taskName.c_str() );

		vTaskDelete(taskHandleToStop);
	}

	void Task::suspendTask()
	{
		if ( _taskHandle != nullptr)
		{
			vTaskSuspend(_taskHandle);
		}
	}

	void Task::resumeTask()
	{
		if ( _taskHandle != nullptr)
		{
			vTaskResume(_taskHandle);
		}
	}

	void Task::runTask(void *taskInstance)
	{
		Task* task = static_cast<Task*>(taskInstance);

		if (task != nullptr)
		{
			task->run();
			task->stopTask();
		}
	}
}


