#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <stdint.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

struct TCPPacket
{
	// Both write and read operations share the same buffer because they aren't mean to be called both in the same Packet
	std::vector<char> Buffer;
	std::size_t Pos = 0;

	template <typename T>
	T Read(T* Buff)
	{
		*Buff = *((T*) (&Buffer[Pos]));
		Pos += sizeof(T);

		return *Buff;
	}

	std::string ReadString()
	{
		std::string Return = "";
		uint16 Size = Read(&Size);

		for (int I = 0; I < Size; I++)
		{
			char Character = Read(&Character);

			Return.push_back(Character);
		}

		return Return;
	}

	template <typename T>
	void Write(T Value)
	{
		Buffer.resize(Buffer.size() + sizeof(T));

		T* Pointer = (T*) (&Buffer[Pos]);

		*Pointer = Value;
		Pos += sizeof(T);
	}

	void Write(std::string Value)
	{
		uint16 Size = Value.size();
		const char* CString = Value.c_str();

		*this << Size;

		for (int I = 0; I < Size; I++)
		{
			*this << CString[I];
		}
	}

	void Write(const char* Value)
	{
		Write(std::string(Value));
	}

	template <typename T>
	TCPPacket& operator<<(T Data)
	{
		Write(Data);

		return *this;
	}

	template <typename T>
	TCPPacket& operator>>(T& Data)
	{
		Data = Read(Data);

		return *this;
	}
};

struct TCPSocket
{
	int Socket;

	bool Connect(std::string Host, int Port);
	void SetBlocking(bool Blocking);

	void Send(TCPPacket& Packet);
	void Read(TCPPacket& Packet);
};

#endif
