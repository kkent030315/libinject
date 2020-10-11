#pragma once
#include <Windows.h>
#include <cstdint>

namespace memory
{
	template<class T>
	__forceinline bool write(
		HANDLE process_handle,
		uint64_t address,
		T value
	)
	{
		return WriteProcessMemory(
			process_handle,
			(LPVOID)address,
			&value,
			sizeof(T),
			nullptr
		);
	}

	__forceinline bool write_raw(
		HANDLE process_handle,
		uint64_t address,
		void* buffer,
		size_t size
	)
	{
		return WriteProcessMemory(
			process_handle,
			(LPVOID)address,
			buffer,
			size,
			nullptr
		);
	}

	template<class T>
	__forceinline T read(
		HANDLE process_handle,
		uint64_t address
	)
	{
		T buffer;

		ReadProcessMemory(
			process_handle,
			(LPCVOID)address,
			&buffer,
			sizeof(T),
			nullptr
		);

		return buffer;
	}

	__forceinline bool read_raw(
		HANDLE process_handle,
		uint64_t address,
		void* buffer,
		size_t size
	)
	{
		return ReadProcessMemory(
			process_handle,
			(LPCVOID)address,
			buffer,
			size,
			nullptr
		);
	}

	__forceinline void* allocate(
		HANDLE process_handle,
		uint64_t address,
		size_t size,
		DWORD allocate_type,
		DWORD protection
	)
	{
		return VirtualAllocEx(
			process_handle,
			(LPVOID)address,
			size,
			allocate_type,
			protection
		);
	}
}