#pragma once

void TYPE_vault(std::string command, 
	std::vector<std::string>* object_options,
	bool* vault_opened,
	unsigned short int* vault_attempts_left
	);

void TYPE_door_lock(std::string command,
	std::vector<std::string>* object_options,
	bool* door_lock_opened
);

void INSERTkey(std::vector<std::string>* object_options, 
	std::vector<std::string>* possession_options, 
	bool* box_opened );

void INSERTwoodenrod(std::vector<std::string>* object_options,
	std::vector<std::string>* possession_options,
	bool* wall_vault_opened);

void PICKUPkey(std::vector<std::string>* possession_options);

void PICKUPgun(std::vector<std::string>* possession_options);

void PICKUPredbook(std::vector<std::string>* possession_options);

void PICKUPblackbook(std::vector<std::string>* possession_options);

void PICKUPwoodenrod(std::vector<std::string>* possession_options);

void OPENwall_vault(std::vector<std::string>* object_options,
	std::vector<std::string>* possession_options,
	bool* wall_vault_opened);

void OPENbox(std::vector<std::string>* possession_options,
	std::vector<std::string>* object_options,
	bool* box_opened);

void KNOCK(int room);

void OPEN(std::vector<std::string>* object_options, 
	std::vector<std::string>* room_options, 
	std::vector<std::string>* possession_options,
	int* room);

void FIRE(std::vector<std::string>* object_options,
	std::vector<std::string> possession_options,
	std::vector<std::string>* room_options,
	bool* gun_shot,
	bool* man_is_dead,
	int room);

void MOVE(bool* bookshelf_moved);

void READ(std::string book_type,
	std::vector<std::string>* object_options,
	std::vector<std::string> possession_options);

void CLIMB(std::vector<std::string>* object_options);

void NEGOTIATE();