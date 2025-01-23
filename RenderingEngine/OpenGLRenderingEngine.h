#pragma once

#include "RenderableMesh.h"
#include "Mesh.h"
#include "Transformation.h"
#include "Material.h"
#include "Camera.h"

namespace RenderingEngine {
	class OpenGLRenderingEngine {


	public:
		RenderableMesh& createRenderableMesh(
			const Mesh& mesh,
			const Transformation& transformation,
			const Material& material
		);

		void render(Camera& camera);
	};
}
