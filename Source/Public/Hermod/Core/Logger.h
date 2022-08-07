#pragma once

#include "Hermod/Core/VisibilityControl.h"
#include "Hermod/Core/Sink.h"
#include "Hermod/Core/Level.h"
#include "Hermod/Core/Message.h"

#include <initializer_list>
#include <memory>
#include <atomic>
#include <vector>

#include <fmt/format.h>
#include <fmt/chrono.h>

#include <iostream>

namespace Hermod
{
	class HERMOD_API Logger
	{
	public:
		Logger(std::initializer_list<std::shared_ptr<Sink>> sinks);

		template<ELevel Level, typename... Args>
		void Log(const char* format, Args&&... args)
		{
			LogInternal(Level, format, std::forward<Args>(args)...);
		}

		void SetLevel(ELevel level);
		ELevel GetLevel();

	public:
		ELevel level;

	private:
		template<typename... Args>
		void LogInternal(ELevel level, fmt::basic_string_view<char> format, Args &&... args)
		{
			fmt::basic_memory_buffer<char, 250> buffer;
			fmt::detail::vformat_to(buffer, format, fmt::make_format_args(std::forward<Args>(args)...));

			Message message(level, fmt::basic_string_view<char>(buffer.data(), buffer.size()));

			for (auto& sink : m_Sinks)
			{
				if (sink->ShouldLog(message.level))
				{
					sink->Log(message);
				}
			}

			if (ShouldFlush(message))
			{
				for (auto& sink : m_Sinks)
				{
					sink->Flush();
				}
			}
		}

		bool ShouldFlush(const Message& message);

	protected:
		std::vector<std::shared_ptr<Sink>> m_Sinks;
		std::atomic<std::underlying_type_t<ELevel>> m_Level = ELevel::Info;
		std::atomic<std::underlying_type_t<ELevel>> m_FlushLevel = ELevel::Off;
	};

}
