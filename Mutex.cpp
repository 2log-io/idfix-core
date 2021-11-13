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

#include "Mutex.h"

extern "C"
{
	#include <esp_log.h>
}

namespace
{
	const char*	LOG_TAG = "IDFix::Mutex";
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"

//#define DEBUG_MUTEX

namespace IDFix
{

	Mutex::Mutex(RecursionMode recursionMode) : _recursionMode(recursionMode)
	{
		switch (_recursionMode)
		{
			case NonRecursive:	_mutex = xSemaphoreCreateMutex();			break;
			case Recursive:		_mutex = xSemaphoreCreateRecursiveMutex();	break;
		}
	}

	Mutex::~Mutex()
	{
		vSemaphoreDelete(_mutex);
	}

	bool Mutex::lock()
	{
		if ( _mutex == nullptr )
		{
			return false;
		}

		BaseType_t result = pdTRUE;

		switch (_recursionMode)
		{
			case NonRecursive:	result = xSemaphoreTake			(_mutex, portMAX_DELAY ); break;
			case Recursive:		result = xSemaphoreTakeRecursive(_mutex, portMAX_DELAY ); break;
		}

		if ( result != pdTRUE )
		{
			ESP_LOGE(LOG_TAG, "Failed to take mutex at file %s:%d.", __FILE__, __LINE__);
			return false;
		}

		#ifdef DEBUG_MUTEX
			ESP_LOGV(LOG_TAG, "Mutex locked");
		#endif
		return true;
	}

	bool Mutex::tryLock(unsigned int timeout)
	{
		if ( _mutex == nullptr )
		{
			return false;
		}

		BaseType_t result = pdTRUE;

		switch (_recursionMode)
		{
			case NonRecursive:	result = xSemaphoreTake			(_mutex, timeout / portTICK_PERIOD_MS ); break;
			case Recursive:		result = xSemaphoreTakeRecursive(_mutex, timeout / portTICK_PERIOD_MS ); break;
		}

		if ( result != pdTRUE )
		{
			ESP_LOGE(LOG_TAG, "Failed to take mutex at file %s:%d.", __FILE__, __LINE__);
			return false;
		}

		#ifdef DEBUG_MUTEX
			ESP_LOGV(LOG_TAG, "Mutex locked");
		#endif
		return true;
	}

	void Mutex::unlock()
	{
		if ( _mutex == nullptr )
		{
			return;
		}

		switch (_recursionMode)
		{
			case NonRecursive:	xSemaphoreGive			(_mutex); break;
			case Recursive:		xSemaphoreGiveRecursive	(_mutex); break;
		}

		#ifdef DEBUG_MUTEX
			ESP_LOGV(LOG_TAG, "Mutex unlocked");
		#endif
	}

	bool Mutex::isRecursive() const
	{
		return _recursionMode == Recursive;
	}

}

#pragma GCC diagnostic pop

