#pragma once

#include "Order.h"
#include "core/math/vector2.h"

class BaseUnit;

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
