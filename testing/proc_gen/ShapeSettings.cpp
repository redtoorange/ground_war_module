#include "ShapeSettings.h"

void ShapeSettings::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setPlanetRadius", "radius"), &ShapeSettings::setPlanetRadius);
	ClassDB::bind_method(D_METHOD("getPlanetRadius"), &ShapeSettings::getPlanetRadius);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "planet_radius"), "setPlanetRadius", "getPlanetRadius");
}
