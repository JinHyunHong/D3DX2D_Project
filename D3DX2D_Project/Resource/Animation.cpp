#include "stdafx.h"
#include "Animation.h"

Animation::Animation(Tool* const tool) :
	IResource(tool)
{
}

Animation::~Animation()
{
	CLEAR_VECTOR(keyframes);
}

bool Animation::SaveToFile(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);
	Xml::XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);
	root->SetAttribute("Name", resource_name.c_str());
	root->SetAttribute("Type", static_cast<uint>(repeat_type));
	root->SetAttribute("TexturePath", sprite_texture_path.c_str());	
	root->SetAttribute("TextureSizeX", sprite_texture_size.x);
	root->SetAttribute("TextureSizeY", sprite_texture_size.y);
	root->SetAttribute("ColorKeyR", color_key.r);
	root->SetAttribute("ColorKeyG", color_key.g);
	root->SetAttribute("ColorKeyB", color_key.b);
	root->SetAttribute("ColorKeyA", color_key.a);
	
	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* first_element = doc.NewElement("Keyframe");
		root->LinkEndChild(first_element);
		first_element->SetAttribute("OffsetX", keyframe.offset.x);
		first_element->SetAttribute("OffsetY", keyframe.offset.y);
		first_element->SetAttribute("SizeX", keyframe.size.x);
		first_element->SetAttribute("SizeY", keyframe.size.y);
		first_element->SetAttribute("Time", keyframe.time);
	}

	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(path.c_str());
}

bool Animation::LoadFromFile(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}	
	Xml::XMLElement* root = doc.FirstChildElement();
	resource_name = root->Attribute("Name");
	repeat_type = static_cast<RepeatType>(root->UnsignedAttribute("Type"));
	sprite_texture_path = root->Attribute("TexturePath");
	sprite_texture_size.x = root->FloatAttribute("TextureSizeX");
	sprite_texture_size.y = root->FloatAttribute("TextureSizeY");
	color_key.r = root->FloatAttribute("ColorKeyR");
	color_key.g = root->FloatAttribute("ColorKeyG");
	color_key.b = root->FloatAttribute("ColorKeyB");
	color_key.a = root->FloatAttribute("ColorKeyA");

	SetSpriteTexture(sprite_texture_path);

	Xml::XMLElement* first_element = root->FirstChildElement();

	for (; first_element; first_element = first_element->NextSiblingElement())
	{
		D3DXVECTOR2 offset;
		offset.x = first_element->FloatAttribute("OffsetX");
		offset.y = first_element->FloatAttribute("OffsetY");

		D3DXVECTOR2 size;
		size.x = first_element->FloatAttribute("SizeX");
		size.y = first_element->FloatAttribute("SizeY");

		float time;
		time = first_element->FloatAttribute("Time");

		AddKeyFrame(offset, size, time);
	}

	return true;
}

bool Animation::LoadFromFile_Continue(Xml::XMLElement* element)
{
	Xml::XMLElement* root = element;
	resource_name = root->Attribute("Name");
	repeat_type = static_cast<RepeatType>(root->UnsignedAttribute("Type"));
	sprite_texture_path = root->Attribute("TexturePath");
	sprite_texture_size.x = root->FloatAttribute("TextureSizeX");
	sprite_texture_size.y = root->FloatAttribute("TextureSizeY");
	color_key.r = root->FloatAttribute("ColorKeyR");
	color_key.g = root->FloatAttribute("ColorKeyG");
	color_key.b = root->FloatAttribute("ColorKeyB");
	color_key.a = root->FloatAttribute("ColorKeyA");

	SetSpriteTexture(sprite_texture_path);

	Xml::XMLElement* first_element = root->FirstChildElement();

	for (; first_element; first_element = first_element->NextSiblingElement())
	{
		D3DXVECTOR2 offset;
		offset.x = first_element->FloatAttribute("OffsetX");
		offset.y = first_element->FloatAttribute("OffsetY");

		D3DXVECTOR2 size;
		size.x = first_element->FloatAttribute("SizeX");
		size.y = first_element->FloatAttribute("SizeY");

		float time;
		time = first_element->FloatAttribute("Time");

		AddKeyFrame(offset, size, time);
	}

	return true;
}

void Animation::SaveToFile_Continue(Xml::XMLDocument& doc)
{
	Xml::XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);
	root->SetAttribute("Name", resource_name.c_str());
	root->SetAttribute("Type", static_cast<uint>(repeat_type));
	root->SetAttribute("TexturePath", sprite_texture_path.c_str());
	root->SetAttribute("TextureSizeX", sprite_texture_size.x);
	root->SetAttribute("TextureSizeY", sprite_texture_size.y);
	root->SetAttribute("ColorKeyR", color_key.r);
	root->SetAttribute("ColorKeyG", color_key.g);
	root->SetAttribute("ColorKeyB", color_key.b);
	root->SetAttribute("ColorKeyA", color_key.a);

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* first_element = doc.NewElement("Keyframe");
		root->LinkEndChild(first_element);
		first_element->SetAttribute("OffsetX", keyframe.offset.x);
		first_element->SetAttribute("OffsetY", keyframe.offset.y);
		first_element->SetAttribute("SizeX", keyframe.size.x);
		first_element->SetAttribute("SizeY", keyframe.size.y);
		first_element->SetAttribute("Time", keyframe.time);
	}

	return;
}

void Animation::SaveToFile_Continue(Xml::XMLDocument& doc, Xml::XMLElement* root_element)
{
	Xml::XMLElement* new_element = doc.NewElement("Animation");
	root_element->LinkEndChild(new_element);
	new_element->SetAttribute("Name", resource_name.c_str());
	new_element->SetAttribute("Type", static_cast<uint>(repeat_type));
	new_element->SetAttribute("TexturePath", sprite_texture_path.c_str());
	new_element->SetAttribute("TextureSizeX", sprite_texture_size.x);
	new_element->SetAttribute("TextureSizeY", sprite_texture_size.y);
	new_element->SetAttribute("ColorKeyR", color_key.r);
	new_element->SetAttribute("ColorKeyG", color_key.g);
	new_element->SetAttribute("ColorKeyB", color_key.b);
	new_element->SetAttribute("ColorKeyA", color_key.a);

	for (const auto& keyframe : keyframes)
	{
		Xml::XMLElement* first_element = doc.NewElement("Keyframe");
		new_element->LinkEndChild(first_element);
		first_element->SetAttribute("OffsetX", keyframe.offset.x);
		first_element->SetAttribute("OffsetY", keyframe.offset.y);
		first_element->SetAttribute("SizeX", keyframe.size.x);
		first_element->SetAttribute("SizeY", keyframe.size.y);
		first_element->SetAttribute("Time", keyframe.time);
	}

	return;
}

void Animation::SetSpriteTexture(const std::string& path)
{
	this->sprite_texture_path = path;

	sprite_texture = std::make_shared<D3D11_Texture>(tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>());
	sprite_texture->Create(path);
}

auto Animation::GetKeyFrameFromIndex(const uint& index) -> const Keyframe* const
{
	assert(index < keyframes.size());
	return &keyframes[index];
}

void Animation::AddKeyFrame(const Keyframe& keyframe)
{
	keyframes.emplace_back(keyframe);
}

void Animation::AddKeyFrame(const D3DXVECTOR2& offset, const D3DXVECTOR2& size, const double& time)
{
	keyframes.emplace_back(offset, size, time);
}
