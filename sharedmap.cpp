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
#include "sharedmap.h"
#include "mapread.h"

namespace shared
{
	sidedef getsidedef(FILE *SIDEDEFS)
	{
		int i;
		sidedef s;
		getshort_e(i,SIDEDEFS,s.xoffset);
		getshort_e(i,SIDEDEFS,s.yoffset);
		getarray_e(i,SIDEDEFS,s.upper,8);
		getarray_e(i,SIDEDEFS,s.lower,8);
		getarray_e(i,SIDEDEFS,s.middle,8);
		getshort_e(i,SIDEDEFS,s.faces);
		return s;
	}
	
	vertex getvertex(FILE *VERTEXES)
	{
		int i;
		vertex v;
		getshort_e(i,VERTEXES,v.x);
		getshort_e(i,VERTEXES,v.y);
		return v;
	}
	
	sector getsector(FILE *SECTORS)
	{
		int i;
		sector s;
		getshort_e(i,SECTORS,s.floorz);
		getshort_e(i,SECTORS,s.ceilz);
		getarray_e(i,SECTORS,s.floortex,8);
		getarray_e(i,SECTORS,s.ceiltex,8);
		getshort_e(i,SECTORS,s.light);
		getshort_e(i,SECTORS,s.special);
		getshort_e(i,SECTORS,s.tag);
		return s;
	}
};
