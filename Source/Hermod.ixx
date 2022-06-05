module;

#include <initializer_list>
#include <vector>
#include <atomic>
#include <memory>
#include <array>

#include <fmt/format.h>

#include <Windows.h>

export module Hermod;

namespace Hermod
{
	export enum ELevel : uint8_t
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

	export struct Message
	{
		Message(ELevel level, fmt::basic_string_view<char> message)
			: Level(level), Payload(message)
		{
		}

		ELevel Level{ ELevel::Off };
		fmt::basic_string_view<char> Payload;
	};

	export class Sink
	{
	public:
		virtual ~Sink() = default;

		virtual void Log(const Message& message) = 0;
		virtual void Flush() = 0;

		void SetLevel(ELevel level)
		{
			m_Level.store(static_cast<std::underlying_type_t<ELevel>>(level), std::memory_order_relaxed);
		}

		ELevel GetLevel() const
		{
			return static_cast<ELevel>(m_Level.load(std::memory_order_relaxed));
		}

		bool ShouldLog(ELevel level)
		{
			return static_cast<std::underlying_type_t<ELevel>>(level) >= static_cast<std::underlying_type_t<ELevel>>(m_Level.load(std::memory_order_relaxed));
		}

	protected:
		std::atomic<std::underlying_type_t<ELevel>> m_Level{ static_cast<std::underlying_type_t<ELevel>>(ELevel::Trace) };
	};

	export class Logger
	{
	public:
		Logger()
			: m_Sinks()
		{
		}

		Logger(std::initializer_list<std::shared_ptr<Sink>> sinks)
			: m_Sinks(sinks.begin(), sinks.end())
		{
		}

		template<ELevel Level, typename... Args>
		void Log(const char* format, const Args&... args)
		{
			LogInternal(Level, format, std::forward<Args>(args)...);
		}

		void SetLevel(ELevel level) { /* ... */ }
		ELevel GetLevel() { return static_cast<ELevel>(m_Level.load(std::memory_order_relaxed)); }

	private:
		template<typename... Args>
		void LogInternal(ELevel level, fmt::basic_string_view<char> format, Args &&... args)
		{
			fmt::basic_memory_buffer<char, 250> buffer;
            fmt::detail::vformat_to(buffer, format, fmt::make_format_args(std::forward<Args>(args)...));

			Message message(level, fmt::basic_string_view<char>(buffer.data(), buffer.size()));

			for (auto& sink : m_Sinks)
			{
				if (sink->ShouldLog(message.Level))
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

		inline bool ShouldFlush(const Message& message)
		{
			auto flushLevel = m_FlushLevel.load(std::memory_order_relaxed);
			return (message.Level >= flushLevel) && (message.Level != ELevel::Off);
		}

	protected:
		std::vector<std::shared_ptr<Sink>> m_Sinks;
		std::atomic<std::underlying_type_t<ELevel>> m_Level{ ELevel::Info };
		std::atomic<std::underlying_type_t<ELevel>> m_FlushLevel{ ELevel::Off };
	};

	// Sinks
	export class ConsoleSink : public Sink
	{
	public:
		ConsoleSink()
		{
			m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			m_Colors[ELevel::Trace] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;     // white
			m_Colors[ELevel::Debug] = FOREGROUND_GREEN | FOREGROUND_BLUE;                      // cyan
			m_Colors[ELevel::Info] = FOREGROUND_GREEN;                                         // green
			m_Colors[ELevel::Warning] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; // intense yellow
			m_Colors[ELevel::Error] = FOREGROUND_RED | FOREGROUND_INTENSITY;                     // intense red
			m_Colors[ELevel::Critical] = BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // intense white on red background
			m_Colors[ELevel::Off] = 0;
		}

		virtual void Log(const Message& message) override
		{
			CONSOLE_SCREEN_BUFFER_INFO originalBufferInfo;
			if (GetConsoleScreenBufferInfo(static_cast<HANDLE>(m_ConsoleHandle), &originalBufferInfo))
			{
				auto newAttribs = static_cast<WORD>(m_Colors[message.Level]) | (originalBufferInfo.wAttributes & 0xfff0);
				auto ignored = SetConsoleTextAttribute(static_cast<HANDLE>(m_ConsoleHandle), static_cast<WORD>(m_Colors[message.Level])); // This breaks stuff?
				(void)(ignored); // What's up with this?
			}
			
			fmt::basic_memory_buffer<char, 250> buffer;
			fmt::format_to(std::back_inserter(buffer), "[TIME] {}\n", message.Payload);
			WriteConsoleA(static_cast<HANDLE>(m_ConsoleHandle), buffer.data(), static_cast<DWORD>(buffer.size()), nullptr, nullptr);

			SetConsoleTextAttribute(static_cast<HANDLE>(m_ConsoleHandle), originalBufferInfo.wAttributes);
		}

		virtual void Flush() override {}

	protected:
		//std::unique_ptr<Formatter> m_Formatter;
		HANDLE m_ConsoleHandle;
		std::array<std::uint16_t, ELevel::Count> m_Colors;

	};
}
