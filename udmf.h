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

#ifndef udmf_data_h
#define udmf_data_h

#include <map>
#include <string>
#include <fstream>

namespace udmf
{
	enum valtypes
	{
		BVT_NULL,
		BVT_INTEGER,
		BVT_FLOAT,
		BVT_BOOLEAN,
		BVT_STRING,
		BVT_SUBBLOCK
	};

	class variant;

	typedef std::map <std::string,variant> block;

	class variant
	{
		friend void writeblock(const char *,block,std::ofstream &);

	private:
		int valtype;
		union
		{
			int intval;
			double floatval;
			bool boolval;
			char *stringval;
			block *subval;
		} val;
	public:
		variant();
		variant(const variant &);
		variant(int);
		variant(double);
		variant(bool);
		variant(const char *);
		variant(const block &);
		variant &operator=(const variant &);
		bool operator>(const variant &) const;
		bool operator<(const variant &) const;
		bool operator>=(const variant &) const;
		bool operator<=(const variant &) const;
		bool operator==(const variant &) const;
		bool operator!=(const variant &) const;
		void nullify();
		void setint(int);
		void setfloat(double);
		void setbool(bool);
		void setstr(const char *);
		void setstr(const char *,int);
		void setsub(const block &);
		~variant();
	};

	void writeblock(const char *,block,std::ofstream &);

/*	class block
	{
	private:
		char *name;
		int valcount;
		blockval *top;
		blockval &addval(char *,blockval &);
	public:
		block();
		block(const block &);
		explicit block(const char *);
		block &operator=(const block &);
		blockval &operator[](const char *);
		~block();
	};*/
}

#endif
