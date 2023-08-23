#pragma once
#include "math/MyMath.h"
#include<variant>
#include<string>
#include <map>
#include<json.hpp>
class GlovalVariables {
	using json=nlohmann::json;
public:
	static GlovalVariables* GetInstance();

	void CreateGroup(const std::string& groupName);
	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	void SetValue(const std::string& groupName, const std::string& key, float value);
	void SetValue(const std::string& groupName, const std::string& key, Vector3& value);
	void Update();
	void SaveFile(const std::string& groupName);

private:
	GlovalVariables() = default;
	~GlovalVariables() = default;
	GlovalVariables(const GlovalVariables& obj) = default;
	GlovalVariables& operator=(const GlovalVariables& obj) = default;
	struct Item {
		std::variant<int32_t, float, Vector3> value;
	};
	struct Group {
		std::map<std::string, Item> items;
	};
	std::map<std::string, Group> datas_;
	const std::string kDirectoryPath = "Resources/GlovalVariables/";
};
