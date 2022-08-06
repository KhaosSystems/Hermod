#include "Hermod/Core/Logger.h"
#include "Hermod/Sinks/ConsoleSink.h"

namespace Hermod
{
	Logger::Logger(std::initializer_list<std::shared_ptr<Sink>> sinks)
		: m_Sinks(sinks.begin(), sinks.end())
	{
		level = ELevel::Error;
		
		Logger* t = this;
		Log<ELevel::Warning>("This works2...");
	}

    void Logger::SetLevel(ELevel level)
    {
		Log<ELevel::Warning>("This works...");
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