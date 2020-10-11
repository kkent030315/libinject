#include "pch.h"
#include "framework.h"

#include "injector.hpp"

//
// wrapper for the inject behavior
//
bool inject(
	const uint32_t process_id,
	const std::string_view dll_path,
	bool elevate_handle
)
{
	return injector::perform_inject(
		process_id,
		dll_path,
		elevate_handle
	);
}