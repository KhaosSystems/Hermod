#pragma once

namespace Hermod
{
	namespace OS
	{
		std::chrono::system_clock::time_point now()
		{
			/*#if defined __linux__ && defined SPDLOG_CLOCK_COARSE
			    timespec ts;
			    ::clock_gettime(CLOCK_REALTIME_COARSE, &ts);
			    return std::chrono::time_point<std::chrono::system_clock, typename std::chrono::system_clock::duration>(std::chrono::duration_cast<typename std::chrono::system_clock::duration>(std::chrono::seconds(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec)));
            #else
			    return std::chrono::system_clock::now();
            #endif*/

			return std::chrono::system_clock::now();
		}
	}	
}