#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include<ios>
#include<limits>
#include "RoomObject.h"
#include "HelperFunctions.h"
#include "AssessObjects.h"
#include "ObjectCommands.h"
using namespace std;
// Interactive Story

// You are trapped in a locked room with water is being poured into the room.
// pull open the red book, look at the message.
// "1+(7*6/5)*8-(7^2)+(267/3)-(3*4*4)(25/49)^(5-11/2)"
// Type in 41 into a vault. Open it and you get a key
// The key does not work on the door, it works on a box. In the box, you find a wooden rod.
// You must move the bookshelf. Behind it is a key-like handle.
// Insert the wooden rod into the handle, you find a black book.
// You also find a loaded gun.
// The message says "(2/55)/(4/110)+(125/4)^(-120/240)/(1/5^0.5)"
// Type in 3 into the door.
// You see a flight of stairs with water trickling down, when you go to the top, there is a door.
// When you go inside the room, you see a killer clown, like out of a horror movie, staring right at you.
// The clown runs at you with a knife, with a crazy laugh.
// When you shoot the clown, run and escape.


int main() {

	//predefining the room_options you start with. Room options is reset when you enter a new room.
	vector<string> room_options;
	room_options.reserve(3);
	room_options = { "ASSESS", "ASSESS [object, use spaces]", "QUIT"};

	//predefining the object options
	//the object options are what you are going to be able to do with the 
	//with the objects that you are assessing.
	//example 1: bookshelf
	//when you assess it, the object_options vector will gain the string "MOVE"
	vector<string> object_options;
	object_options.reserve(8);

	//predefining the options you get from your possessions.
	//example 1: gun
	//when you pick up the gun, you will be able to shoot it for the entire game, 
	//but if you shoot it before, you run out of bullets.
	//if you shoot it while in room 3, you kill the clown. Then you climb into an elevator and escape.
	//example 2: red book.
	//you can read the red book for the entire game, the ability will be in the options.
	//predefining the main objects in room 1
	string bookshelf_desc = "It is too big to put in your pocket.";
	RoomObject bookshelf(0, 
		bookshelf_desc,
		vector<string> {"MOVE bookshelf"});

	string door_lock_desc = "Has a keycode with digits 0, 1, 2, 3, 4.\nYou have unlimited attempts and it seems to want a 2-digit solution.";
	RoomObject door_lock(1, 
		door_lock_desc, 
		vector<string> {"TYPE door lock [code]"});

	string string_r1_door_desc = "A solid sturdy, metal door. A small hole at the bottom of the door lets water under.";
	RoomObject room_1_door(2,
		string_r1_door_desc,
		vector<string> {"KNOCK"});

	string vault_desc = "A vault. It has a keycode with digits 0-9. You only get 3 attempts.";
	RoomObject vault(3,
		vault_desc,
		vector<string> {"TYPE vault [code]"});

	string wall_vault_desc = "A vault built into the wall, that has a rectangular shaped opening in the center.";
	RoomObject wall_vault(4,
		wall_vault_desc,
		vector<string> {"PULL"});

	string room_2_door_desc = "A solid sturdy, metal door. A small hole at the bottom of the door lets water under.";
	RoomObject room_2_door(5,
		room_2_door_desc,
		vector<string> {"KNOCK", "OPEN door"});

	string room_3_door_desc = "A solid sturdy, metal door. A small hole at the bottom of the door lets water under.";
	RoomObject room_3_door(6,
		room_3_door_desc,
		vector<string> {"KNOCK", "OPEN door"});


	//you don't start out with any possessions, but you pick up stuff as you go through.
	//you can pick up the red book and black book, but it is not necessary.
	//you also pick up the gun and the wooden rod.
	vector<string> possession_options;
	possession_options.reserve(4);

	//These keep track of the progression of the game.
	int room = 1;
	string command; // the user command
	bool vault_opened = false;
	bool box_opened = false;
	bool bookshelf_moved = false;
	bool wall_vault_opened = false;
	bool door_lock_opened = false;
	bool gun_shot = false; // the gun only has one bullet. This will be edited via a reference in a function.
	bool man_is_dead = false;
	unsigned short int vault_attempts_left = 3;

	//start of the loop. ends when you exit the room
	//the things done inside of the room are
	//1: telling you your options.
	//2: letting you choose what you do
	//3: telling you the consequence of your action (ex: assessing gives a message)
	//4: changing the conditions for the next loop 
	//conditions: room, bools defined above, object_options, possession_options
	IntroText();

	while (room != 4) {

		PrintOptions(object_options, possession_options, room_options, false);

		//user input
		command.clear();
		cout << "\n:";
		cin.ignore(0, '\n');
		getline(cin, command);

		if ( room == 3 && !man_is_dead && command != "FIRE" && command != "NEGOTIATE" ){
			cout << "You do not have that option. Please enter a different command.\n";
			continue;
		}

		if (command.size() < 4) { // if the command 
			// is less than 4 letters or the last letter is a space
			cout << "That is an invalid input in some way. \n" <<
				"Make sure that you are not using [], those were just to separate the object, like in linux.\n";
			EmptyOptions(&object_options);
			continue;
		}
		//what happens due to each user input.
		else if (command == "QUIT") {
			cout << "Goodbye! Sad to see you go :(" << endl;
			return 0;
		}

		//if you assess, it will describe the room you are in.
		else if (command == "ASSESS") {
			EmptyOptions(&object_options);
			//it will depend on the room you are in
			if (room == 1) {
				cout << "You look around and see a door and a door lock to it.\n";
				if (!IsIn(possession_options, "READ red book")) {
					cout << "You see a bookshelf with a single book and a box.\n";
				}
				else {
					cout << "You see a bookshelf with a box.\n";
				}
				if (bookshelf_moved) {
					cout << "You see a vault inside of the wall.\n";
					if (wall_vault_opened) {
						cout << "It is opened, revealing "; 
						if (IsIn(possession_options, "READ black book")) {
							cout << "nothing. It is empty.\n";
						}
						else {
							cout << "a black book.\n";
						}

					}
				}
				if (vault_opened) {
					cout << "There is an open vault.";
					if (IsIn(possession_options, "INSERT key") && IsIn(possession_options, "FIRE")) {
						cout << " It is empty.";
					}
					else if (IsIn(possession_options, "INSERT key")) {
						cout << " There is a gun in the vault.";
					}
					else if (IsIn(possession_options, "FIRE")) {
						cout << "There is a key in the vault.";
					}
					else {
						cout << " The vault has a key and a gun in it.";
					}
					cout << endl;
				}
				else {
					cout << "You see a locked vault. It has a keycode with digits 0-9 and has " << vault_attempts_left << " attempts left.\n";
				}
			}
			else if (room == 2) {
				cout << "You see a stairway leading up to a door" << endl;
			}
			else if (room == 3) {
				cout << "It is a dark room, a laboratory smeared with blood.\n";
				if (!man_is_dead) {
					cout << "You no longer have access to this command.";
				}
				else {
					cout << "You are relieved to see a door at the back of the laboratory.\n";
				}

			}
			continue;
		}

		//this is when the user is assessing a single object.
		//we want to see what the object name is, make sure it is real
		//then add the options and describe the object.
		else if ( CommandStartsWith(command, "ASSESS ", 3) ) {

			//make all objects lowercase
			string object_viewing = command.substr(7, command.size() - 7);
			transform(object_viewing.begin(), object_viewing.end(), object_viewing.begin(),
				[](unsigned char c) { return tolower(c); });

			EmptyOptions(&object_options);
			// GROUP - Bookshelf and doors
			if (object_viewing == "bookshelf") {
				if (room == 1) {
					bookshelf_called(bookshelf, &object_options, 
						possession_options, box_opened, wall_vault_opened);
				}
				else {
					cout << "You are not in the first room, you cannot view the bookshelf.\n";
				}
				continue;
			}

			else if (object_viewing == "door") {
				if (room == 1) {
					door_1_called(room_1_door, &object_options, door_lock_opened);
				}
				else if (room == 2) {
					door_2_called(room_2_door, &object_options);
				}
				else if (room == 3) {
					door_3_called(room_3_door, &object_options);
				}
				continue;
			}

			//GROUP - Books, gun, wooden rod, and gun.
			else if (object_viewing == "black book") {
				if (!IsIn(possession_options, "READ black book") && !IsIn(object_options, "READ black book")) {
					cout << "You do not have access to the black book.\n";
				}
				else {
					black_book_called(&object_options, possession_options);
				}
				continue;
			}
			else if (object_viewing == "red book") {
				red_book_called(&object_options, possession_options);
				continue;
			}


			//GROUP - Locks and vaults
			else if (object_viewing == "box") {
				box_called( &object_options, possession_options, box_opened, wall_vault_opened );
				continue;
			}
			else if (object_viewing == "vault") {
				if (room == 1) {
					vault_called(vault, &object_options, possession_options, vault_opened, vault_attempts_left);
				}
				else {
					cout << "You are not in the first room, you cannot view the vault.\n";
				}
				continue;
			}
			else if (object_viewing == "wall vault") {
				if (room == 1 && bookshelf_moved) {
					wall_vault_called(wall_vault, &object_options, possession_options, wall_vault_opened);
				}
				else {
					cout << "You do not have access to the wall vault.\n";
				}
				continue;
			}
			else if (object_viewing == "door lock") {
				if (room == 1) {
					door_lock_called(door_lock, &object_options, possession_options, door_lock_opened);
				}
				else {
					cout << "You are not in the first room.\n";
				}
				continue;
			}
			else {
				//this means that the user assesses something that does not exist in the game.
				//ex: red_book. tell them that it is wrong and start over.
				cout << "That is not a valid object. To get all of the names of the valid objects, type HELP.\n";
				object_options.clear();
			}
		}


		//GROUP - gun, books
		else if (command == "FIRE") {
			if (IsIn(possession_options, "FIRE")) {
				FIRE(&object_options, possession_options, &room_options, &gun_shot, &man_is_dead, room);
		}
			else {
				cout << "You do not have access to that object\n";
			}
		}

		else if (command == "READ red book") {
			if (!IsIn(object_options, "READ red book") && !IsIn(possession_options, "READ red book") ) {
				cout << "You do not have access to the red book.\n";
				EmptyOptions(&object_options);
			}
			else {
				READ("red book", &object_options, possession_options);
			}
		}

		else if (command == "READ black book") {
			if (IsIn(object_options, "READ black book") || IsIn(possession_options, "READ black book")) {
				READ("black book", &object_options, possession_options);
			}
			else {
				cout << "You do not have access to the black book.\n";
				EmptyOptions(&object_options);
			}
		}

		//GROUP - vaults, keys, wooden rod
		else if ( CommandStartsWith(command, "TYPE vault ", 1) ) {
			if (IsIn(object_options, "TYPE vault [code]")) {
				TYPE_vault(command, &object_options, &vault_opened, &vault_attempts_left);
			}
			else {
				cout << "You can't do that.\n";
			}
		}

		else if ( CommandStartsWith(command, "TYPE door lock ", 1) ) {
			if (IsIn(object_options, "TYPE door lock [code]")) {
				TYPE_door_lock(command, &object_options, &door_lock_opened);
			}
			else {
				cout << "You can't do that.\n";
			}
		}

		else if (command == "INSERT key") {
			if (IsIn(possession_options, "INSERT key")) {
				INSERTkey(&object_options, &possession_options, &box_opened);
			}
			else {
				cout << "You do not have the key.\n";
			}
		}
		else if (command == "INSERT wooden rod") {
			if (IsIn(possession_options, "INSERT wooden rod")) {
				INSERTwoodenrod(&object_options, &possession_options, &wall_vault_opened);
			}
			else {
				cout << "You do not have the wooden rod.\n";
			}
		}
		else if (command == "OPEN wall vault") {
			if (IsIn(object_options, "OPEN wall vault")) {
				OPENwall_vault(&object_options, &possession_options, &wall_vault_opened);
			}
			else {
				cout << "You do not have access to do that currently.\n";
			}
		}
		else if (command == "OPEN box") {
			if (IsIn(object_options, "OPEN box")) {
				OPENbox(&possession_options, &object_options, &box_opened);
			}
			else {
				cout << "You cannot currently open the box.\n";
			}
		}
		else if (command == "PICKUP key") {
			if (IsIn(object_options, "PICKUP key")) {
				EmptyOptions(&object_options);
				if (!IsIn(possession_options, "FIRE")) {
					AddOption(&object_options, "PICKUP gun");
				}
				PICKUPkey(&possession_options);
			}
			else {
				cout << "You cannot pick that up.\n";
			}
		}
		else if (command == "PICKUP gun") {
			if (IsIn(object_options, "PICKUP gun")) {
				EmptyOptions(&object_options);
				if (!IsIn(possession_options, "INSERT key")) {
					AddOption(&object_options, "PICKUP key");
				}
				PICKUPgun(&possession_options);
			}
			else {
				cout << "You cannot pick that up.\n";
			}
		}
		else if (command == "PICKUP red book") {
			if (IsIn(object_options, "PICKUP red book")) {
				EmptyOptions(&object_options);
				PICKUPredbook(&possession_options);
			}
			else {
				cout << "You cannot pick that up.\n";
			}
		}
		else if (command == "PICKUP black book") {
			if (IsIn(object_options, "PICKUP black book")) {
				EmptyOptions(&object_options);
				PICKUPblackbook(&possession_options);
			}
			else {
				cout << "You cannot pick that up.\n";
			}
		}
		else if (command == "PICKUP wooden rod") {
			if (IsIn(object_options, "PICKUP wooden rod")) {
				EmptyOptions(&object_options);
				PICKUPwoodenrod(&possession_options);
			}
			else {
				EmptyOptions(&object_options);
				cout << "You cannot pick that up.\n";
			}
		}
		//make a pickup option! make a help option!

		//GROUP - bookshelf, stairs, doors
		else if (command == "MOVE bookshelf") {
			if ( IsIn(object_options, "MOVE bookshelf") && room == 1 ) {
				MOVE(&bookshelf_moved);
			}
			else {
				cout << "You are not in that room.\n";
			}
			EmptyOptions(&object_options);
		}
		else if (command == "KNOCK") {
			if (IsIn(object_options, "KNOCK")) {
				KNOCK(room);
			}
			else {
				cout << "You can't do that.\n";
			}
		}
		else if (command == "OPEN door") {
			if (IsIn(object_options, "OPEN door")) {
				OPEN(&object_options, &room_options, &possession_options, &room);
			}
			else {
				cout << "You can't do that.\n";
			}
		}
		else if (command == "CLIMB stairway") {
			if (room == 2) {
				RemoveOption(&object_options, "CLIMB stairway");
				CLIMB(&object_options);
			}
			else {
				cout << "You do not have access to the stairs.\n";
			}
		}
		else if (command == "NEGOTIATE") {
			if (IsIn(room_options, "NEGOTIATE")) {
				NEGOTIATE();
				return 0;
			}
			else {
				cout << "You cannot do that.\n";
			}
		}

		else if (command == "HELP") {
			//typing HELP will do the following:
			//tell you all of the objects you can access, including possession options
			//tells you every single command that you can run.

			cout << "Sorry that you are confused. I hope this list helps you out." << endl;
			cout << "All of the objects that you can assess or have already used are\n" << 
				"(though you may need to assess other things in order to access them):\n";
			//these are the room objects
			if (room == 1) {
				cout << "bookshelf\nvault\ndoor\ndoor lock\nbox\nred book\n"; 
				//room1objects(vault_opened, box_opened, bookshelf_moved, wall_vault_opened);
				if (vault_opened)
					cout << "key\ngun\n";
				if (box_opened) 
					cout << "wooden rod\n";
				if (bookshelf_moved)
					cout << "wall vault\n";
				if (wall_vault_opened)
					cout << "black book\n";
			}
			else {
				cout << "door\n";
				//possession objects, if outside of room 1
				if (IsIn(possession_options, "INSERT wooden rod")) 
					cout << "wooden rod\n";
				if (IsIn(possession_options, "FIRE")) 
					cout << "gun\n";
				if (IsIn(possession_options, "INSERT key")) 
					cout << "key\n";
				if (IsIn(possession_options, "READ red book")) 
					cout << "red book\n";
				if (IsIn(possession_options, "READ black book"))
					cout << "black book\n";
			}
			cout << "All of your options are:\n" <<
				"ASSESS, ASSESS [object],\n" <<
				"HELP, QUIT\n";
			PrintOptions(object_options, possession_options, room_options, true);
		}
		else {
			cout << "That is not a valid command.\n";
		}
	}
	cout << "Congrulations, you have made it to the end of the escape room.\n";
	return 0;
}