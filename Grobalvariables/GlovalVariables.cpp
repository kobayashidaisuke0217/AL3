#include "GlovalVariables.h"
#include "ImGuiManager.h"
#include <fstream>
GlovalVariables* GlovalVariables::GetInstance() {
	static GlovalVariables instance;
	return &instance;
}

void GlovalVariables::CreateGroup(const std::string& groupName) { datas_[groupName]; }
void GlovalVariables::SetValue(
    const std::string& groupName, const std::string& key, int32_t value) {
	Group& group = datas_[groupName];
	Item newItems{};

	newItems.value = value;
	group.items[key] = newItems;
}

void GlovalVariables::SetValue(const std::string& groupName, const std::string& key, float value) {
	Group& group = datas_[groupName];
	Item newItems{};

	newItems.value = value;
	group.items[key] = newItems;
}

void GlovalVariables::SetValue(
    const std::string& groupName, const std::string& key, Vector3& value) {
	Group& group = datas_[groupName];
	Item newItems{};

	newItems.value = value;
	group.items[key] = newItems;
}

void GlovalVariables::Update() {
	if (!ImGui::Begin("Global Variables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		return;
	}

	if (!ImGui::BeginMenuBar())
		return;

	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end();
	     ++itGroup) {
		const std::string& groupName = itGroup->first;
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;

		for (std::map<std::string, Item>::iterator itItem = group.items.begin();
		     itItem != group.items.end(); ++itItem) {
			const std::string& itemName = itItem->first;
			Item& item = itItem->second;

			if (std::holds_alternative<int32_t>(item.value)) {
				int32_t* ptr = std::get_if<int32_t>(&item.value);
				ImGui::SliderInt(itemName.c_str(), ptr, 0, 100);
			} else if (std::holds_alternative<float>(item.value)) {
				float* ptr = std::get_if<float>(&item.value);
				ImGui::SliderFloat(itemName.c_str(), ptr, 0, 100);
			} else if (std::holds_alternative<Vector3>(item.value)) {
				Vector3* ptr = std::get_if<Vector3>(&item.value);
				ImGui::SliderFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);
			}
		}
		ImGui::Text("\n");

		if (ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = std::format("{}.json saved", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		}

		ImGui::EndMenu();
	}

	ImGui::EndMenuBar();
	ImGui::End();

}

void GlovalVariables::SaveFile(const std::string& groupName) {
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	assert(itGroup != datas_.end());

	json root;
	root = json::object();

	root[groupName] = json::object();

	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin();
	     itItem != itGroup->second.items.end(); ++itItem) {
		const std::string& itemName = itItem->first;
		Item& item = itItem->second;

		if (std::holds_alternative<int32_t>(item.value)) {
			root[groupName][itemName] = std::get<int32_t>(item.value);
		} else if (std::holds_alternative<float>(item.value)) {
			root[groupName][itemName] = std::get<float>(item.value);
		}

		if (std::holds_alternative<Vector3>(item.value)) {
			Vector3 value = std::get<Vector3>(item.value);
			root[groupName][itemName] = json::array({value.x, value.y, value.z});
		}
	}
	std::filesystem::path dir(kDirectoryPath);

	if (!std::filesystem::exists(kDirectoryPath)) {
		std::filesystem::create_directory(kDirectoryPath);
	}
	std::string filePath = kDirectoryPath + groupName + ".json";
	std::ofstream ofs{};
	ofs.open(filePath);

	if (ofs.fail()) {
		std::string message = "Failed Open Data File Fow Write";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(0);
		return;
	}

	ofs << std::setw(4) << root << std::endl;
	ofs.close();
}
