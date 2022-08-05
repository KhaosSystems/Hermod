#pragma once

#include "Core/VisibilityControl.h"
#include "Core/Sink.h"

#include <mutex>

namespace Hermod
{
    class HERMOD_API ConsoleSink : public Sink
	{
	public:
		ConsoleSink();

		virtual void Log(const Message& message) override;
		virtual void Flush() override;

	protected:
		std::mutex m_Mutex;
		//std::unique_ptr<Formatter> m_Formatter;
		HANDLE m_ConsoleHandle;
		std::array<std::uint16_t, ELevel::Count> m_Colors;
	};
}
