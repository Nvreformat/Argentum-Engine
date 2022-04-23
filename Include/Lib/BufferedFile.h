#ifndef BUFFEREDFILE_H
#define BUFFEREDFILE_H

#include <string>
#include <stdint.h>

struct MapHeader
{
	char Description[255];
	uint32_t CRC;
	uint32_t Magic;
}; //__attribute__((packed));

struct BufferedFile
{
	FILE* File;
	char* Buffer;
	int Position = 0;

	BufferedFile(std::string Name, std::string Mode);
	~BufferedFile();
	
	template <typename T>
	T Read(T* Buff)
	{
		*Buff = *((T*) ((char*)Buffer + Position));
		Position += sizeof(T);
	
		return *Buff;
	}
};

#endif
