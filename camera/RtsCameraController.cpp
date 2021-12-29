#include "RtsCameraController.h"

#include "scene/2d/camera_2d.h"

RtsCameraController::RtsCameraController() {
	cameraSpeed = 5.0f;
	cameraFastMultiplier = 2.0f;
	minZoom = 0.5f;
	maxZoom = 10.0f;
	zoomSpeed = 5.0f;

	set_process(true);
}

void RtsCameraController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetCameraSpeed", "camera_speed"), &RtsCameraController::SetCameraSpeed);
	ClassDB::bind_method(D_METHOD("GetCameraSpeed"), &RtsCameraController::GetCameraSpeed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_speed"), "SetCameraSpeed", "GetCameraSpeed");

	ClassDB::bind_method(D_METHOD("SetCameraFastMultiplier", "camera_fast_multiplier"), &RtsCameraController::SetCameraFastMultiplier);
	ClassDB::bind_method(D_METHOD("GetCameraFastMultiplier"), &RtsCameraController::GetCameraFastMultiplier);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_fast_multiplier"), "SetCameraFastMultiplier", "GetCameraFastMultiplier");


	ClassDB::bind_method(D_METHOD("SetMinZoom", "camera_min_zoom"), &RtsCameraController::SetMinZoom);
	ClassDB::bind_method(D_METHOD("GetMinZoom"), &RtsCameraController::GetMinZoom);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_min_zoom"), "SetMinZoom", "GetMinZoom");

	ClassDB::bind_method(D_METHOD("SetMaxZoom", "camera_max_zoom"), &RtsCameraController::SetMaxZoom);
	ClassDB::bind_method(D_METHOD("GetMaxZoom"), &RtsCameraController::GetMaxZoom);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "camera_max_zoom"), "SetMaxZoom", "GetMaxZoom");
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
	print_line("Prepping RtsCameraController");
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
