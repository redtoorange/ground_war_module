#include "BaseUnit.h"

#include "scene/2d/sprite_2d.h"
#include "scene/2d/area_2d.h"

BaseUnit::BaseUnit() {
	currentHoverState = UNHOVERED;
	currentSelectionState = UNSELECTED;

	set_process(true);
}

void BaseUnit::_bind_methods() {
	ADD_GROUP("Paths", "path_");
	ClassDB::bind_method(D_METHOD("SetUnitSpritePath", "sprite_path"), &BaseUnit::SetUnitSpritePath);
	ClassDB::bind_method(D_METHOD("GetUnitSpritePath"), &BaseUnit::GetUnitSpritePath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_unit_sprite", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Sprite2D"), "SetUnitSpritePath", "GetUnitSpritePath");

	ClassDB::bind_method(D_METHOD("SetHoveredSpritePath", "sprite_path"), &BaseUnit::SetHoveredSpritePath);
	ClassDB::bind_method(D_METHOD("GetHoveredSpritePath"), &BaseUnit::GetHoveredSpritePath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_hovered_sprite", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Sprite2D"), "SetHoveredSpritePath", "GetHoveredSpritePath");

	ClassDB::bind_method(D_METHOD("SetSelectionSpritePath", "sprite_path"), &BaseUnit::SetSelectionSpritePath);
	ClassDB::bind_method(D_METHOD("GetSelectionSpritePath"), &BaseUnit::GetSelectionSpritePath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_selection_sprite", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Sprite2D"), "SetSelectionSpritePath", "GetSelectionSpritePath");

	ClassDB::bind_method(D_METHOD("SetAreaPath", "area_path"), &BaseUnit::SetAreaPath);
	ClassDB::bind_method(D_METHOD("GetAreaPath"), &BaseUnit::GetAreaPath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_area", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Area2D"), "SetAreaPath", "GetAreaPath");
}

void BaseUnit::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	}
}

void BaseUnit::_ready() {
	unitSprite = cast_to<Sprite2D>(get_node_or_null(unitSpritePath));
	selectionSprite = cast_to<Sprite2D>(get_node_or_null(selectionSpritePath));
	hoveredSprite = cast_to<Sprite2D>(get_node_or_null(hoveredSpritePath));

	selectionSprite->set_visible(false);
	hoveredSprite->set_visible(false);

	Area2D *area = cast_to<Area2D>(get_node(NodePath("Area2D")));
	if (area) {

		area->connect("mouse_entered", callable_mp(this, &BaseUnit::OnMouseEntered));
		area->connect("mouse_exited", callable_mp(this, &BaseUnit::OnMouseExited));
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

void BaseUnit::Select() {
	currentSelectionState = SELECTED;
	UpdateOverlays();
}

void BaseUnit::Deselect() {
	currentSelectionState = UNSELECTED;
	UpdateOverlays();
}

// --------------------------- Getters / Setters -------------------------------------------------

NodePath BaseUnit::GetUnitSpritePath() const {
	return unitSpritePath;
}

void BaseUnit::SetUnitSpritePath(const NodePath &p_unitSpritePath) {
	unitSpritePath = p_unitSpritePath;
}

NodePath BaseUnit::GetSelectionSpritePath() const {
	return selectionSpritePath;
}

void BaseUnit::SetSelectionSpritePath(const NodePath &p_selectionSpritePath) {
	selectionSpritePath = p_selectionSpritePath;
}

NodePath BaseUnit::GetHoveredSpritePath() const {
	return hoveredSpritePath;
}

void BaseUnit::SetHoveredSpritePath(const NodePath &p_hoveredSpritePath) {
	hoveredSpritePath = p_hoveredSpritePath;
}

NodePath BaseUnit::GetAreaPath() const {
	return areaPath;
}

void BaseUnit::SetAreaPath(const NodePath &p_areaPath) {
	areaPath = p_areaPath;
}
