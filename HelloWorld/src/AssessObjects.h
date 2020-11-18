#pragma once

void bookshelf_called(RoomObject bookshelf, 
	std::vector<std::string>* objects_options, 
	std::vector<std::string> possessions_options, 
	bool box_opened, bool wall_vault_opened);

void door_1_called(RoomObject room_1_door,
	std::vector<std::string>* object_options,
	bool door_lock_opened);

void door_2_called(RoomObject room_2_door, 
	std::vector<std::string>* object_options);

void door_3_called(RoomObject room_3_door,
	std::vector<std::string>* object_options);

void red_book_called(std::vector<std::string>* objects_options, 
	std::vector<std::string> possessions_options);

void black_book_called(
	std::vector<std::string>* object_options,
	std::vector<std::string> possession_options
);

void key_called(std::vector<std::string>* object_options,
	std::vector<std::string> possession_options);

void vault_called(
	RoomObject vault,
	std::vector<std::string>* object_options,
	std::vector<std::string> possession_options,
	bool vault_opened,
	unsigned short int vault_attempts_left
);

void box_called(
	std::vector<std::string>* object_options,
	std::vector<std::string> possession_options,
	bool box_open,
	bool wall_vault_opened
);

void wall_vault_called(RoomObject wall_vault, 
	std::vector<std::string>* object_options, 
	std::vector<std::string> possession_options, 
	bool wall_vault_opened);

void door_lock_called(
	RoomObject door_lock,
	std::vector<std::string>* object_options,
	std::vector<std::string> possession_options,
	bool door_lock_opened
);
