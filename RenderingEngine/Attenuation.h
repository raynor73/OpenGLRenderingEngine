#pragma once

namespace RenderingEngine
{
class Attenuation {
public:
	virtual float constant() = 0;
	virtual float linear() = 0;
	virtual float exponent() = 0;
};
}