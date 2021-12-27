#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "Order.h"
#include "modules/ground_war/units/UnitSelectionManager.h"
#include "scene/2d/node_2d.h"

#include <queue>

class UnitOrderManager : public Node2D  {
	GDCLASS(UnitOrderManager, Node2D);

public:
	UnitOrderManager();

	void CommitOrder(Order* order);

	NodePath GetUnitSelectionManagerPath() const;
	void SetUnitSelectionManagerPath(const NodePath &p_unitSelectionManagerPath);
protected:
	static void _bind_methods();
	void _notification(int p_what);

	void _ready();
	void _process(float delta);

private:
	NodePath unitSelectionManagerPath;
	UnitSelectionManager* unitSelectionManager;


	std::queue<Order*> orderQueue;
};

#endif

