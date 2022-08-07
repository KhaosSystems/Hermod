#include "Hermod/Sinks/ConsoleSink.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <fmt/format.h>
#include <fmt/chrono.h>

namespace Hermod
{
    ConsoleSink::ConsoleSink()
        : m_Mutex(std::mutex())
    {
        m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        m_Colors[ELevel::Trace] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        m_Colors[ELevel::Debug] = FOREGROUND_GREEN | FOREGROUND_BLUE;
        m_Colors[ELevel::Info] = FOREGROUND_GREEN;
        m_Colors[ELevel::Warning] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        m_Colors[ELevel::Error] = FOREGROUND_RED | FOREGROUND_INTENSITY;
        m_Colors[ELevel::Critical] = BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        m_Colors[ELevel::Off] = 0;
    }

    void ConsoleSink::Log(const Message &message) 
    {
        std::lock_guard<std::mutex> lock(m_Mutex);

        CONSOLE_SCREEN_BUFFER_INFO originalBufferInfo;
        if (GetConsoleScreenBufferInfo(static_cast<HANDLE>(m_ConsoleHandle), &originalBufferInfo))
        {
            auto newAttribs = static_cast<WORD>(m_Colors[message.level]) | (originalBufferInfo.wAttributes & 0xfff0);
            SetConsoleTextAttribute(static_cast<HANDLE>(m_ConsoleHandle), static_cast<WORD>(m_Colors[message.level]));
        }

        fmt::basic_memory_buffer<char, 250> buffer;
        fmt::format_to(std::back_inserter(buffer), "[{}] {}\n", message.time.time_since_epoch(), message.payload);
        WriteConsoleA(static_cast<HANDLE>(m_ConsoleHandle), buffer.data(), static_cast<DWORD>(buffer.size()), nullptr, nullptr);

        SetConsoleTextAttribute(static_cast<HANDLE>(m_ConsoleHandle), originalBufferInfo.wAttributes);
    }

    void ConsoleSink::Flush()
    {
        // Windows flushes automatically?
        // TODO: More research...
    }
}