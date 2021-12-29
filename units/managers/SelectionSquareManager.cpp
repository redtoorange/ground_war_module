#include "SelectionSquareManager.h"

SelectionSquareManager::SelectionSquareManager() {
	set_process(true);
	set_process_input(true);
}

void SelectionSquareManager::_ready() {
	selectionSquare = cast_to<NinePatchRect>(get_node(selectionSquarePath));
	selectionSquare->set_visible(false);
}

void SelectionSquareManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetSelectionSquarePath", "selection_square_path"), &SelectionSquareManager::SetSelectionSquarePath);
	ClassDB::bind_method(D_METHOD("GetSelectionSquarePath"), &SelectionSquareManager::GetSelectionSquarePath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "selection_square_path", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "NinePatchRect"), "SetSelectionSquarePath", "GetSelectionSquarePath");

	ADD_SIGNAL(MethodInfo("selection_completed", PropertyInfo(Variant::RECT2, "selection_area")));
}

void SelectionSquareManager::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	} else if (p_what == NOTIFICATION_PROCESS) {
		_process(get_process_delta_time());
	}
}


void SelectionSquareManager::_process(float delta) {
	if (selecting) {
		currentMousePosition = get_global_mouse_position();
		UpdateRectExtents();
	}
}

void SelectionSquareManager::input(const Ref<InputEvent> &inputEvent) {
	Node2D::input(inputEvent);

	// Is the event a mouse button event?
	Ref<InputEventMouseButton> eventMouseButton = inputEvent;
	if (eventMouseButton.is_valid()) {
		// check if it's left or right
		if (eventMouseButton->get_button_index() == MouseButton::LEFT) {
			HandleLeftMouseEvent(inputEvent);
		} else if (eventMouseButton->get_button_index() == MouseButton::RIGHT) {
			HandleRightMouseEvent(inputEvent);
		}
	}
}

void SelectionSquareManager::HandleLeftMouseEvent(const Ref<InputEventMouseButton> &eventMouseButton) {
	if (eventMouseButton->is_pressed()) {
		startMousePosition = get_global_mouse_position();
		currentMousePosition = startMousePosition;
		UpdateRectExtents();
		selecting = true;
		selectionSquare->set_visible(true);
	} else {
		selectionSquare->set_visible(false);
		selecting = false;
		emit_signal("selection_completed", Rect2(rect_position, rect_size));
	}
}

void SelectionSquareManager::HandleRightMouseEvent(const Ref<InputEventMouseButton> &eventMouseButton) {
}

void SelectionSquareManager::UpdateRectExtents() {
	// Handle X
	if (currentMousePosition.x > startMousePosition.x) {
		rect_position.x = startMousePosition.x;
		rect_size.x = currentMousePosition.x - startMousePosition.x;
	} else {
		rect_position.x = currentMousePosition.x;
		rect_size.x = startMousePosition.x - currentMousePosition.x;
	}

	// Handle Y
	if (currentMousePosition.y > startMousePosition.y) {
		rect_position.y = startMousePosition.y;
		rect_size.y = currentMousePosition.y - startMousePosition.y;
	} else {
		rect_position.y = currentMousePosition.y;
		rect_size.y = startMousePosition.y - currentMousePosition.y;
	}

	selectionSquare->set_position(rect_position);
	selectionSquare->set_size(rect_size);
}

// --------------------------- Getters / Setters -------------------------------------------------

NodePath SelectionSquareManager::GetSelectionSquarePath() const {
	return selectionSquarePath;
}

void SelectionSquareManager::SetSelectionSquarePath(const NodePath &p_selectionSquarePath) {
	selectionSquarePath = p_selectionSquarePath;
}
