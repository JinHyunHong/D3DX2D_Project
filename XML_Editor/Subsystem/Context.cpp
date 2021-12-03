#include "stdafx.h"
#include "Context.h"

Context::Context(Tool* const tool) :
	ISubsystem(tool)
{
}

bool Context::Initialize()
{
	return true;
}

void Context::AddElement(const std::string& element_name, const std::string& base_element_name)
{
	if (base_element_name.empty())
	{
		Xml::XMLElement* element = doc.NewElement(element_name.c_str());
		doc.LinkEndChild(element);
		return;
	}

	Xml::XMLElement* element = GetElement(base_element_name);
	Xml::XMLElement* element_child = doc.NewElement(element_name.c_str());
	element->LinkEndChild(element_child);
}

auto Context::GetElement(const std::string& element_name) -> Xml::XMLElement*
{
	Xml::XMLElement* element = doc.FirstChildElement();
	
	for (; element; element = element->NextSiblingElement())
	{
		if (element->Name() == element_name)
		{
			return element;
		}

		for (Xml::XMLElement* chlild_element = element->FirstChildElement();
			chlild_element; chlild_element = chlild_element->NextSiblingElement())
		{
			if (chlild_element->Name() == element_name)
			{
				return element;
			}
		}

	}
	return nullptr;
}

bool Context::SaveToFile(const std::string& path)
{
	std::string file_path_name = path + file_name;
	return Xml::XMLError::XML_SUCCESS != doc.SaveFile(file_path_name.c_str());
}

bool Context::LoadFromFile(const std::string& path)
{
	std::string file_path_name = path + file_name;
	return Xml::XMLError::XML_SUCCESS != doc.LoadFile(file_path_name.c_str());
}
