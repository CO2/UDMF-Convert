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

#ifndef shared_mapdata_h
#define shared_mapdata_h

#include <iostream>

#define shared_call(funcname,returntype,parmtype) returntype funcname(parmtype parm) {return shared::funcname(parm);}

namespace shared
{
	struct sidedef
	{
		short xoffset;
		short yoffset;
		char upper[8];
		char lower[8];
		char middle[8];
		short faces;
	};

	struct vertex
	{
		short x;
		short y;
	};

	struct sector
	{
		short floorz;
		short ceilz;
		char floortex[8];
		char ceiltex[8];
		short light;
		short special;
		short tag;
	};

	sidedef getsidedef(FILE *sidedefs);
	vertex getvertex(FILE *vertexes);
	sector getsector(FILE *sectors);
};

#endif
