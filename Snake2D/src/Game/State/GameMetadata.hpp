#pragma once
#include <string>
#include <map>
#include <any>

class GameMetadata 
{
public:
	template<typename T>
	void SetValue(const std::string& name, T&& value) 
	{
		m_Values[name] = std::move(value);
	}
	template<typename T>
	const T GetValue(const std::string& name) const { return std::any_cast<T>(m_Values.at(name)); }
private:
	std::map<std::string, std::any> m_Values;
};