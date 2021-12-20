#ifndef SHAPE_SETTINGS_H
#define SHAPE_SETTINGS_H

#include "core/io/resource.h"

class ShapeSettings : public Resource {
	GDCLASS(ShapeSettings, Resource);
public:
	void setPlanetRadius(int p_radius) { planetRadius = p_radius; }
	int getPlanetRadius() const { return planetRadius; }

protected:
	static void _bind_methods();

public:
	float planetRadius;
};

#endif
