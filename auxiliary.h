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

#ifndef AUXILIARY_H
#define AUXILIARY_H

#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    #include <stdint.h>
    #include <esp_timer.h>

    /**
     * @brief   Get time in miliseconds since RTOS starts
     * @return  number of miliseconds since RTOS start
     */
    inline uint64_t getTickMs(void)
    {
        return static_cast<uint64_t>( esp_timer_get_time() / 1000);
    }

#ifdef __cplusplus
}
#endif

#include <memory>

/**
* \@brief   Convenience macro to define STL based pointer types.
*
* Usage:    DeclarePointers(Class); will define the following types:
*
*           Class_weakPtr   as std::weak_ptr<Class>
*           Class_sharedPtr as std::shared_ptr<Class>
*           Class_uniquePtr as std::unique_ptr<Class>
*/
#define DeclarePointers(type)	class type; \
					typedef std::weak_ptr<type> type##_weakPtr; \
					typedef std::shared_ptr<type> type##_sharedPtr; \
					typedef std::unique_ptr<type> type##_uniquePtr

#endif
