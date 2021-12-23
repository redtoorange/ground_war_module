#include "BaseUnit.h"

#include "core/engine.h"
#include "scene/2d/area_2d.h"

BaseUnit::BaseUnit() {
	currentHoverState = UNHOVERED;
	currentSelectionState = UNSELECTED;

	set_process(true);
	set_process_unhandled_input(true);
}

void BaseUnit::_bind_methods() {
	// Expose these methods as callable for Signals
	ClassDB::bind_method(D_METHOD("OnMouseEntered"), &BaseUnit::OnMouseEntered);
	ClassDB::bind_method(D_METHOD("OnMouseExited"), &BaseUnit::OnMouseExited);

	// Engine Callbacks
	ClassDB::bind_method("_unhandled_input", &BaseUnit::_unhandled_input);
	ClassDB::bind_method("_process", &BaseUnit::_process);
}

void BaseUnit::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	}
}

void BaseUnit::_ready() {
	unitSprite = cast_to<Sprite>(get_node_or_null(NodePath("UnitSprite")));
	selectionSprite = cast_to<Sprite>(get_node_or_null(NodePath("SelectionSprite")));
	hoveredSprite = cast_to<Sprite>(get_node_or_null(NodePath("HoverSprite")));

	selectionSprite->set_visible(false);
	hoveredSprite->set_visible(false);

	Area2D *area = cast_to<Area2D>(get_node(NodePath("Area2D")));
	if (area) {
		area->connect("mouse_entered", this, "OnMouseEntered");
		area->connect("mouse_exited", this, "OnMouseExited");
	}
}

void BaseUnit::OnMouseEntered() {
	currentHoverState = HOVERED;
	UpdateOverlays();
}

void BaseUnit::OnMouseExited() {
	currentHoverState = UNHOVERED;
	UpdateOverlays();
}

void BaseUnit::UpdateOverlays() {
	if (currentSelectionState == UNSELECTED) {
		selectionSprite->set_visible(false);
		hoveredSprite->set_visible(currentHoverState == HOVERED);
	} else {
		hoveredSprite->set_visible(false);
		selectionSprite->set_visible(currentSelectionState == SELECTED);
	}
}

void BaseUnit::_unhandled_input(Ref<InputEvent> p_event) {
	if(currentHoverState == HOVERED || currentSelectionState == SELECTED) {
		Ref<InputEventMouseButton> mouseButtonEvent = p_event;
		if(mouseButtonEvent.is_valid()) {
			if(mouseButtonEvent->get_button_index() == BUTTON_LEFT) {
				if(currentHoverState == HOVERED && currentSelectionState == UNSELECTED) {
					currentSelectionState = SELECTED;
				}
			}
			if(mouseButtonEvent->get_button_index() == BUTTON_RIGHT) {
				if(currentSelectionState == SELECTED) {
					currentSelectionState = UNSELECTED;
				}
			}

			UpdateOverlays();
		}
	}
}

void BaseUnit::_process(float delta) {
}
