#pragma once
#include "Scene.h"

enum class Edit_Mode : uint
{
	NoMove,
	Move
};

class MapEditorScene final :
	public Scene
{
public:
	MapEditorScene(class Tool* const tool);
	~MapEditorScene();

	void Initialize() override;
	void Input() override;
	void Update() override;
	void Destroy() override;

private:
	Edit_Mode edit_mode = Edit_Mode::NoMove;
};