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

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "convert.h"
#include "exceptions.h"

#ifdef HEXEN
#define format hexen
#define format_namespace "Hexen"
#elif defined(ZDOOM)
#define format zdoom
#define format_namespace "ZDoom"
#elif defined(DOOM)
#define format doom
#define format_namespace "Doom"
#elif defined(STRIFE)
#error Strife is not supported (yet)
#else
#error No input format defined
#endif

//EOF is thrown by getbyte_e in mapread.h
#define eofloop(i) try { while (1) { i; } } catch (exception::eof problem) {}

void getlong(FILE *f,long &i)
{
	i = fgetc(f);
	i |= (fgetc(f) << (8 * 1));
	i |= (fgetc(f) << (8 * 2));
	i |= (fgetc(f) << (8 * 3));
}

char *strtoupper(char *);
void showhelp(int,char**);
int scanparm(int,char **,const char *);
char *grabparm(int,char **,int);
char *shiftparm(int,char**);
FILE *fopen_e(const char*,const char*);
FILE *extractlump(FILE *wad,long f_size);

bool dolog;
inline void log(const char *msg)
{
	if (!dolog)
		return;
	std::cout << msg << std::endl;
}

int main(int argc,char **argv)
{
	try
	{
		dolog = (!!scanparm(argc,argv,"-v"));
		double xfactor = 1;
		if (int xpos = scanparm(argc,argv,"-xf"))
			if ((xfactor = strtod(grabparm(argc,argv,xpos + 1),0)) == 0)
			{
				throw exception::root("Invalid value after -xf");
			}
		double yfactor = 1;
		if (int ypos = scanparm(argc,argv,"-yf"))
			if ((yfactor = strtod(grabparm(argc,argv,ypos + 1),0)) == 0)
			{
				throw exception::root("Invalid value after -yf");
			}
		double zfactor = 1;
		if (int zpos = scanparm(argc,argv,"-zf"))
			if ((zfactor = strtod(grabparm(argc,argv,zpos + 1),0)) == 0)
			{
				throw exception::root("Invalid value after -zf");
			}
		char *tm_fname;
		if (scanparm(argc,argv,"-h"))
		{
			showhelp(argc,argv);
			return 0;
		}
		FILE *THINGS = 0;
		FILE *LINEDEFS = 0;
		FILE *SIDEDEFS = 0;
		FILE *VERTEXES = 0;
		FILE *SECTORS = 0;
		if (int wpos = scanparm(argc,argv,"-w"))
		{
			grabparm(argc,argv,wpos + 3);
			FILE *wad;
			log("Opening wad file...");
			wad = fopen_e(grabparm(argc,argv,wpos + 1),"rb");
			log("Reading wad header...");
			int dirofs;
			int lumpcount;
			long filesize;
			fseek(wad,0,SEEK_END);
			filesize = ftell(wad);
			if (filesize < 12)
			{
				throw exception::root("Wad is less than 12 bytes large (invalid wad)");
			}
			fseek(wad,0,SEEK_SET);
			char type[5];
			for (int i = 0;i < 4;i++)
			{
				type[i] = fgetc(wad);
			}
			type[4] = 0;
			std::cout << "WAD Type: " << type << std::endl;
			lumpcount = fgetc(wad);
			lumpcount |= (fgetc(wad) << (8 * 1));
			lumpcount |= (fgetc(wad) << (8 * 2));
			lumpcount |= (fgetc(wad) << (8 * 3));
			if (lumpcount <= 0)
			{
				throw exception::root("Wad lump count less than 1 (empty wad)");
			}
			dirofs = fgetc(wad);
			dirofs |= (fgetc(wad) << (8 * 1));
			dirofs |= (fgetc(wad) << (8 * 2));
			dirofs |= (fgetc(wad) << (8 * 3));
			if ((dirofs < 0) || ((dirofs + (16 * lumpcount)) > filesize))
			{
				throw exception::root("Lump directory outside of WAD file (invalid wad)");
			}
			fseek(wad,dirofs,SEEK_SET);
			log("Searching for map lump...");
			char lumpname[9];
			lumpname[8] = 0;
			strtoupper(grabparm(argc,argv,wpos + 2));
			for (int i = 0;i < lumpcount;i++)
			{
				fseek(wad,8,SEEK_CUR);
				for (int j = 0;j < 8;j++)
					lumpname[j] = fgetc(wad);
				if (!strcmp(lumpname,grabparm(argc,argv,wpos + 2)))
					break;
				if (i == lumpcount - 1)
				{
					throw exception::root("Map lump not found");
				}
			}
			log("Extracting lumps...");
			THINGS = extractlump(wad,filesize);
			LINEDEFS = extractlump(wad,filesize);
			SIDEDEFS = extractlump(wad,filesize);
			VERTEXES = extractlump(wad,filesize);
			fseek(wad,16 * 3,SEEK_CUR);
			SECTORS = extractlump(wad,filesize);
			log("Closing wad file...");
			fclose(wad);
			tm_fname = grabparm(argc,argv,wpos + 3);
		}
		else
		{
			log("Opening THINGS...");
			THINGS = fopen_e(shiftparm(argc,argv),"rb");
			log("Opening LINEDEFS...");
			LINEDEFS = fopen_e(shiftparm(argc,argv),"rb");
			log("Opening SIDEDEFS...");
			SIDEDEFS = fopen_e(shiftparm(argc,argv),"rb");
			log("Opening VERTEXES...");
			VERTEXES = fopen_e(shiftparm(argc,argv),"rb");
			log("Opening SECTORS...");
			SECTORS = fopen_e(shiftparm(argc,argv),"rb");
			tm_fname = shiftparm(argc,argv);
		}
		log("Checking if TEXTMAP already exists...");
		if (!scanparm(argc,argv,"-f") && fopen(tm_fname,"rb"))
		{
			char verify[10];
			std::cout << tm_fname << " already exists. Overwrite? (Y/N)";
			std::cin.getline(verify,10);
			if (strcmp("Y",strtoupper(verify)))
			{
				std::cout << "Aborting...";
				std::cout << std::endl;
				return 2;
			}
		}
		log("Opening TEXTMAP...");
		FILE *textmap_check;
		textmap_check = fopen(tm_fname,"w");	//Ugly, but I see no other way
		if (textmap_check == 0)
		{
			throw exception::file_error(tm_fname);
		}
		fclose(textmap_check);
		std::ofstream TEXTMAP(tm_fname);
		log("Writing Namespace...");
		int pos;
		pos = scanparm(argc,argv,"-n");
		TEXTMAP << "Namespace = \"" << (pos ? grabparm(argc,argv,pos + 1) : format_namespace) << "\";\n\n";
		log("Converting things...");
		eofloop(udmf::writeblock("thing",convert(format::getthing(THINGS),xfactor,yfactor),TEXTMAP));
		log("Converting linedefs...");
		eofloop(udmf::writeblock("linedef",convert(format::getlinedef(LINEDEFS)),TEXTMAP));
		log("Converting sidedefs...");
		eofloop(udmf::writeblock("sidedef",convert(format::getsidedef(SIDEDEFS)),TEXTMAP));
		log("Converting vertexes...");
		eofloop(udmf::writeblock("vertex",convert(format::getvertex(VERTEXES),xfactor,yfactor),TEXTMAP));
		log("Converting sectors...");
		eofloop(udmf::writeblock("sector",convert(format::getsector(SECTORS),zfactor),TEXTMAP));
		log("Closing files...");
		std::cout << "Conversion complete!" << std::endl;
		return 0;
	}
	catch (exception::missing_args problem)
	{
		std::cerr << "Missing arguments. Run with -h for help." << std::endl;
		return 0;
	}
	catch (exception::root problem)
	{
		std::cerr << problem.what() << std::endl;
		return 0;
	}
	catch (std::exception problem)
	{
		std::cerr << "Error: \"" << problem.what() << "\"!" << std::endl;
		return 255;
	}
}

