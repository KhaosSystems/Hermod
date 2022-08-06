#pragma once

#include "Hermod/Core/VisibilityControl.h"

#include <stdint.h>

namespace Hermod
{
    enum HERMOD_API ELevel : uint8_t
	{
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Critical,
		Off,
		Count
	};

}