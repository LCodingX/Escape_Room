#include <iostream>
#include <vector>
#include <string>
#include "RoomObject.h"
#include "HelperFunctions.h"
using namespace std;


//this is what is called when the user types in "ACCESS red book"
//GROUP - books and gun and key
void red_book_called(
	vector<string>* object_options, 
	vector<string> possession_options) {

	if (IsIn(*object_options, "READ red book") || IsIn(possession_options, "READ red book")) {
		cout << "You flip through the empty pages of the red book and find this message on a random page:\n" <<
			"1+(7*6/5)*8-(7^2)+(267/3)-(3*4*4)(25/49)^(5-11/2)\n";
	}
	else {
		cout << "You do not have access to the red book.\n";
		return;
	}
	//if the book is not in your possession, you get the ability to pick it up.
	if (!IsIn(*object_options, "PICKUP red book") && !IsIn(possession_options, "READ red book")) {
		AddOption(object_options, "PICKUP red book");
		//does not replace options because if you assess the bookshelf then read the red book, 
		//you should be able to move the bookshelf.
	}
}

void black_book_called(
	vector<string>* object_options,
	vector<string> possession_options
) {
	//assuming that it the program has verified access to black book before calling this.
	cout << "You are flipping through the pages of the black book, and all of the pages are empty except for one.\n" <<
		"It has this message: (125/4)^(-120/240)/(1/5^0.5)+(26/20)*2\n";
	if (!IsIn(possession_options, "PICKUP black book")) {
		AddOption(object_options, "PICKUP black book");
	}
}

void key_called(
	vector<string>* object_options,
	vector<string> possession_options
) {

	if ( !IsIn(*object_options, "PICKUP key") && !IsIn(possession_options, "PICKUP key") ) {
		cout << "You do not have access to the key.\n";
	}
	else {
		cout << "It is a standard key from Home Depot.\n";
	}
}

//GROUP - vaults/locks
void vault_called(
	RoomObject vault,
	vector<string>* object_options,
	vector<string> possession_options,
	bool vault_opened,
	unsigned short int vault_attempts_left
) {
	if (vault_opened) {
		cout << "The vault is open.";
		if (IsIn(possession_options, "INSERT key") && IsIn(possession_options, "FIRE")) {
			cout << " It is empty.";
		}
		else if (IsIn(possession_options, "INSERT key")) {
			cout << " There is a gun in the vault.";
			AddOption(object_options, "PICKUP gun");
		}
		else if (IsIn(possession_options, "FIRE")) {
			cout << "There is a key in the vault.";
			AddOption(object_options, "PICKUP key");
		}
		else {
			cout << " The vault has a key and a gun in it.";
			AddOption(object_options, "PICKUP key");
			AddOption(object_options, "PICKUP gun");
		}
		cout << endl;
	}
	else {
		cout << "The vault is locked. It has a code-lock with digits 0-9.\n" <<
			"You have " << to_string(vault_attempts_left) << " attempts left.\n";
		if ( vault_attempts_left > 0 && !IsIn(*object_options, "TYPE vault [code]") ) {
			AddOption(object_options, "TYPE vault [code]");
		}
	}
}
void box_called(
	vector<string>* object_options,
	vector<string> possession_options,
	bool box_open,
	bool wall_vault_opened
) {
	if (!IsIn(*object_options, "MOVE bookshelf")) {
		cout << "You do not have access to the box without viewing the bookshelf first.\n";
	}
	if (!box_open) {
		cout << "The box is locked by a key lock.\n";
		if (IsIn(possession_options, "INSERT key") && !IsIn(*object_options, "OPEN box")) {
			AddOption(object_options, "OPEN box");
		}
	}
	else {
		if (!IsIn(possession_options, "INSERT wooden rod") && !wall_vault_opened) {
			cout << "In the box you find a wooden rod.\n";
			if (!IsIn(*object_options, "PICKUP wooden rod")) {
				AddOption(object_options, "PICKUP wooden rod");
			}
		}
		else {
			cout << "The box is empty.\n";
		}
	}
}
void wall_vault_called(
	RoomObject wall_vault, 
	vector<string>* object_options, 
	vector<string> possession_options, 
	bool wall_vault_opened
) {
	wall_vault.describe();
	if (!wall_vault_opened && IsIn(possession_options, "INSERT wooden rod") ) {
		AddOption(object_options, "OPEN wall vault");
	}
	else if (wall_vault_opened) {
		cout << "The vault is opened, revealing ";
		if (!IsIn(possession_options, "READ black book")) {
			cout << "a black book.\n";
			ReplaceOptions( object_options, vector<string> {"PICKUP black book", "READ black book"} );
		}
		else {
			cout << "nothing; It is empty.\n";
			ReplaceOptions( object_options, vector<string> {} );
		}
	}
	else {
		cout << "It is locked.\n";
		EmptyOptions(object_options);
	}
}
void door_lock_called(
	RoomObject door_lock,
	vector<string>* object_options,
	vector<string> possession_options,
	bool door_lock_opened
) {
	if (!door_lock_opened) {
		door_lock.describe();
		ReplaceOptions(object_options, vector<string> {"TYPE door lock [code]"});
	}
	else {
		cout << "The door lock is opened. You can go ahead and enter the next room, IF YOU DARE.\n";
	}
}

//ACCESS bookshelf - first gives you information, 
//then adds PICKUP red book, READ red book, and MOVE bookshelf to your options.
//USE key will already be an option if you have picked up the key from the vault.
// GROUP - doors and bookshelf
void bookshelf_called(
	RoomObject bookshelf, 
	vector<string>* object_options, 
	vector<string> possession_options, 
	bool box_opened,
	bool wall_vault_opened
) {

	vector<string> new_options = bookshelf.obj_options;
	bookshelf.describe();
	if ( !IsIn(possession_options, "READ red book") ) {
		cout << "On the bookshelf, there is a single red book.\n";
		new_options.push_back("PICKUP red book");
		new_options.push_back("READ red book");
	}
	if (!box_opened) {
		cout << "There is a box, which you find has a key lock.\n";
		if (IsIn(possession_options, "INSERT key")) {
			new_options.push_back("OPEN box");
		}
	}
	else {
		cout << "There is an opened box.";
		if (!wall_vault_opened && !IsIn(possession_options, "INSERT wooden rod")) {
			cout << " In the wooden box you find a rectangular wooden rod.\n";
			new_options.push_back("PICKUP wooden rod");
		}
		else {
			cout << " It is empty.\n";
		}
	}

	ReplaceOptions(object_options, new_options);
}

void door_1_called(RoomObject room_1_door, 
	vector<string>* object_options, 
	bool door_lock_opened) {
	room_1_door.describe();
	if (door_lock_opened) {
		ReplaceOptions(object_options, vector<string> {"OPEN door", "KNOCK"});
		cout << "The door cracks open.\n";
	}
	else {
		ReplaceOptions(object_options, vector<string> {"KNOCK"});
		cout << "The door is firmly shut and locked.\n";
	}
}

void door_2_called(RoomObject room_2_door, 
	vector<string>* object_options) {
	ReplaceOptions(object_options, room_2_door.get_obj_options());
	room_2_door.describe();
}

void door_3_called(RoomObject room_3_door,
	vector<string>* object_options
) {
	ReplaceOptions(object_options, room_3_door.get_obj_options());
	room_3_door.describe();
}