#include <iostream>
#include <string>
#include <vector>
#include "RoomObject.h"
using namespace std;

RoomObject::RoomObject(int Id, string Description, vector<string> Obj_options) {
		id = Id;
		description = Description;
		obj_options = Obj_options;
	}
void RoomObject::describe() {
	cout << description << endl;
}
vector<string> RoomObject::get_obj_options() {
	return obj_options;
}