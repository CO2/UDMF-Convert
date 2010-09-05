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
#include "strifemap.h"
#include "mapread.h"

namespace strife
{
	thing getthing(FILE *THINGS)
	{
		int i;
		thing t;
		getshort_e(i,THINGS,t.x);
		getshort_e(i,THINGS,t.y);
		getshort_e(i,THINGS,t.angle);
		getshort_e(i,THINGS,t.doomednum);
		getshort_e(i,THINGS,t.flags);
		return t;
	}
	
	linedef getlinedef(FILE *LINEDEFS)
	{
		int i;
		linedef l;
		getshort_e(i,LINEDEFS,l.start);
		getshort_e(i,LINEDEFS,l.end);
		getshort_e(i,LINEDEFS,l.flags);
		getshort_e(i,LINEDEFS,l.special);
		getshort_e(i,LINEDEFS,l.tag);
		getshort_e(i,LINEDEFS,l.right);
		getshort_e(i,LINEDEFS,l.left);
		return l;
	}

	shared_call(getsidedef,sidedef,FILE *);
	shared_call(getvertex,vertex,FILE *);
	shared_call(getsector,sector,FILE *);
}
