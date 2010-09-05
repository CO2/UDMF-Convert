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

#ifndef convert_map_h
#define convert_map_h

#include <cstring>

#include "doommap.h"
#include "hexenmap.h"
#include "zdoommap.h"
#include "strifemap.h"
#include "sharedmap.h"
#include "udmf.h"

//Shared -> UDMF
udmf::block convert(shared::sidedef);
udmf::block convert(shared::vertex,double xf = 1,double yf = 1);
udmf::block convert(shared::sector,double zf = 1);

//Hexen -> UDMF
udmf::block convert(hexen::linedef);
udmf::block convert(hexen::thing,double xf = 1,double yf = 1,double zf = 1);

//Doom -> UDMF
udmf::block convert(doom::linedef);
udmf::block convert(doom::thing,double xf = 1,double yf = 1,double zf = 1);

//ZDoom -> UDMF
udmf::block convert(zdoom::linedef);
udmf::block convert(zdoom::thing,double xf = 1,double yf = 1,double zf = 1);

//Strife -> UDMF
udmf::block convert(strife::linedef);
udmf::block convert(strife::thing,double xf = 1,double yf = 1,double zf = 1);

#endif
