#ifndef BASE_BUILDING_H
#define BASE_BUILDING_H

#include "scene/2d/node_2d.h"

class BaseBuilding : public Node2D  {
	GDCLASS(BaseBuilding, Node2D);

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

#endif

