#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "scene/2d/node_2d.h"

class Camera2D;

class RtsCameraController : public Node2D {
	GDCLASS(RtsCameraController, Node2D);

public:
	RtsCameraController();

	float GetCameraSpeed() const {
		return cameraSpeed;
	}

	void SetCameraSpeed(float p_cameraSpeed) {
		cameraSpeed = p_cameraSpeed;
	}

	float GetCameraFastMultiplier() const {
		return cameraFastMultiplier;
	}

	void SetCameraFastMultiplier(float p_cameraFastMultiplier) {
		cameraFastMultiplier = p_cameraFastMultiplier;
	}

	float GetMinZoom() const {
		return minZoom;
	}

	void SetMinZoom(float p_minZoom) {
		minZoom = p_minZoom;
	}

	float GetMaxZoom() const {
		return maxZoom;
	}

	void SetMaxZoom(float p_maxZoom) {
		maxZoom = p_maxZoom;
	}

	float GetZoomSpeed() const {
		return zoomSpeed;
	}

	void SetZoomSpeed(float p_zoomSpeed) {
		zoomSpeed = p_zoomSpeed;
	}

	float GetZoomLevel() const {
		return zoomLevel;
	}

	void SetZoomLevel(float p_zoomLevel) {
		zoomLevel = p_zoomLevel;
	}

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

#endif
