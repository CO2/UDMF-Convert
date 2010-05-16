// Copyright (C) 2009, 2010 Brendon Duncan

/* This file is a part of UDMFConvert.

UDMFConvert is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version
3 of the License or (at your option) any later version.

UDMFConvert is distributed in the hope that it will be useful
but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public
License along with this program. If not, see
<http://www.gnu.org/licenses/>. */

#ifndef exceptions_cvt_h
#define exceptions_cvt_h

#include <string>

namespace exception
{
	class root
	{
	private:
		std::string err;
	public:
		root(std::string newerr)
		{
			this->err = newerr;
		};
		root(const root &src)
		{
			this->err = src.err;
		};
		const char *what() const
		{
			return this->err.c_str();
		};
	};

	class eof : public root {public: eof() : root("End Of File") {};};
	class missing_args : public root {public: missing_args() : root("Missing arguments") {};};
	class file_error : public root {public: file_error(std::string fname) : root(std::string("Error opening file \'") + fname + std::string("\'")) {};};
};

#endif
