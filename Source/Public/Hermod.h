#pragma once

#include <initializer_list>
#include <vector>
#include <atomic>
#include <memory>
#include <array>
#include <mutex>
#include <filesystem>
#include <assert.h>
#include <chrono>

#include "Core/VisibilityControl.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


namespace Hermod
{
	namespace OS
	{
		std::chrono::system_clock::time_point HERMOD_API now();
	}

	

	

	
}