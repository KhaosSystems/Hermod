#include "Core/Message.h"

#include "Core/OS.h"

namespace Hermod
{
   Message::Message(ELevel level, fmt::basic_string_view<char> message)
		: time(OS::now()), Level(level), Payload(message)
	{
	}
}