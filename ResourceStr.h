/*******************************************************************************
 * This program and the accompanying materials
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution, and is available at 
 * http://www.eclipse.org/legal/cpl-v10.html
 * 
 * Contributors:
 *     Peter Smith
 *******************************************************************************/
const unsigned int LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 0x00000040;

#if defined(_WIN64)
 typedef unsigned __int64 ULONG_PTR;
#else
 typedef unsigned long ULONG_PTR;
#endif

 #if defined(_WIN64)
 typedef __int64 LONG_PTR; 
#else
 typedef long LONG_PTR;
#endif


#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)

typedef struct
{
	LPCTSTR lpType;
	LPCTSTR lpName;
	WORD wLang;
} ResourceInfo;

typedef struct
{
	WORD count;
	WORD max;
	ResourceInfo* ri;
} ResourceInfoList;

typedef struct 
{
	BYTE width;
	BYTE height;
	BYTE colorCount;
	BYTE reserved;
	WORD planes;
	WORD bitCount;
	DWORD bytesInRes;
	DWORD imageOffset;
} ICONENTRY;

typedef struct  
{
	WORD reserved;
	WORD type;
	WORD count;
	ICONENTRY entries[1];
} ICONHEADER;

typedef struct 
{
	BITMAPINFOHEADER header;
	RGBQUAD colors;
	BYTE xors[1];
	BYTE ands[1];
} ICONIMAGE;

#pragma pack(push)
#pragma pack(2)

typedef struct
{
	BYTE width;
	BYTE height;
	BYTE colourCount;
	BYTE reserved;
	BYTE planes;
	BYTE bitCount;
	WORD bytesInRes;
	WORD bytesInRes2;
	WORD reserved2;
	WORD id;
} GRPICONENTRY;

typedef struct 
{
	WORD reserved;
	WORD type;
	WORD count;
	GRPICONENTRY entries[1];
} GRPICONHEADER;

#pragma pack(pop)

