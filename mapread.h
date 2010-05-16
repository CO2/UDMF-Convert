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

#include <iostream>
#include "exceptions.h"

#define getbyte_e(i,f,v) getchar_e(i,f); \
	v = i;
#define getarray_e(i,f,v,p) for (int pos = 0;pos < p;pos++) \
	{ getbyte_e(i,f,v[pos]); }

static void getchar_e(int &i,FILE *f)
{
	i = fgetc(f);
	if (i == EOF)
	{
		throw exception::eof();
	}
}

static void getshort_e(int &i,FILE *f,short &v)
{
	getchar_e(i,f);
	v = i;
	getchar_e(i,f);
	v |= (i << 8);
}
