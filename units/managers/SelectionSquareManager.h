#ifndef SELECTION_CONTROLLER_H
#define SELECTION_CONTROLLER_H

#include "scene/2d/node_2d.h"
#include "scene/gui/nine_patch_rect.h"

class SelectionSquareManager : public Node2D {
	GDCLASS(SelectionSquareManager, Node2D);

public:
	SelectionSquareManager();

	NodePath GetSelectionSquarePath() const;

	void SetSelectionSquarePath(const NodePath &p_selectionSquarePath);

protected:
	static void _bind_methods();
	void _notification(int p_what);
	void _ready();
	void _process(float delta);
	void input(const Ref<InputEvent> &inputEvent) override;

private:
	NodePath selectionSquarePath;
	NinePatchRect *selectionSquare;


	// selection properties
	bool selecting;
	Vector2	startMousePosition;
	Vector2 currentMousePosition;
	Vector2 rect_position;
	Vector2 rect_size;

	void HandleLeftMouseEvent(const Ref<InputEventMouseButton> &eventMouseButton);
	void HandleRightMouseEvent(const Ref<InputEventMouseButton> &eventMouseButton);
	void UpdateRectExtents();
};

#endif
