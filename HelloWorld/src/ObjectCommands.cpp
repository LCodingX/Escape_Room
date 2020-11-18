#include <iostream>
#include <string>
#include <vector>
#include "RoomObject.h"
#include "HelperFunctions.h"
using namespace std;

//GROUP - Bookshelf and doors
void MOVE(bool* bookshelf_moved) {
	// you shouldn't have any object options after moving the bookshelf.
	bool actual_bool = *bookshelf_moved;
	if (!actual_bool) {

		*bookshelf_moved = true;
		cout << "You move the bookshelf. Behind it is a wall vault.\n" <<
			"The wall vault has a rectangular opening on it, to open it.\n";
	}
	else if (bookshelf_moved) {
		cout << "You move the bookshelf again. This time, just a wall.\n";
	}
}

void OPEN(vector<string>* object_options, 
	vector<string>* room_options, 
	vector<string>* possession_options,
	int* room) {
	(*room)++;
	if ((*room) == 2) {
		cout << "You open the door and enter the next room.\nYou see a stairway leading up to a door.\n";
		ReplaceOptions(object_options, vector<string> {"CLIMB stairway"});
	}
	else if ((*room) == 3) {
		cout << "You open the door and enter a dimly lit laboratory.\n" <<
			"A short, bald, creepy-looking man starts walking towards you with a knife\n";
		ReplaceOptions(room_options, vector<string> {"NEGOTIATE"});
		EmptyOptions(object_options);
		bool has_gun = IsIn(*possession_options, "FIRE");
		EmptyOptions(possession_options);
		if (has_gun) {
			AddOption(possession_options, "FIRE");
		}
		EmptyOptions(object_options);
	}
	else if ((*room) == 4) {
		cout << "You have never appreciated the sky like this in your life.\n" <<
			"There is a river in front of you. You are in a city. This dark laboratory was hiding in plain sight.\n" <<
			"You will never be able to explain why that man locked all of those people up, but you will always remember it.\n" <<
			"You rush to the authorities.\n";
	}
}

void NEGOTIATE() {
	cout << "You try to talk to the bald man who is running at you.\nHe walks up to you and stabs you in the chest with a knife.\nGAME OVER\n";
}

void KNOCK(int room) {
	if (room == 2) {
		cout << "You knock on the door three times. You hear faint laughter, but no one opens the door for you.\n";
	}
	else if (room == 1) {
		cout << "You knock on the door three times. There is no response.\n";
	}
	else if (room == 3) {
		cout << "You knock on the door three times.\nYou hear the sound of running water and see sunlight creeping in from under the door.";
	}
}

void CLIMB(vector<string>* object_options) {
	ReplaceOptions(object_options, vector<string> {"OPEN door", "KNOCK"});
}

//GROUP - opening things (keys, typing, insert)
void TYPE_vault(string command,
	vector<string>* object_options,
	bool* vault_opened,
	unsigned short int* vault_attempts_left
) {
	EmptyOptions(object_options);
	if (*vault_opened) {
		cout << "The vault is currently opened.\n";
		return;
	}
	if (*vault_attempts_left == 0) {
		cout << "You are out of attempts. You might want to quit the game.\n";
		return;
	}
	//TYPE vault 90 is correct. Already knows that it starts with TYPE vault .
	//0123456789023
	if (isdigit(command[11])) {
		string guess = command.substr(11, 2);
		if (guess == "41") {
			cout << "That is correct!\n" <<
				"In the vault you see a gun and a key.\n";
			*vault_opened = true;
			ReplaceOptions(object_options, vector<string> {"PICKUP gun", "PICKUP key"});
			return;
		}
		else {
			AddOption(object_options, "TYPE vault [code]");
			cout << "That is incorrect. Please try again.\n";
		}
	}
	else {
		AddOption(object_options, "TYPE vault [code]");
		cout << "You need to type a number. You have the digits 0-9.\n";
	}

	//subtract an attempt even if they don't type a number.
	(*vault_attempts_left)--;
	cout << "You have " << *vault_attempts_left << " attempts left.\n";
}

void TYPE_door_lock(string command, 
	vector<string>* object_options, 
	bool* door_lock_opened
) {
	//TYPE door lock 03 is correct.
	//01234567890123456
	EmptyOptions(object_options);
	if (isdigit(command[15])) {
		string guess = command.substr(15, 2);
		if (guess == "03") {
			cout << "That is correct!\n";
			*door_lock_opened = true;
			ReplaceOptions(object_options, vector<string> {"OPEN door"});
		}
		else {
			AddOption(object_options, "TYPE door lock [code]");
			cout << "That is incorrect. Please try again.\n";
		}
	}
	else {
		AddOption(object_options, "TYPE door lock [code]");
		cout << "That is not a valid entry.\n";
	}
}

