#pragma once

struct RoomObject {
	int id; std::string description; std::vector<std::string> obj_options;
	RoomObject(int Id, std::string Description, std::vector<std::string> Obj_options);
	void describe();
	std::vector<std::string> get_obj_options();
};
