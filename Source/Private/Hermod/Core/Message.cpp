#include "Hermod/Core/Message.h"
#include "Hermod/Core/OS.h"

namespace Hermod
{
   Message::Message(ELevel level, fmt::basic_string_view<char> message)
		: time(OS::now()), Level(level), Payload(message)
	{
	}
}