void INSERTkey(vector<string>* object_options, 
	vector<string>* possession_options, 
	bool* box_opened) {
	if ( IsIn(*object_options, "OPEN box") ) {
		*box_opened = true;
		RemoveOption(possession_options, "INSERT key");
		cout << "You insert the key and open the box.\n" <<
			"In the box, you find a wooden rod.\n";
		AddOption(object_options, "PICKUP wooden rod");
	}
	else {
		cout << "You insert the key into ... nothing.\n";
		EmptyOptions(object_options);
	}
}

void INSERTwoodenrod(vector<string>* object_options, 
	vector<string>* possession_options, 
	bool* wall_vault_opened) {
	if (IsIn(*object_options, "OPEN wall vault")) {
		*wall_vault_opened = true;
		RemoveOption(possession_options, "INSERT wooden rod");
		cout << "In the wall vault you find a black book.\n";
		ReplaceOptions(object_options, vector<string> {"READ black book", "PICKUP black book"});
	}
	else {
		cout << "You wave around the wooden rod in the air.\n";
	}
}

void OPENwall_vault(vector<string>* object_options,
	vector<string>* possession_options,
	bool* wall_vault_opened) {
	*wall_vault_opened = true;
	cout << "In the wall vault you find a black book.\n";
	RemoveOption(possession_options, "INSERT wooden rod");
	ReplaceOptions(object_options, vector<string> {"READ black book", "PICKUP black book"});
}

void OPENbox(vector<string>* possession_options,
	vector<string>* object_options,
	bool* box_opened) {
	if (IsIn(*object_options, "OPEN box")) {
		*box_opened = true;
		cout << "You insert the key and open the box.\n" <<
		"In the box, you find a wooden rod.\n";
		ReplaceOptions(object_options, vector<string> {"PICKUP wooden rod"});
		RemoveOption(possession_options, "INSERT key");
	}
	else {
		cout << "You insert the key into ... nothing.\n";
		EmptyOptions(object_options);
	}
}

//GROUP - possession objects like gun and books
void FIRE(vector<string>* object_options, 
	vector<string> possession_options, 
	vector<string>* room_options,
	bool* gun_shot, 
	bool* man_is_dead, 
	int room) {
	EmptyOptions(object_options);
	
	
	if ( !(*gun_shot) ) {
		(*gun_shot) = true;
		cout << "BANG!\n";
		if ( room == 3 && !(*man_is_dead) ){
			*man_is_dead = true;
			cout << "You killed the man. His body flops onto the floor, a puddle of blood forming from his chest.\n";
			EmptyOptions(room_options);
		}
	}
	else {
		cout << "The gun has no bullets left.\n";
	}
}


void READ(string book_type, 
	vector<string>* object_options, 
	vector<string> possession_options) {
	if (book_type == "red book") {
		cout << "You flip through the empty pages of the red book and find this message on a random page:\n" <<
			"1+(7*6/5)*8-(7^2)+(267/3)-(3*4*4)(25/49)^(5-11/2)\n";
	}
	else if (book_type == "black book") {
		cout << "You are flipping through the pages of the black book, and all of the pages are empty except for one.\n" <<
			"It has this message: (125/4)^(-120/240)/(1/5^0.5)+(26/20)*2\n";
	}
	if (!IsIn(possession_options, "READ " + book_type)) {
		ReplaceOptions(object_options, vector<string> {"PICKUP " + book_type});
	}
}

void PICKUPkey(vector<string>* possession_options) {
	AddOption(possession_options, "INSERT key");
	cout << "You have picked up the key.\n";
}

void PICKUPgun(vector<string>* possession_options) {
	AddOption(possession_options, "FIRE");
	cout << "You have picked up the gun.\n";
}

void PICKUPredbook(vector<string>* possession_options) {
	AddOption(possession_options, "READ red book");
	cout << "You have picked up the red book.\n";
}

void PICKUPblackbook(vector<string>* possession_options) {
	AddOption(possession_options, "READ black book");
	cout << "You have picked up the black book.\n";
}

void PICKUPwoodenrod(vector<string>* possession_options) {
	AddOption(possession_options, "INSERT wooden rod");
	cout << "You have picked up the wooden rod.\n";
}