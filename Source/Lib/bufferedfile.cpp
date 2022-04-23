#include "Lib/BufferedFile.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

using namespace std;

BufferedFile::BufferedFile(string Name, string Mode)
{
	fopen_s(&File, Name.c_str(), Mode.c_str());

	fseek(File, 0, SEEK_END);
	int Size = ftell(File);
	fseek(File, 0, SEEK_SET);
		
	Buffer = (char*) malloc(Size + 1);
		
	fread(Buffer, 1, Size, File);
}

BufferedFile::~BufferedFile()
{
	free(Buffer);
}
