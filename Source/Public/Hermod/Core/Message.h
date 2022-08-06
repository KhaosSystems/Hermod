#pragma once

#include "Hermod/Core/VisibilityControl.h"
#include "Hermod/Core/Level.h"

#include <fmt/format.h>
#include <fmt/chrono.h>

namespace Hermod
{
	struct HERMOD_API Message
	{
		Message(ELevel level, fmt::basic_string_view<char> message);

		std::chrono::system_clock::time_point time;
		ELevel Level{ ELevel::Off };
		fmt::basic_string_view<char> Payload;
	};
}
