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
#include "sharedmap.h"
#include "hexenmap.h"
#include "doommap.h"
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

//Old UDMF conversion
/*//Hexen -> UDMF
udmf::linedef chglinedef(hexen::linedef);
udmf::thing chgthing(hexen::thing);

//Doom -> UDMF
udmf::linedef chglinedef(doom::linedef);
udmf::thing chgthing(doom::thing);

//Shared -> UDMF
udmf::sidedef chgsidedef(shared::sidedef);
udmf::vertex chgvertex(shared::vertex);
udmf::sector chgsector(shared::sector);*/

#endif
