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
#include "hexenmap.h"

udmf::block convert(hexen::linedef l)
{
	udmf::block ul;
	ul["v1"].setint((unsigned short)l.start);
	ul["v2"].setint((unsigned short)l.end);
	if (l.flags & hexen::LDF_IMPASSIBLE)
		ul["blocking"].setbool(1);
	if (l.flags & hexen::LDF_BLOCKMONSTER)
		ul["blockmonsters"].setbool(1);
	if (l.flags & hexen::LDF_TWOSIDED)
		ul["twosided"].setbool(1);
	if (l.flags & hexen::LDF_UPPERUNPEGGED)
		ul["dontpegtop"].setbool(1);
	if (l.flags & hexen::LDF_LOWERUNPEGGED)
		ul["dontpegbottom"].setbool(1);
	if (l.flags & hexen::LDF_SECRET)
		ul["secret"].setbool(1);
	if (l.flags & hexen::LDF_BLOCKSOUND)
		ul["blocksound"].setbool(1);
	if (l.flags & hexen::LDF_NOAUTOMAP)
		ul["dontdraw"].setbool(1);
	if (l.flags & hexen::LDF_VISIBLE)
		ul["mapped"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_PLAYERCROSS)
		ul["playercross"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_PLAYERUSE)
		ul["playeruse"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_MONSTERCROSS)
		ul["monstercross"].setbool(1);
	if (((l.flags & 0x1C00) == hexen::LDA_PLAYERCROSS) && (l.flags & hexen::LDF_MONSTERUSE))
		ul["monsteruse"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_PROJECTILEHIT)
		ul["impact"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_PLAYERBUMP)
		ul["playerpush"].setbool(1);
	if (((l.flags & 0x1C00) == hexen::LDA_PLAYERCROSS) && (l.flags & hexen::LDF_MONSTERUSE))
		ul["monsterpush"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_PROJECTILECROSS)
		ul["missilecross"].setbool(1);
	if (l.flags & hexen::LDF_REPEATABLE)
		ul["repeatspecial"].setbool(1);
	if (l.special != 0)
		ul["special"].setint(l.special);
	if (l.arg[0] != 0)
		ul["arg0"].setint(l.arg[0]);
	if (l.arg[1] != 0)
		ul["arg1"].setint(l.arg[1]);
	if (l.arg[2] != 0)
		ul["arg2"].setint(l.arg[2]);
	if (l.arg[3] != 0)
		ul["arg3"].setint(l.arg[3]);
	if (l.arg[4] != 0)
		ul["arg4"].setint(l.arg[4]);
	ul["sidefront"].setint((unsigned short)l.right);
	if (l.left != -1)
		ul["sideback"].setint((unsigned short)l.left);
#ifdef ZDOOM
	if (l.flags & hexen::LDF_MONSTERUSE)
		ul["monsteractivate"].setbool(1);
	if (l.flags & hexen::LDF_BLOCKPLAYERS)
		ul["blockplayers"].setbool(1);
	if (l.flags & hexen::LDF_BLOCKALL)
		ul["blockeverything"].setbool(1);
	if ((l.flags & 0x1C00) == hexen::LDA_PROJECTILEANY)
	{
		ul["impact"].setbool(1);
		ul["missilecross"].setbool(1);
	}
#endif
	if (ul["special"] == 121)
	{
		ul["id"] = ul["arg0"];
		ul["special"].nullify();
		ul["arg0"].nullify();
		ul["arg1"].nullify();
		ul["arg2"].nullify();
		ul["arg3"].nullify();
		ul["arg4"].nullify();
#ifdef ZDOOM
		ul["id"].setint(l.arg[0] | (l.arg[4] << 8));
		if (l.arg[1] & hexen::LDFE_ZONEBOUNDARY)
			ul["zoneboundary"].setbool(1);
		if (l.arg[1] & hexen::LDFE_RAILING)
			ul["jumpover"].setbool(1);
		if (l.arg[1] & hexen::LDFE_BLOCKFLOATERS)
			ul["blockfloaters"].setbool(1);
		if (l.arg[1] & hexen::LDFE_CLIPMIDTEX)
			ul["clipmidtex"].setbool(1);
		if (l.arg[1] & hexen::LDFE_WRAPMIDTEX)
			ul["wrapmidtex"].setbool(1);
		if (l.arg[1] & hexen::LDFE_3DMIDTEX)
			ul["midtex3d"].setbool(1);
		if (l.arg[1] & hexen::LDFE_CHECKRANGE)
			ul["checkswitchrange"].setbool(1);
		if (l.arg[1] & hexen::LDFE_FIRSTSIDE)
			ul["firstsideonly"].setbool(1);
	}
	if (ul["special"] == 208)
	{
		ul["id"] = l.arg[0];
		if (l.arg[3] & hexen::LDFE_ZONEBOUNDARY)
			ul["zoneboundary"].setbool(1);
		if (l.arg[3] & hexen::LDFE_RAILING)
			ul["jumpover"].setbool(1);
		if (l.arg[3] & hexen::LDFE_BLOCKFLOATERS)
			ul["blockfloaters"].setbool(1);
		if (l.arg[3] & hexen::LDFE_CLIPMIDTEX)
			ul["clipmidtex"].setbool(1);
		if (l.arg[3] & hexen::LDFE_WRAPMIDTEX)
			ul["wrapmidtex"].setbool(1);
		if (l.arg[3] & hexen::LDFE_3DMIDTEX)
			ul["midtex3d"].setbool(1);
		if (l.arg[3] & hexen::LDFE_CHECKRANGE)
			ul["checkswitchrange"].setbool(1);
		if (l.arg[3] & hexen::LDFE_FIRSTSIDE)
			ul["firstsideonly"].setbool(1);
	}
	if (ul["special"] == 1)
	{
		ul["id"] = ul["arg3"];
		ul["arg3"].nullify();
	}
	if (ul["special"] == 5)
	{
		ul["id"] = ul["arg4"];
		ul["arg4"].nullify();
	}
	if (ul["special"] == 215)
	{
		ul["id"] = ul["arg0"];
		ul["arg0"].nullify();
	}
	if (ul["special"] == 222)
	{
		ul["id"] = ul["arg0"];
	}
	if (ul["special"] == 181)
	{
	    ul["id"] = ul["arg2"];
	    ul["arg2"].nullify();
#endif
	}
	return ul;
}

