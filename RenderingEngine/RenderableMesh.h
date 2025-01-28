#pragma once

#include <cstdint>

namespace RenderingEngine {
	class RenderableMesh {
		
		bool m_isEnabled;
		uint32_t m_id;

		static uint32_t s_nextId;

	public:
		RenderableMesh() : m_isEnabled(true), m_id(s_nextId++) {}

		bool isEnabled() const { return m_isEnabled; }
		void setEnabled(bool isEnabled) { m_isEnabled = isEnabled; }

		uint32_t id() const { return m_id; }

		virtual bool isValid() const = 0;
	};
}