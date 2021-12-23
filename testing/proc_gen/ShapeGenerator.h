#pragma once
#include "ShapeSettings.h"

class ShapeGenerator {

public:
	ShapeGenerator(Ref<ShapeSettings> p_shapeSettings) :
		shapeSettings(p_shapeSettings) {
	}

	Vector3 calculatePointOnPlanet(const Vector3 &pointOnUnitSphere) {
		if (shapeSettings.is_valid()) {
			return pointOnUnitSphere * shapeSettings->getPlanetRadius();
		}

		print_error("Null ShapeSettings inside ShapeGenerator");
		return { 0, 0, 0 };
	}

private:
	Ref<ShapeSettings> shapeSettings;
};
