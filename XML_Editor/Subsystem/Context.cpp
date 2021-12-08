#include "stdafx.h"
#include "Context.h"

Context::Context(Tool* const tool) :
	ISubsystem(tool)
{
}

bool Context::Initialize()
{
	dec = doc.NewDeclaration();
	doc.LinkEndChild(dec);

	return true;
}

void Context::Destroy()
{
	doc.Clear();
	dec = nullptr;
	file_name = "";
}

void Context::AddElement(const std::string& element_name, const std::string& base_element_name)
{
	if (element_name.empty())
		assert(false);

	if (base_element_name.empty())
	{
		Xml::XMLElement* element = doc.NewElement(element_name.c_str());
		doc.LinkEndChild(element);
		return;
	}

	Xml::XMLElement* element = GetElement(base_element_name);

	if (!element)
		assert(false);

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
				return chlild_element;
			}
		}

	}
	return nullptr;
}

bool Context::SaveToFile(const std::string& filepath_name)
{
	std::string cut_off = filepath_name.substr(filepath_name.find_last_of("\\/") + 1, filepath_name.length());
	file_name = cut_off.substr(0, cut_off.find_last_of("."));
	return Xml::XMLError::XML_SUCCESS == doc.SaveFile(filepath_name.c_str());
}

bool Context::LoadFromFile(const std::string& filepath_name)
{
	std::string cut_off = filepath_name.substr(filepath_name.find_last_of("\\/") + 1, filepath_name.length());
	file_name = cut_off.substr(0, cut_off.find_last_of("."));
	return Xml::XMLError::XML_SUCCESS == doc.LoadFile(filepath_name.c_str());
}

auto Context::ToString() -> const std::string
{
	Xml::XMLPrinter printer;
	doc.Print(&printer);

	return printer.CStr();
}

auto Context::DeduceTextType(const std::string& text) -> const std::string
{
	if (text.empty())
		return "";

	if (text.find_last_not_of("0123456789") == std::string::npos)
	{
		if (text.find_last_not_of(".") == std::string::npos)
			return std::string("float");
		else
			return std::string("int");
	}

	else
		return std::string("string");
}
