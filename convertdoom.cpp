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
#include "doommap.h"

udmf::block convert(doom::linedef l)
{
	udmf::block ul;
	if (l.tag != 0)
	{
		ul["id"].setint((unsigned short)l.tag);
		ul["arg0"].setint((unsigned short)l.tag);
	}
	ul["v1"].setint((unsigned short)l.start);
	ul["v2"].setint((unsigned short)l.end);
	if (l.flags & doom::LDF_IMPASSIBLE)
		ul["blocking"].setbool(1);
	if (l.flags & doom::LDF_BLOCKMONSTER)
		ul["blockmonsters"].setbool(1);
	if (l.flags & doom::LDF_TWOSIDED)
		ul["twosided"].setbool(1);
	if (l.flags & doom::LDF_UPPERUNPEGGED)
		ul["dontpegtop"].setbool(1);
	if (l.flags & doom::LDF_LOWERUNPEGGED)
		ul["dontpegbottom"].setbool(1);
	if (l.flags & doom::LDF_SECRET)
		ul["secret"].setbool(1);
	if (l.flags & doom::LDF_BLOCKSOUND)
		ul["blocksound"].setbool(1);
	if (l.flags & doom::LDF_NOAUTOMAP)
		ul["dontdraw"].setbool(1);
	if (l.flags & doom::LDF_VISIBLE)
		ul["mapped"].setbool(1);
	if (l.flags & doom::LDF_PASSUSE)
		ul["passuse"].setbool(1);
	if (l.special != 0)
		ul["special"].setint((unsigned short)l.special);
	ul["sidefront"] = (unsigned short)l.right;
	if (l.left != -1)
		ul["sideback"].setint((unsigned short)l.left);
	return ul;
}

udmf::block convert(doom::thing t,double xfactor,double yfactor,double zfactor)
{
	udmf::block ut;
	ut["x"].setfloat(t.x * xfactor);
	ut["y"].setfloat(t.y * yfactor);
	if (t.angle != 0)
		ut["angle"].setint(t.angle);
	ut["type"].setint((unsigned short)t.doomednum);
	if (t.flags & doom::TF_EASY)
	{
		ut["skill1"].setbool(1);
		ut["skill2"].setbool(1);
	}
	if (t.flags & doom::TF_MEDIUM)
		ut["skill3"].setbool(1);
	if (t.flags & doom::TF_HARD)
	{
		ut["skill4"].setbool(1);
		ut["skill5"].setbool(1);
	}
	if (t.flags & doom::TF_AMBUSH)
		ut["ambush"].setbool(1);
	if (!(t.flags & doom::TF_MULTI))
		ut["single"].setbool(1);
	if (!(t.flags & doom::TF_NODM))
		ut["dm"].setbool(1);
	if (!(t.flags & doom::TF_NOCOOP))
		ut["coop"].setbool(1);
	if (t.flags & doom::TF_FRIEND)
		ut["friend"].setbool(1);
	return ut;
}