udmf::block convert(hexen::thing t,double xfactor,double yfactor,double zfactor)
{
	udmf::block ut;
	if (t.tid != 0)
		ut["id"] = t.tid;
	ut["x"].setfloat(t.x * xfactor);
	ut["y"].setfloat(t.y * yfactor);
	if (t.angle != 0)
		ut["angle"] = t.angle;
	ut["type"] = t.doomednum;
	if (t.height != 0)
		ut["height"].setfloat(t.height * zfactor);
	if (t.flags & hexen::TF_EASY)
	{
		ut["skill1"].setbool(1);
		ut["skill2"].setbool(1);
	}
	if (t.flags & hexen::TF_MEDIUM)
		ut["skill3"].setbool(1);
	if (t.flags & hexen::TF_HARD)
	{
		ut["skill4"].setbool(1);
		ut["skill5"].setbool(1);
	}
	if (t.flags & hexen::TF_AMBUSH)
		ut["ambush"].setbool(1);
	if (t.flags & hexen::TF_SINGLE)
		ut["single"].setbool(1);
	if (t.flags & hexen::TF_DMATCH)
		ut["dm"].setbool(1);
	if (t.flags & hexen::TF_COOP)
		ut["coop"].setbool(1);
	if (t.flags & hexen::TF_DORMANT)
		ut["dormant"].setbool(1);
	if (t.flags & hexen::TF_FIGHTER)
		ut["class1"].setbool(1);
	if (t.flags & hexen::TF_CLERIC)
		ut["class2"].setbool(1);
	if (t.flags & hexen::TF_MAGE)
		ut["class3"].setbool(1);
#ifdef ZDOOM
	if (t.flags & hexen::TF_TRANSLUCENT)
		ut["translucent"].setbool(1);
	if (t.flags & hexen::TF_INVISIBLE)
		ut["invisible"].setbool(1);
	if (t.flags & hexen::TF_FRIENDLY)
		ut["stifeally"].setbool(1);
	if (t.flags & hexen::TF_STANDSTILL)
		ut["standing"].setbool(1);
#endif
	if (t.special != 0)
		ut["special"].setint(t.special);
	if (t.arg[0] != 0)
		ut["arg0"].setint(t.arg[0]);
	if (t.arg[1] != 0)
		ut["arg1"].setint(t.arg[1]);
	if (t.arg[2] != 0)
		ut["arg2"].setint(t.arg[2]);
	if (t.arg[3] != 0)
		ut["arg3"].setint(t.arg[3]);
	if (t.arg[4] != 0)
		ut["arg4"].setint(t.arg[4]);
	return ut;
}
