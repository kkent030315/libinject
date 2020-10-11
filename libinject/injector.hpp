#pragma once
#include <Windows.h>
#include <string>
#include <cstdint>

#include "libelevate.h"
#include "memory_utils.hpp"

#define CHECK_HANDLE(x) (x && x != INVALID_HANDLE_VALUE)
#define RET_CHECK(x) if(!x) return false;

namespace injector
{
	bool perform_inject(
		const uint32_t process_id,
		const std::string_view dll_path,
		bool elevate_handle
	);
}