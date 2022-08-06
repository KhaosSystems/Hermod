#pragma once

#include "Hermod/Core/VisibilityControl.h"
#include "Hermod/Core/Sink.h"

#include <mutex>
#include <cstdint>
#include <array>

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
		void* m_ConsoleHandle;
		std::array<std::uint16_t, ELevel::Count> m_Colors;
	};
}
