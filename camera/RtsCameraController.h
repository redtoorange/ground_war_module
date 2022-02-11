#pragma once

#include "scene/2d/node_2d.h"

class Camera2D;

class RtsCameraController : public Node2D {
	GDCLASS(RtsCameraController, Node2D);

public:
	RtsCameraController();

	float get_camera_speed() const;
	void set_camera_speed(float p_cameraSpeed);

	float get_camera_fast_multiplier() const;
	void set_camera_fast_multiplier(float p_cameraFastMultiplier);

	float get_min_zoom() const;
	void set_min_zoom(float p_minZoom);

	float get_max_zoom() const;
	void set_max_zoom(float p_maxZoom);

	float get_zoom_speed() const;
	void set_zoom_speed(float p_zoomSpeed);

	float get_zoom_level() const;
	void set_zoom_level(float p_zoomLevel);

protected:
	static void _bind_methods();

	void _notification(int p_what);

	void _ready();

	void _process(float delta);

private:
	float cameraSpeed;
	float cameraFastMultiplier;

	float minZoom;
	float maxZoom;
	float zoomSpeed;

	float zoomLevel;
	Camera2D *camera2D;

	void HandleMovement(float delta);
	void HandleZoom(float delta);
};