void showhelp(int argc,char **argv)
{
	std::cout << argv[0] << " -h" << std::endl;
	std::cout << argv[0] << " THINGS LINEDEFS SIDEDEFS VERTEXES SECTORS TEXTMAP [-f] [-v] [-n NAMESPACE]" << std::endl;
	std::cout << argv[0] << " -w WADFILE MAPNAME TEXTMAP [-f] [-v] [-n NAMESPACE]" << std::endl;
	std::cout << std::endl;
	std::cout << "THINGS\t\tInput filename for THINGS lump" << std::endl;
	std::cout << "LINEDEFS\tInput filename for LINEDEFS lump" << std::endl;
	std::cout << "SIDEDEFS\tInput filename for SIDEDEFS lump" << std::endl;
	std::cout << "VERTEXES\tInput filename for VERTEXES lump" << std::endl;
	std::cout << "SECTORS\t\tInput filename for SECTORS lump" << std::endl;
	std::cout << "WADFILE\t\tInput filename of WAD-Format file" << std::endl;
	std::cout << "MAPNAME\t\tMap lumpname from WADFILE" << std::endl;
	std::cout << "TEXTMAP\t\tOutput filename for TEXTMAP data" << std::endl;
	std::cout << "NAMESPACE\tThe namespace to be used for TEXTMAP" << std::endl;
	std::cout << "-h\t\tDisplay this message" << std::endl;
	std::cout << "-f\t\tDon't prompt for overwrite of TEXTMAP" << std::endl;
	std::cout << "-v\t\tGenerate more output messages" << std::endl;
	std::cout << "-n\t\tManually choose a namespace for TEXTMAP" << std::endl;
}

int scanparm(int argc,char **argv,const char *find)
{
	if (argc <= 1)
	{
		return 0;
	}
	unsigned int pos = 1;
	while (strcmp(find,argv[pos]))
	{
		pos++;
		if ((unsigned int)argc <= pos)
		{
			return 0;
		}
	}
	return pos;
}

char *grabparm(int argc,char **argv,int pos)
{
	if (argc <= pos)
	{
		throw exception::missing_args();
	}
	return argv[pos];
}

char *shiftparm(int argc,char **argv)
{
	static int pos = 1;
	if (argc <= pos)
	{
		throw exception::missing_args();
	}
	return argv[pos++];
}

FILE *fopen_e(const char *filename,const char *mode)
{
	FILE *result;
	result = fopen(filename,mode);
	if (!result)
	{
		throw exception::file_error(filename);
	}
	return result;
}

FILE *extractlump(FILE *wad,long f_size)
{
	long f_pos;
	long f_ofs;
	long f_len;
	f_pos = ftell(wad);
	getlong(wad,f_ofs);
	getlong(wad,f_len);
	if (((f_ofs + f_len) > f_size) || (f_ofs < 0))
	{
		throw exception::root("Part or all of lump data outside wad file");
	}
	if (f_len < 0)
	{
		throw exception::root("Lump has negative length");
	}
	fseek(wad,f_ofs,SEEK_SET);
	FILE *tmp;
	tmp = tmpfile();
	log("Extracting lump...");
	for (int i = 0;i < f_len;i++)
		fputc(fgetc(wad),tmp);
	fseek(tmp,0,SEEK_SET);
	fseek(wad,f_pos + 16,SEEK_SET);
	return tmp;
}

char *strtoupper(char *str)
{
	char *upr;
	upr = str;
	while (*upr)
	{
		*upr = toupper(*upr);
		upr++;
	}
	return str;
}
