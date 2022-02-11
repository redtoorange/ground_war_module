#pragma once

#include "scene/2d/node_2d.h"

class Sprite2D;
class BaseUnit : public Node2D {
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

	NodePath GetUnitSpritePath() const;
	void SetUnitSpritePath(const NodePath &p_unitSpritePath);

	NodePath GetSelectionSpritePath() const;
	void SetSelectionSpritePath(const NodePath &p_selectionSpritePath);

	NodePath GetHoveredSpritePath() const;
	void SetHoveredSpritePath(const NodePath &p_hoveredSpritePath);

	NodePath GetAreaPath() const;
	void SetAreaPath(const NodePath &p_areaPath);

	void Select();
	void Deselect();

protected:
	static void _bind_methods();
	void _notification(int p_what);
	void _ready();

private:
	void UpdateOverlays();

	void OnMouseEntered();
	void OnMouseExited();

	NodePath unitSpritePath;
	Sprite2D *unitSprite;

	NodePath selectionSpritePath;
	Sprite2D *selectionSprite;

	NodePath hoveredSpritePath;
	Sprite2D *hoveredSprite;

	NodePath areaPath;

	HoverState currentHoverState;
	SelectionState currentSelectionState;
};

