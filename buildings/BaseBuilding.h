#pragma once

#include "scene/2d/node_2d.h"

class BaseBuilding : public Node2D  {
	GDCLASS(BaseBuilding, Node2D);

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

