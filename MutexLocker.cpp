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

#include "MutexLocker.h"

extern "C"
{
	#include <esp_log.h>
}

namespace
{
	const char*	LOG_TAG	= "IDFix::MutexLocker";
}

namespace IDFix
{

	MutexLocker::MutexLocker(Mutex &mutex) : _mutex(mutex)
	{
		if ( _mutex.lock() )
		{
			_locked = true;
		}
	}

	MutexLocker::~MutexLocker()
	{
		unlock();
	}

	Mutex &MutexLocker::mutex() const
	{
		return _mutex;
	}

	void MutexLocker::unlock()
	{
		if ( _locked )
		{
			_locked = false;
			_mutex.unlock();
		}
	}

	bool MutexLocker::relock()
	{
		if ( _locked )
		{
			return false;
		}
		else
		{
			if ( _mutex.lock() )
			{
				_locked = true;
			}
		}

		return true;
	}

}

