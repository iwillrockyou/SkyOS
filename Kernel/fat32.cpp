#include "fat32.h"
#include "string.h"
#include "FAT.h"

FILESYSTEM g_fat32FileSys;

FILE fsysFat32Directory(const char* DirectoryName) {

	FILE file;
	file.flags = FS_INVALID;
	return file;
}

/**
*	Reads from a file
*/
void fsysFat32Read(PFILE file, unsigned char* Buffer, unsigned int Length) {

	if (file) {
		FATReadFile(file->id, Length, Buffer);
	}
}

/**
*	Closes file
*/
void fsysFat32Close(PFILE file) {

	if (file->flags == FS_FILE && file->id != 0)
		FATIsEndOfFile(file->id);
}


/**
*	Opens a file
*/
FILE fsysFat32Open(const char* FileName) {

	FILE ret;
	UINT16 handle = FATFileOpen((char*)FileName, 0);

	if (handle == 0)
		ret.flags = FS_INVALID;
	else
	{
		ret.flags = FS_FILE;
		ret.id = handle;
	}

	return ret;
}


void fsysFat32Mount() {


}


bool VFSInitialize()
{

	//! initialize filesystem struct
	strcpy(g_fat32FileSys.Name, "FAT32");
	g_fat32FileSys.Directory = fsysFat32Directory;
	g_fat32FileSys.Mount = fsysFat32Mount;
	g_fat32FileSys.Open = fsysFat32Open;
	g_fat32FileSys.Read = fsysFat32Read;
	g_fat32FileSys.Close = fsysFat32Close;

	//! register ourself to volume manager
	volRegisterFileSystem(&g_fat32FileSys, 0);

	return true;
}