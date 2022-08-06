#pragma once

#include "Hermod/Core/VisibilityControl.h"
#include "Hermod/Core/Level.h"
#include "Hermod/Core/Message.h"

#include <atomic>

namespace Hermod
{
    class HERMOD_API Sink
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
}