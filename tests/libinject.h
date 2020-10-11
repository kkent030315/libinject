#pragma once
#include <Windows.h>
#include <string>

//
// inject any dlls to the target process.
//
bool inject(
	const uint32_t process_id,
	const std::string_view dll_path,
	bool elevate_handle
);