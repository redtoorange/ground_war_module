#include "UnitOrderManager.h"

UnitOrderManager::UnitOrderManager() {
	set_process(true);
}

void UnitOrderManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("AddOrder", "order"), &UnitOrderManager::AddOrder);
	ClassDB::bind_method(D_METHOD("ClearOrders"), &UnitOrderManager::ClearOrders);
	ClassDB::bind_method(D_METHOD("CancelOrder"), &UnitOrderManager::CancelOrder);
}

void UnitOrderManager::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_PROCESS) {
		_process(get_process_delta_time());
	}
}

void UnitOrderManager::AddOrder(Ref<Order> order) {
	orderQueue.push(order);
}

void UnitOrderManager::_process(float delta) {
	ProcessOrders();
}

void UnitOrderManager::ProcessOrders() {
	if (!orderQueue.empty()) {
		Ref<Order> order = orderQueue.front();

		if (order.is_valid()) {
			order->Execute();
			if (order->IsComplete()) {
				orderQueue.pop();
			}
		}
	}
}

void UnitOrderManager::ClearOrders() {
	while (!orderQueue.empty()) {
		orderQueue.pop();
	}
}

void UnitOrderManager::CancelOrder() {
	orderQueue.pop();
}
