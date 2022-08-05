#include "Core/Logger.h"

namespace Hermod
{
    Logger::Logger()
		: m_Sinks()
	{
	}

	Logger::Logger(std::initializer_list<std::shared_ptr<Sink>> sinks)
		: m_Sinks(sinks.begin(), sinks.end())
	{
	}

    void Logger::SetLevel(ELevel level)
    {
        /* ... */
    }

	ELevel Logger::GetLevel()
    {
        return static_cast<ELevel>(m_Level.load(std::memory_order_relaxed));
    }

    bool Logger::ShouldFlush(const Message& message)
	{
		auto flushLevel = m_FlushLevel.load(std::memory_order_relaxed);
		return (message.Level >= flushLevel) && (message.Level != ELevel::Off);
	}
}