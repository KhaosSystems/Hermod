#include "Hermod/Sinks/FileSink.h"

#include <cassert>

namespace Hermod
{
    FileSink::FileSink(const std::string &filename)
    {
        Open(filename);
    }

    FileSink::~FileSink()
    {
        Close();
    }

    void FileSink::Log(const Message &message)
    {

        fmt::basic_memory_buffer<char, 250> buffer;
        fmt::format_to(std::back_inserter(buffer), "[{}] {}\n", message.time.time_since_epoch(), message.Payload);
        Write(buffer);
    }

    void FileSink::Flush()
    {
        if (std::fflush(m_File) != 0)
        {
            assert(false);
            // "Failed flush to file " + os::filename_to_str(filename_), errno);
        }
    }

    void FileSink::Open(const std::string &filename)
    {
        Close();

        m_Filepath = std::filesystem::path(filename);

        // Create containing folder if doesn't exists already.
        if (m_Filepath.has_parent_path() && !std::filesystem::exists(m_Filepath.parent_path()))
        {
            std::filesystem::create_directory(m_Filepath.parent_path());
        }

        m_File = std::fopen(m_Filepath.string().c_str(), "ab");
    }

    void FileSink::Close()
    {
        if (m_File != nullptr)
        {
            std::fclose(m_File);
        }
    }

    void FileSink::Write(const fmt::basic_memory_buffer<char, 250> &buffer)
    {
        if (std::fwrite(buffer.data(), 1, buffer.size(), m_File) != buffer.size())
        {
            assert(false);
            // "Failed writing to file " + os::filename_to_str(filename_), errno);
        }
    }
}