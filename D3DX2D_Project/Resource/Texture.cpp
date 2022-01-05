#include "stdafx.h"
#include "Texture.h"

Texture::Texture(Tool* const tool) :
    IResource(tool)
{
}

Texture::~Texture()
{
}

bool Texture::SaveToFile(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);
	Xml::XMLElement* root = doc.NewElement("Texture");
	doc.LinkEndChild(root);
	root->SetAttribute("Name", resource_name.c_str());
	root->SetAttribute("TexturePath", sprite_texture_path.c_str());
	root->SetAttribute("TextureSizeX", sprite_texture_size.x);
	root->SetAttribute("TextureSizeY", sprite_texture_size.y);
	root->SetAttribute("ColorKeyR", color_key.r);
	root->SetAttribute("ColorKeyG", color_key.g);
	root->SetAttribute("ColorKeyB", color_key.b);
	root->SetAttribute("ColorKeyA", color_key.a);

	root->SetAttribute("OffsetX", offset.x);
	root->SetAttribute("OffsetY", offset.y);
	root->SetAttribute("SizeX", size.x);
	root->SetAttribute("SizeY", size.y);
	

	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(path.c_str());
}

bool Texture::LoadFromFile(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}

	Xml::XMLElement* root = doc.FirstChildElement();
	Xml::XMLElement* first_element = root->FirstChildElement();

	resource_name = first_element->Attribute("Name");
	sprite_texture_path = first_element->Attribute("TexturePath");
	sprite_texture_size.x = first_element->FloatAttribute("TextureSizeX");
	sprite_texture_size.y = first_element->FloatAttribute("TextureSizeY");
	color_key.r = first_element->FloatAttribute("ColorKeyR");
	color_key.g = first_element->FloatAttribute("ColorKeyG");
	color_key.b = first_element->FloatAttribute("ColorKeyB");
	color_key.a = first_element->FloatAttribute("ColorKeyA");

	SetSpriteTexture(sprite_texture_path);

	offset.x = first_element->FloatAttribute("OffsetX");
	offset.y = first_element->FloatAttribute("OffsetY");

	size.x = first_element->FloatAttribute("SizeX");
	size.y = first_element->FloatAttribute("SizeY");

    return true;
}

void Texture::SaveToFile_Continue(Xml::XMLDocument& doc)
{
	Xml::XMLElement* root = doc.NewElement("Texture");
	doc.LinkEndChild(root);
	root->SetAttribute("Name", resource_name.c_str());
	root->SetAttribute("TexturePath", sprite_texture_path.c_str());
	root->SetAttribute("TextureSizeX", sprite_texture_size.x);
	root->SetAttribute("TextureSizeY", sprite_texture_size.y);
	root->SetAttribute("ColorKeyR", color_key.r);
	root->SetAttribute("ColorKeyG", color_key.g);
	root->SetAttribute("ColorKeyB", color_key.b);
	root->SetAttribute("ColorKeyA", color_key.a);

	root->SetAttribute("OffsetX", offset.x);
	root->SetAttribute("OffsetY", offset.y);
	root->SetAttribute("SizeX", size.x);
	root->SetAttribute("SizeY", size.y);

	return;
}

void Texture::SaveToFile_Continue(Xml::XMLDocument& doc, Xml::XMLElement* root_element)
{
	Xml::XMLElement* new_element = doc.NewElement("Texture");
	root_element->LinkEndChild(new_element);
	new_element->SetAttribute("Name", resource_name.c_str());
	new_element->SetAttribute("TexturePath", sprite_texture_path.c_str());
	new_element->SetAttribute("TextureSizeX", sprite_texture_size.x);
	new_element->SetAttribute("TextureSizeY", sprite_texture_size.y);
	new_element->SetAttribute("ColorKeyR", color_key.r);
	new_element->SetAttribute("ColorKeyG", color_key.g);
	new_element->SetAttribute("ColorKeyB", color_key.b);
	new_element->SetAttribute("ColorKeyA", color_key.a);

	new_element->SetAttribute("OffsetX", offset.x);
	new_element->SetAttribute("OffsetY", offset.y);
	new_element->SetAttribute("SizeX", size.x);
	new_element->SetAttribute("SizeY", size.y);

	return;
}

bool Texture::LoadFromFile_Continue(Xml::XMLElement* sib_element)
{
	Xml::XMLElement* element = sib_element;
	resource_name = element->Attribute("Name");
	sprite_texture_path = element->Attribute("TexturePath");
	sprite_texture_size.x = element->FloatAttribute("TextureSizeX");
	sprite_texture_size.y = element->FloatAttribute("TextureSizeY");
	color_key.r = element->FloatAttribute("ColorKeyR");
	color_key.g = element->FloatAttribute("ColorKeyG");
	color_key.b = element->FloatAttribute("ColorKeyB");
	color_key.a = element->FloatAttribute("ColorKeyA");

	SetSpriteTexture(sprite_texture_path);

	offset.x = element->FloatAttribute("OffsetX");
	offset.y = element->FloatAttribute("OffsetY");
	
	size.x = element->FloatAttribute("SizeX");
	size.y = element->FloatAttribute("SizeY");

    return true;
}

void Texture::SetSpriteTexture(const std::string& path)
{
    this->sprite_texture_path = path;

    sprite_texture = std::make_shared<D3D11_Texture>(tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>());
    sprite_texture->Create(path);
}
