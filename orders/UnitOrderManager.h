#pragma once

#include "Order.h"
#include "scene/2d/node_2d.h"

#include <queue>

class UnitOrderManager : public Node2D {
	GDCLASS(UnitOrderManager, Node2D);

public:
	UnitOrderManager();

	void AddOrder(Ref<Order> order);

	void ProcessOrders();

	void ClearOrders();

	void CancelOrder();

protected:
	static void _bind_methods();

	void _notification(int p_what);

	void _process(float delta);

private:
	std::queue<Ref<Order>> orderQueue;
};

