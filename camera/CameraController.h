#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "scene/2d/node_2d.h"

class CameraController : public Node2D  {
	GDCLASS(CameraController, Node2D);

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

#endif

