#pragma once

namespace RenderingEngine {
	class RenderableMesh {
		
		bool isEnabled;

	public:
		RenderableMesh() : isEnabled(true) {}

		bool isEnabled() const { return isEnabled; }
		void setEnabled(bool isEnabled) { this->isEnabled = isEnabled; }
	};
}