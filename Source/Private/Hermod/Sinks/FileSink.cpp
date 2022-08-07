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
        fmt::format_to(std::back_inserter(buffer), "[{}] {}\n", message.time.time_since_epoch(), message.payload);
        Write(buffer);
    }

    void FileSink::Flush()
    {
        if (std::fflush(file) != 0)
        {
            assert(false);
            // "Failed flush to file " + os::filename_to_str(filename_), errno);
        }
    }

    void FileSink::Open(const std::string &filename)
    {
        Close();

        filepath = std::filesystem::path(filename);

        // Create containing folder if doesn't exists already.
        if (filepath.has_parent_path() && !std::filesystem::exists(filepath.parent_path()))
        {
            std::filesystem::create_directory(filepath.parent_path());
        }

        file = std::fopen(filepath.string().c_str(), "ab");
    }

    void FileSink::Close()
    {
        if (file != nullptr)
        {
            std::fclose(file);
        }
    }

    void FileSink::Write(const fmt::basic_memory_buffer<char, 250> &buffer)
    {
        if (std::fwrite(buffer.data(), 1, buffer.size(), file) != buffer.size())
        {
            assert(false);
            // "Failed writing to file " + os::filename_to_str(filename_), errno);
        }
    }
}