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

#ifndef IDFIXTASK_H
#define IDFIXTASK_H

extern "C"
{
	#include <freertos/FreeRTOS.h>
	#include <freertos/task.h>
}

#include <string>

#ifdef CONFIG_IDF_TARGET_ESP8266
    #define tskNO_AFFINITY 0
#endif

#ifdef CONFIG_IDF_TARGET_ESP32
#endif

namespace IDFix
{
    /**
     * @brief The Task class represents a FreeRTOS task
     *
     * The Task class represents a FreeRTOS task and manages the execution of the task. To implement
     * a task subclass this class and implement the run() function, which is the starting point of the task.
     */
	class Task
	{
		public:

            /**
             * @brief Constructs a new Task
             *
             * Constructs a new Task to manage and run a FreeRTOS task. The task does not begin executing
             * until startTask() is called.
             *
             * @param taskName      A descriptive name for the task
             * @param stackSize     The size of the task stack specified as the number of bytes.
             * @param priority      The priority at which the created task will execute.
             * @param coreID        If the value is tskNO_AFFINITY, the created task is not pinned to any CPU, and
             *                      the scheduler can run it on any core available. Values 0 or 1 indicate the index
             *                      number of the CPU which the task should be pinned to
             */
							Task(std::string taskName, uint16_t stackSize = 3072, uint8_t priority = 5, BaseType_t coreID = tskNO_AFFINITY);
			virtual			~Task();

            /**
             * @brief Begins execution of the task
             *
             * Begins execution of the task by calling run(). If the task is already running, this function does nothing.
             */
			virtual void	startTask();

            /**
             * @brief Stops the execution of the task
             *
             * Stops the execution and deletes the FreeRTOS task.
             */
			virtual void	stopTask();

             /**
             * @brief Suspend this task.
             *
             * When suspended a task will never get any microcontroller processing time, no matter what its priority.
             */
			virtual void	suspendTask();

            /**
             * @brief Resumes this suspended task.
             */
			virtual void	resumeTask();

			/**
			 * @brief Function of the task to execute
			 *
			 * This function must be implemented in the subclass that represents the actual task to run.
			 * When a task is started by calling start(), this is the code that is executed in the
			 * newly created task. Returning from this method will end the executinon of the task.
			 */
			virtual void	run() = 0;

			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wold-style-cast"

            /**
             * @brief Delay the calling task for a given number of miliseconds
             * @param delayTime     the amount of time, in miliseconds, that the calling task should block
             */
			static inline void delay(TickType_t delayTime) { vTaskDelay(delayTime / portTICK_RATE_MS); }

			#pragma GCC diagnostic pop

            /**
             * @brief Get the descriptive name of the calling task
             * @return  the descriptive name of the calling task
             */
			static inline std::string getRunningTaskName(void) { return pcTaskGetTaskName(NULL); }

		private:

            /**
             * @brief Static wrapper callback for the FreeRTOS call
             * @param taskInstance  the object instance of the task to run
             */
			static void		runTask(void* taskInstance);

		protected:

			std::string		_taskName;
			uint16_t		_stackSize;
			uint8_t			_priority;
			xTaskHandle		_taskHandle = { nullptr };
			BaseType_t		_coreID;

	};
}

#endif
