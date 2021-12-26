#include "stdafx.h"
#include "TextRendererComponent.h"

TextRendererComponent::TextRendererComponent(Tool* const tool, Actor* const actor,
	TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
}

bool TextRendererComponent::Initialize()
{
	return true;
}

void TextRendererComponent::Update()
{
}

void TextRendererComponent::Destroy()
{
}

void TextRendererComponent::AddText(const std::string& text, const D3DXCOLOR& color, const D3DXVECTOR2& offset)
{
	if (text.empty() || HasText(text))
	{
		assert(false);
		return;
	}

	texts.emplace_back(std::make_shared<TextRenderInfo>(text, color, offset));
}

bool TextRendererComponent::HasText(const std::string& text)
{
	for (auto iter = texts.begin(); iter != texts.end(); ++iter)
	{
		if ((*iter)->text == text)
			return true;
	}

	return false;
}
