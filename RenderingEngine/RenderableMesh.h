#pragma once

#include <cstdint>
#include <memory>
#include "Transformation.h"
#include "Material.h"
#include <vector>
#include <string>

namespace RenderingEngine {
	class RenderableMesh {
		
		bool m_isEnabled;
		uint32_t m_id;

		std::shared_ptr<Transformation> m_transformation;
		std::shared_ptr<Material> m_material;

		std::vector<std::string> m_layers;

		static uint32_t s_nextId;

	public:
		RenderableMesh(
			std::shared_ptr<Transformation> transformation,
			std::shared_ptr<Material> material,
			const std::vector<std::string> &layers
		) : m_isEnabled(true),
			m_id(s_nextId++),
			m_transformation(transformation), 
			m_material(material),
			m_layers(layers)
		{}

		bool isEnabled() const { return m_isEnabled; }
		void setEnabled(bool isEnabled) { m_isEnabled = isEnabled; }

		std::shared_ptr<Transformation> transformation() { return m_transformation; }
		std::shared_ptr<Material> material() { return m_material; }

		const std::vector<std::string> &layers() { return m_layers; }

		uint32_t id() const { return m_id; }

		virtual bool isValid() const = 0;
	};
}