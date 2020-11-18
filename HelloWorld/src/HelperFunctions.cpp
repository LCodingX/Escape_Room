#include <iostream>
#include <vector>
#include <string>
using namespace std;

//This is for room objects, like the bookshelf.

bool IsIn(vector<string> optionsVect, string option) {
	for (string tempOption : optionsVect) {
		if (tempOption == option) {
			return true;
		}
	}
	return false;
}

void AddOption(vector<string>* options_vect, string option) {
	vector<string> obj_opts_dupe = *options_vect;
	obj_opts_dupe.push_back(option);
	*options_vect = obj_opts_dupe;
}

void ReplaceOptions(vector<string>* options_vect, vector<string> new_options) {
	*options_vect = new_options;
}

void EmptyOptions(vector<string>* options_vect) {
	*options_vect = vector<string> {};
}

void RemoveOption(vector<string>* options_vect, string option) {
	vector<string> actual_vect = *options_vect;
	for (unsigned int idx = 0; idx < actual_vect.size(); idx++) {
		if (actual_vect[idx] == option) {
			actual_vect.erase(actual_vect.begin() + idx);
			ReplaceOptions(options_vect, actual_vect);
			break;
		}
	}
}

void PrintOptions(vector<string> object_options,
	vector<string> possession_options,
	vector<string> room_options, bool calledHelp) {
	//tell the user all of their options, including the room options and the object options.
	bool vectors_empty = (object_options.empty() && possession_options.empty());
	if (!calledHelp) {
		if (!vectors_empty) {
			cout << "Options: \n";
		}
		else {
			cout << "\nOptions:\nASSESS\nASSESS [object]\nQUIT\nHELP\n";
		}
	}
	//loops through the room and object options, printing them all out.
	for (string curr_opt_o : object_options) {
		cout << curr_opt_o << endl;
	}
	for (string curr_opt_p : possession_options) {
		cout << curr_opt_p << endl;
	}
	if (IsIn(room_options, "NEGOTIATE")) {
		cout << "NEGOTIATE" << endl;
	}
}

void IntroText() {
	//introduction messages
	cout<< "WELCOME TO VINCE'S ESCAPE ROOM. GOOD LUCK!" << endl
		<< "You wake up confused, trapped in an unfamiliar room." << endl
		<< "The ground feels wet." << endl
		<< "You realize that water is filling into the room from under the door." << endl
		<< "You remember hearing about a number of local disappearances in your area and curse aloud.\n"
		<< "ENTER QUIT to exit the game or HELP when you are confused." << endl
		<< "Remember not to leave unnecessary spaces, but do include spaces when they are in the name of the objects you are viewing." << endl;
}

bool CommandStartsWith(string command, string substring, int min_string_close_len) {
	// the substring should be something like "ASSESS ", 
	// then the min_string_close_len would be 3.
	// first it makes sure that the command is long enough to 
	// do the substr() function and not throw an error 
	if (command.length() < substring.length() + min_string_close_len) {
		return false;
	}
	// then it checks to see if it starts with the substring.
	else if ( (string) command.substr(0, substring.length()) == substring) {
		return true;
	}
	//if not, return false
	return false;
}