#ifndef MOVE_ORDER_H
#define MOVE_ORDER_H

#include "Order.h"
#include "core/math/vector2.h"
#include "modules/ground_war/units/BaseUnit.h"


class MoveOrder : public Order {
	GDCLASS(MoveOrder, Order);
public:
	MoveOrder() :
		Order(),
		targetUnit(nullptr),
		origin({ 0.0f, 0.0f }),
		destination({ 0.0f, 0.0f }) {
	}

	void Execute() override;

	bool IsComplete() override;

protected:
	static void _bind_methods();

	void _notification(int p_what);

private:
	BaseUnit *targetUnit;
	Vector2 origin;
	Vector2 destination;
};

#endif
