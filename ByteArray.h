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

#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <vector>
#include <string>

namespace IDFix
{
    /**
     * @brief The ByteArray class provides an array of bytes.
     */
    class ByteArray : public std::vector<char>
	{
		public:

			ByteArray() {}

			// inherit constructors from std::vector
            using std::vector<char>::vector;

            /**
             * @brief Returns the number of bytes in the array
             * @return number of bytes in the array
             */
            using std::vector<char>::size;

            /**
             * @brief Returns a std::string object with the data contained in this ByteArray
             * @return std::string reprensentation of the data
             */
			inline std::string toString() const
			{
				return std::string( reinterpret_cast<const char*>( data() ) , size() );
			}
	};
}

#endif
