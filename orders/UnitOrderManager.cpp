#include "UnitOrderManager.h"

UnitOrderManager::UnitOrderManager() {
	set_process(true);
}

void UnitOrderManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetUnitSelectionManagerPath", "unit_selection_manager_path"), &UnitOrderManager::SetUnitSelectionManagerPath);
	ClassDB::bind_method(D_METHOD("GetUnitSelectionManagerPath"), &UnitOrderManager::GetUnitSelectionManagerPath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "Unit Selection Manager", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "UnitSelectionManager"), "SetUnitSelectionManagerPath", "GetUnitSelectionManagerPath");
}

void UnitOrderManager::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	} else if (p_what == NOTIFICATION_PROCESS) {
		_process(get_process_delta_time());
	}
}

void UnitOrderManager::CommitOrder(Order *order) {
	orderQueue.push(order);
}

void UnitOrderManager::_ready() {
	unitSelectionManager = cast_to<UnitSelectionManager>(get_node(unitSelectionManagerPath));
}

void UnitOrderManager::_process(float delta) {
}

// --------------------------- Getters / Setters -------------------------------------------------

NodePath UnitOrderManager::GetUnitSelectionManagerPath() const {
	return unitSelectionManagerPath;
}

void UnitOrderManager::SetUnitSelectionManagerPath(const NodePath &p_unitSelectionManagerPath) {
	unitSelectionManagerPath = p_unitSelectionManagerPath;
}
