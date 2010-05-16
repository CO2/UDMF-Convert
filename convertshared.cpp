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

#include "convert.h"
#include "udmf.h"
#include "sharedmap.h"

udmf::block convert(shared::sidedef s)
{
	udmf::block us;
	if (s.xoffset != 0)
		us["offsetx"] = s.xoffset;
	if (s.yoffset != 0)
		us["offsety"] = s.yoffset;
	if (strcmp("-",s.upper))
		us["texturetop"].setstr(s.upper,8);
	if (strcmp("-",s.lower))
		us["texturebottom"].setstr(s.lower,8);
	if (strcmp("-",s.middle))
		us["texturemiddle"].setstr(s.middle,8);
	us["sector"] = s.faces;
	return us;
}

udmf::block convert(shared::vertex v,double xfactor,double yfactor)
{
	udmf::block uv;
	uv["x"].setfloat(v.x * xfactor);
	uv["y"].setfloat(v.y * yfactor);
	return uv;
}

udmf::block convert(shared::sector s,double zfactor)
{
	udmf::block us;
	if (s.floorz != 0)
		us["heightfloor"].setint(s.floorz * zfactor);
	if (s.ceilz != 0)
		us["heightceiling"].setint(s.ceilz * zfactor);
	us["texturefloor"].setstr(s.floortex,8);
	us["textureceiling"].setstr(s.ceiltex,8);
	if (s.light != 160)
		us["lightlevel"].setint(s.light);
	if (s.special != 0)
		us["special"].setint((unsigned short)s.special);
	if (s.tag != 0)
		us["id"].setint((unsigned short)s.tag);
	return us;
}
