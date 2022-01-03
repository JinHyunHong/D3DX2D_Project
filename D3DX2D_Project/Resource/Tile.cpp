#include "stdafx.h"
#include "Tile.h"

Tile::Tile(class Tool* const tool, const ResourceType type) :
	IResource(tool, type)
{
}

Tile::~Tile()
{
}

bool Tile::SaveToFile(const std::string& path)
{
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);
	Xml::XMLElement* root = doc.NewElement("Tile");
	doc.LinkEndChild(root);
	root->SetAttribute("Name", name.c_str());
	root->SetAttribute("Is_Move", is_move);
	root->SetAttribute("Potal_Tile_Name", potal_tile_name.c_str());

	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(path.c_str());
}

bool Tile::LoadFromFile(const std::string& path)
{
	if (path.empty())
		return false;

	Xml::XMLDocument doc;
	Xml::XMLError error = doc.LoadFile(path.c_str());
	if (error != Xml::XMLError::XML_SUCCESS)
	{
		assert(false);
		return false;
	}
	Xml::XMLElement* root = doc.FirstChildElement();
	
	name = root->Attribute("Name");
	is_move = root->BoolAttribute("Is_Move");
	potal_tile_name = root->Attribute("Potal_Tile_Name");

	return true;
}

void Tile::SaveToFile_Continue(Xml::XMLDocument& doc)
{
	Xml::XMLElement* root = doc.NewElement("Tile");
	doc.LinkEndChild(root);
	root->SetAttribute("Name", name.c_str());
	root->SetAttribute("Is_Move", is_move);
	root->SetAttribute("Potal_Tile_Name", potal_tile_name.c_str());
	return;
}

void Tile::SaveToFile_Continue(Xml::XMLDocument& doc, Xml::XMLElement* root_element)
{
	Xml::XMLElement* new_element = doc.NewElement("Tile");
	root_element->LinkEndChild(new_element);
	new_element->SetAttribute("Name", name.c_str());
	new_element->SetAttribute("Is_Move", is_move);
	new_element->SetAttribute("Potal_Tile_Name", potal_tile_name.c_str());
	return;
}

bool Tile::LoadFromFile_Continue(Xml::XMLElement* element)
{
	name = element->Attribute("Name");
	is_move = element->BoolAttribute("Is_Move");
	potal_tile_name = element->Attribute("Potal_Tile_Name");

	return true;
}

void Tile::SetPotal(const std::string& potal_tile_name)
{
	this->potal_tile_name = potal_tile_name;
}
