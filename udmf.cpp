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

#include "udmf.h"
#include <math.h>
#include <cstring>
#include "exceptions.h"

#define vtod(x,y,z) switch (x) \
	{ case BVT_BOOLEAN: z = y.boolval;break; \
	case BVT_FLOAT: z = y.floatval;break; \
	case BVT_INTEGER: z = y.intval;break; \
	default: z = 0;break; }

namespace udmf
{
	variant::variant()
	{
		this->valtype = BVT_NULL;
	}

	variant::variant(const variant &src)
	{
		this->valtype = src.valtype;
		this->val = src.val;
	}

	variant::variant(int newval)
	{
		this->valtype = BVT_INTEGER;
		this->val.intval = newval;
	}

	variant::variant(double newval)
	{
		this->valtype = BVT_FLOAT;
		this->val.floatval = newval;
	}

	variant::variant(bool newval)
	{
		this->valtype = BVT_BOOLEAN;
		this->val.boolval = newval;
	}

	variant::variant(const char *newval)
	{
		this->valtype = BVT_STRING;
		this->val.stringval = new char[strlen(newval) + 1];
		strcpy(this->val.stringval,newval);
	}

	variant::variant(const udmf::block &newval)
	{
		this->valtype = BVT_SUBBLOCK;
		this->val.subval = new udmf::block;
		*(this->val.subval) = newval;
	}

	variant &variant::operator=(const variant &other)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = other.valtype;
		if (other.valtype == BVT_STRING)
		{
			this->val.stringval = new char[strlen(other.val.stringval) + 1];
			strcpy(this->val.stringval,other.val.stringval);
		}
		else if (other.valtype ==  BVT_SUBBLOCK)
		{
			this->val.subval = new udmf::block;
			*(this->val.subval) = *(other.val.subval);
		}
		else
			this->val = other.val;
		return *this;
	}

	bool variant::operator>(const variant &other) const
	{
		double a;
		double b;
		vtod(this->valtype,(*this).val,a);
		vtod(other.valtype,other.val,b);
		return (a > b);
	}

	bool variant::operator<(const variant &other) const
	{
		double a;
		double b;
		vtod(this->valtype,(*this).val,a);
		vtod(other.valtype,other.val,b);
		return (a < b);
	}

	bool variant::operator>=(const variant &other) const
	{
		double a;
		double b;
		vtod(this->valtype,(*this).val,a);
		vtod(other.valtype,other.val,b);
		return (a >= b);
	}

	bool variant::operator<=(const variant &other) const
	{
		double a;
		double b;
		vtod(this->valtype,(*this).val,a);
		vtod(other.valtype,other.val,b);
		return (a <= b);
	}

	bool variant::operator==(const variant &other) const
	{
		if ((this->valtype == BVT_STRING) && (other.valtype == BVT_STRING))
			return !strcmp(this->val.stringval,other.val.stringval);
		double a;
		double b;
		vtod(this->valtype,(*this).val,a);
		vtod(other.valtype,other.val,b);
		return (a == b);
	}

	bool variant::operator!=(const variant &other) const
	{
		if ((this->valtype == BVT_STRING) && (other.valtype == BVT_STRING))
			return strcmp(this->val.stringval,other.val.stringval);
		double a;
		double b;
		vtod(this->valtype,(*this).val,a);
		vtod(other.valtype,other.val,b);
		return (a != b);
	}

	void variant::nullify()
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_NULL;
	}

	void variant::setint(int newval)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_INTEGER;
		this->val.intval = newval;
	}

	void variant::setfloat(double newval)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_FLOAT;
		this->val.floatval = newval;
	}

	void variant::setbool(bool newval)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_BOOLEAN;
		this->val.boolval = newval;
	}

	void variant::setstr(const char *newval)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_STRING;
		this->val.stringval = new char[strlen(newval) + 1];
		strcpy(this->val.stringval,newval);
	}

	void variant::setstr(const char *newval,int len)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_STRING;
		this->val.stringval = new char[len + 1];
		strncpy(this->val.stringval,newval,len);
		this->val.stringval[len] = 0;
	}

	void variant::setsub(const udmf::block &other)
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
		this->valtype = BVT_SUBBLOCK;
		this->val.subval = new udmf::block;
		*(this->val.subval) = other;
	}

	variant::~variant()
	{
		if (this->valtype == BVT_STRING)
			delete[] this->val.stringval;
		else if (this->valtype == BVT_SUBBLOCK)
			delete this->val.subval;
	}

	void writeblock(const char *name,block b,std::ofstream &out)
	{
		out << name << "\n{\n";
		for (block::iterator it = b.begin();it != b.end();it++)
		{
			if (it->second.valtype == BVT_NULL)
				continue;
			out << it->first << " = ";
			switch (it->second.valtype)
			{
			case BVT_BOOLEAN:
				out << (it->second.val.boolval ? "true" : "false");
				break;
			case BVT_FLOAT:
				if (it->second.val.floatval == floor(it->second.val.floatval))
					out << it->second.val.floatval << '.';
				else
					out << it->second.val.floatval;
				break;
			case BVT_INTEGER:
				out << it->second.val.intval;
				break;
			case BVT_STRING:
				out << '\"' << it->second.val.stringval << '\"';
				//Does not escape strings and backslashes like it should
				break;
			case BVT_SUBBLOCK:
				writeblock(it->first.c_str(),*(it->second.val.subval),out);
				break;
			default:
				throw exception::root("Unknown variant type detected");
			}
			out << ";\n";
		}
		out << "}\n\n";
	}
};
