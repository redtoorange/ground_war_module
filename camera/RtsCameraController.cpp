#include "RtsCameraController.h"

#include "scene/2d/camera_2d.h"

RtsCameraController::RtsCameraController() {
	cameraSpeed = 100.0f;
	cameraFastMultiplier = 2.0f;
	minZoom = 0.5f;
	maxZoom = 10.0f;
	zoomSpeed = 5.0f;

	set_process(true);
}

void RtsCameraController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_camera_speed", "camera_speed"), &RtsCameraController::set_camera_speed);
	ClassDB::bind_method(D_METHOD("get_camera_speed"), &RtsCameraController::get_camera_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_speed"), "set_camera_speed", "get_camera_speed");

	ClassDB::bind_method(D_METHOD("set_camera_fast_multiplier", "camera_fast_multiplier"), &RtsCameraController::set_camera_fast_multiplier);
	ClassDB::bind_method(D_METHOD("get_camera_fast_multiplier"), &RtsCameraController::get_camera_fast_multiplier);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_fast_multiplier"), "set_camera_fast_multiplier", "get_camera_fast_multiplier");

	ClassDB::bind_method(D_METHOD("set_min_zoom", "camera_min_zoom"), &RtsCameraController::set_min_zoom);
	ClassDB::bind_method(D_METHOD("get_min_zoom"), &RtsCameraController::get_min_zoom);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_min_zoom"), "set_min_zoom", "get_min_zoom");

	ClassDB::bind_method(D_METHOD("set_max_zoom", "camera_max_zoom"), &RtsCameraController::set_max_zoom);
	ClassDB::bind_method(D_METHOD("get_max_zoom"), &RtsCameraController::get_max_zoom);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_max_zoom"), "set_max_zoom", "get_max_zoom");
}

void RtsCameraController::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_READY) {
			_ready();
		} else if (p_what == NOTIFICATION_PROCESS) {
			_process(get_process_delta_time());
		}
	}
}

void RtsCameraController::_ready() {
	camera2D = cast_to<Camera2D>(get_node(NodePath("Camera2D")));
	zoomLevel = camera2D->get_zoom().x;
}

void RtsCameraController::_process(float delta) {
	HandleMovement(delta);
	HandleZoom(delta);
}

void RtsCameraController::HandleMovement(float delta) {
	Vector2 deltaInput = Vector2(0, 0);
	Input *input = Input::get_singleton();

	if (input->is_action_pressed("camera_up")) {
		deltaInput.y -= 1;
	}
	if (input->is_action_pressed("camera_down")) {
		deltaInput.y += 1;
	}
	if (input->is_action_pressed("camera_left")) {
		deltaInput.x -= 1;
	}
	if (input->is_action_pressed("camera_right")) {
		deltaInput.x += 1;
	}

	if (deltaInput.length_squared() > 0) {
		float speed = cameraSpeed;
		if (input->is_action_pressed("camera_fast")) {
			speed *= cameraFastMultiplier;
		}

		Vector2 pos = get_position();
		pos += deltaInput.normalized() * delta * speed;
		set_position(pos);
	}
}

void RtsCameraController::HandleZoom(float delta) {
	float deltaZoom = 0;
	Input *input = Input::get_singleton();

	if (input->is_action_just_released("camera_zoom_in")) {
		deltaZoom -= 1;
	}
	if (input->is_action_just_released("camera_zoom_out")) {
		deltaZoom += 1;
	}

	if (deltaZoom != 0) {
		deltaZoom *= zoomSpeed * delta;

		const Vector2 targetZoom = camera2D->get_zoom();
		// zoomLevel = embree::clamp(targetZoom.x + deltaZoom, minZoom, maxZoom);
		zoomLevel = targetZoom.x + deltaZoom;

		camera2D->set_zoom(Vector2(zoomLevel, zoomLevel));
	}
}


float RtsCameraController::get_camera_speed() const {
	return cameraSpeed;
}

void RtsCameraController::set_camera_speed(float p_cameraSpeed) {
	cameraSpeed = p_cameraSpeed;
}

float RtsCameraController::get_camera_fast_multiplier() const {
	return cameraFastMultiplier;
}

void RtsCameraController::set_camera_fast_multiplier(float p_cameraFastMultiplier) {
	cameraFastMultiplier = p_cameraFastMultiplier;
}

float RtsCameraController::get_min_zoom() const {
	return minZoom;
}

void RtsCameraController::set_min_zoom(float p_minZoom) {
	minZoom = p_minZoom;
}

float RtsCameraController::get_max_zoom() const {
	return maxZoom;
}

void RtsCameraController::set_max_zoom(float p_maxZoom) {
	maxZoom = p_maxZoom;
}

float RtsCameraController::get_zoom_speed() const {
	return zoomSpeed;
}

void RtsCameraController::set_zoom_speed(float p_zoomSpeed) {
	zoomSpeed = p_zoomSpeed;
}

float RtsCameraController::get_zoom_level() const {
	return zoomLevel;
}

void RtsCameraController::set_zoom_level(float p_zoomLevel) {
	zoomLevel = p_zoomLevel;
}
