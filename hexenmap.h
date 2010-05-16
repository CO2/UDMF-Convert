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

#ifndef hexen_mapdata_h
#define hexen_mapdata_h

#include <iostream>
#include "sharedmap.h"

namespace hexen
{
	enum thingflags
	{
		TF_EASY = 0x1,		//Appears on skills 0 and 1
		TF_MEDIUM = 0x2,	//Ditto for skill 2
		TF_HARD = 0x4,		//Ditto for skills 3 and 4
		TF_AMBUSH = 0x8,	//This name is more awesome than "deaf"
		TF_DORMANT = 0x10,	//Must be activated with thing_activate
		TF_FIGHTER = 0x20,	//Appears for fighter class
		TF_CLERIC = 0x40,	//Appears for cleric class
		TF_MAGE = 0x80,		//Appears for mage class
		TF_SINGLE = 0x100,	//Appears in singleplayer games
		TF_COOP = 0x200,	//Appears in cooperative games
		TF_DMATCH = 0x400	//Appears in deathmatch games
	};

	enum linedefflags
	{
		LDF_IMPASSIBLE = 0x1,
		LDF_BLOCKMONSTER = 0x2,
		LDF_TWOSIDED = 0x4,
		LDF_UPPERUNPEGGED = 0x8,
		LDF_LOWERUNPEGGED = 0x10,
		LDF_SECRET = 0x20,
		LDF_BLOCKSOUND = 0x40,
		LDF_NOAUTOMAP = 0x80,
		LDF_VISIBLE = 0x100,
		LDF_REPEATABLE = 0x200,
		LDF_MONSTERUSE = 0x2000
	};

	enum linedefactivation
	{
		LDA_PLAYERCROSS = 0x0,
		LDA_PLAYERUSE = 0x400,
		LDA_MONSTERCROSS = 0x800,
		LDA_PROJECTILEHIT = 0xC00,
		LDA_PLAYERBUMP = 0x1000,
		LDA_PROJECTILECROSS = 0x1400,
		LDA_PASSTHRUUSE = 0x1800
	};

	struct thing
	{
		short tid;		//Thing id
		short x;		//x coordinate
		short y;		//y coordinate
		short height;	//'z' coordinate (sort of)
		short angle;
		short doomednum;
		short flags;	//Refer to thingflags enum
		unsigned char special;
		unsigned char arg[5];
	};

	struct linedef
	{
		short start;
		short end;
		short flags;	//Refer to linedefflags and linedefactivation enums
		unsigned char special;
		unsigned char arg[5];
		short right;
		short left;
	};

	typedef shared::sidedef sidedef;
	typedef shared::vertex vertex;
	typedef shared::sector sector;

	thing getthing(FILE *things);
	linedef getlinedef(FILE *linedefs);
	
	sidedef getsidedef(FILE *sidedefs);
	vertex getvertex(FILE *vertexes);
	sector getsector(FILE *sectors);
};

#endif
