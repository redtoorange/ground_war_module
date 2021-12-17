#ifndef SHAPE_SETTINGS_H
#define SHAPE_SETTINGS_H

#include "core/io/resource.h"

class ShapeSettings : public Resource {
	GDCLASS(ShapeSettings, Resource);

protected:
	static void _bind_methods();
};

#endif
