#pragma once

#include "Core/VisibilityControl.h"
#include "Core/Sink.h"

#include <cstdio>
#include <filesystem>

namespace Hermod
{
    class HERMOD_API FileSink : public Sink
	{
	public:
		FileSink(const std::string& filename);
		~FileSink();

		virtual void Log(const Message& message) override;
		virtual void Flush() override;

	private:
		void Open(const std::string& filename)
		void Close()
		void Write(const fmt::basic_memory_buffer<char, 250>& buffer)

	private:
		std::FILE* m_File{ nullptr };
		std::filesystem::path m_Filepath;
	};
}
