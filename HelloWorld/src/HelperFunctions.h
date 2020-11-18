#pragma once
bool IsIn(std::vector<std::string> optionsVect, std::string option);

void ReplaceOptions(std::vector<std::string>* options_vect, std::vector <std::string> new_options);

void AddOption(std::vector<std::string>* options_vect, std::string option);
void RemoveOption(std::vector<std::string>* options_vect, std::string option);

void PrintOptions(std::vector<std::string> object_options,
	std::vector<std::string> possession_options,
	std::vector<std::string> room_options, bool calledHelp);

void IntroText();

void EmptyOptions(std::vector<std::string>* options_vect);

bool CommandStartsWith(std::string command, std::string substring, int min_string_close_len);