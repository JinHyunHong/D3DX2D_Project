#pragma once

class Renderer final :
	public ISubsystem
{
public:
	Renderer(class Tool* const tool);
	~Renderer() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

private:
	class Tool* tool = nullptr;

};