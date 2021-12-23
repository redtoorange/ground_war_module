#ifndef BASEUNIT_H
#define BASEUNIT_H
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"

class BaseUnit : public Node2D  {
	GDCLASS(BaseUnit, Node2D);
public:
	enum SelectionState {
		UNSELECTED,
		SELECTED
	};

	enum HoverState {
		UNHOVERED,
		HOVERED
	};

	BaseUnit();


protected:
	static void _bind_methods();
	void _notification(int p_what);
	void _ready();

	void _process(float delta);
	void _unhandled_input(Ref<InputEvent> p_event);

private:
	void UpdateOverlays();

	void OnMouseEntered();
	void OnMouseExited();

	Sprite* unitSprite;
	Sprite* selectionSprite;
	Sprite* hoveredSprite;

	HoverState currentHoverState;
	SelectionState currentSelectionState;
};

#endif

