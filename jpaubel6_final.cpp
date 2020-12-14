#include <iostream>
#include <string>
#include <cctype>
#include <vector>


using namespace std;


enum en_DIRS {NORTH, EAST, SOUTH, WEST};


enum en_ROOMS {BALLROOM, CENTRAL_ROOM, KITCHEN, BARRACKS, TRAINING_ROOM, GUARD_ROOM, PRISON_STAIRS, WALKWAY1, WALKWAY3, GUEST_BEDROOM1, ROYAL_BATH, DINING_AREA, GRAND_ENTRYHALL, TEA_ROOM, GATEWAY, JAIL, INTERROGATION_ROOM, WALKWAY2, ENTERTAINMENT_ROOM, GRAND_BALCONY, GUEST_BEDROOM2, ROYAL_MASTER_BEDROOM, WALKWAY5, ROYAL_HALL, HALLWAY, FOYER, BALCONY, GUEST_BEDROOM3, LOUNGE, ROYAL_QUARTERS, LAUNDRY_ROOM, SERVANTS_BEDROOM, SERVANT_QUARTERS2, COURTYARD, SERVANT_QUARTERS, SERVANT_BEDROOM2, SITTING_ROOM, ROYAL_BEDROOM, GATEHOUSE, GARDEN};


enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};


enum en_NOUNS {PRISON_DOOR, MAGNET, MONEY, LOCKET, FUZZ, RING, MATCH, TORCH, GEMS, BOOK, DIAMOND, DRUM, KEY, POTION, CHESS, GOBLET};


const int NONE = -1;
const int DIRS = 4;
const int ROOMS = GARDEN + 1;
const int VERBS = 8;
const int NOUNS = 16;


// Max length of any vector
static const int maxLength = 50;

class Word {
	string word;
	int code;

	public: Word(int code, string word) {
		this->code = code;
		this->word = word;
	}

	public: Word() { // Initialize a cell in a vector.
		this->code = NONE;
		this->word = "UNDEFINED";
	}

	public: ~Word() {
		// Nothing to free
	}

	public: int getCode() {
		return code;
	}

	public: string getWord() {
		return word;
	}
};



class Room {

	int code;
	string description;
	int exits_to_room[DIRS];
	
	public: Room(int code, string description, int north, int east, int south, int west) {
		this->code=code;
		this->description = description;
		exits_to_room[NORTH] = north;
		exits_to_room[EAST] = east;
		exits_to_room[SOUTH] = south;
		exits_to_room[WEST] = west;
	}

	public: Room() {
		code = NONE;
		description = "UNINITIALIZED";
		exits_to_room[NORTH] = NONE;
		exits_to_room[EAST] = NONE;
		exits_to_room[SOUTH] = NONE;
		exits_to_room[WEST] = NONE;
	}

	public: ~Room() {
		// Nothing to delete!
	}
	
	public: string getDescription() {
		return description;
	}

	public: int getCode() {
		return code;
	}
	
	public: int getExitCode(int direction) {
		return exits_to_room[direction];
	}

	public: void setExitCode(int direction, int code) {
		exits_to_room[direction] = code;
	}

};



class Noun {

	string word;
	string description;
	int code;
	int location;
	bool canCarry;

	public: Noun(int code, string word, string description, int location, bool canCarry) {
		this->code = code;
		this->word = word;
		this->description = description;
		this->location = location;
		this->canCarry = canCarry;
	}

	public: Noun() {
		word = "Undefined";
		description = "Undefined";
		code = NONE;
		location = NONE;
		canCarry = false;
	}

	public: int getLocation(){
		return location;
	}

	public: string getWord(){
		return word;
	}

	public: string getDescription(){
		return description;
	}

	public: bool getCanCarry(){
		return canCarry;
	}

	public: void setLocation(int location) {
		this->location = location;
	}

	public: int getCode(){
		return code;
	}
	
	public: void setDescription(string description) {
		this->description = description;
	}

};



void set_rooms(vector<Room> &rms) {

	rms.at(FOYER) = Room(FOYER, "beautiful ballroom", NONE, NONE, GRAND_ENTRYHALL, NONE);
	rms.at(GRAND_ENTRYHALL) = Room(GRAND_ENTRYHALL, "grand elabrate main room", FOYER, ENTERTAINMENT_ROOM, CENTRAL_ROOM, TEA_ROOM);
	rms.at(CENTRAL_ROOM) = Room(CENTRAL_ROOM, "grand elabrate main room", GRAND_ENTRYHALL, GARDEN, BARRACKS, BALLROOM);
	rms.at(KITCHEN) = Room(KITCHEN, "kitchen", BALLROOM, NONE, NONE, DINING_AREA);
	rms.at(BARRACKS) = Room(BARRACKS, "barracks", CENTRAL_ROOM, TRAINING_ROOM, GUARD_ROOM, NONE);
	rms.at(TRAINING_ROOM) = Room(TRAINING_ROOM, "training room", GARDEN, NONE, NONE, BARRACKS);
	rms.at(GUARD_ROOM) = Room(GUARD_ROOM, "empty guard room", BARRACKS, PRISON_STAIRS, NONE, NONE);
	rms.at(PRISON_STAIRS) = Room(PRISON_STAIRS, "staircase connecting interrogation room & jail", NONE, GATEWAY, NONE, GUARD_ROOM);
	rms.at(WALKWAY1) = Room(WALKWAY1, "long beautiful walk way", NONE, WALKWAY2, NONE, GATEHOUSE);
	rms.at(WALKWAY3) = Room(WALKWAY3, "long beautiful walk way", HALLWAY, GUEST_BEDROOM3, NONE, ROYAL_HALL); 
	rms.at(GUEST_BEDROOM1) = Room(GUEST_BEDROOM1, "first gest bedroom", NONE, NONE, NONE, WALKWAY2);
	rms.at(ROYAL_BATH) = Room(ROYAL_BATH, "grand bathroom", NONE, NONE, ROYAL_HALL, ROYAL_MASTER_BEDROOM);
	rms.at(DINING_AREA) = Room(DINING_AREA, "grand dining room area", GRAND_BALCONY, KITCHEN,  SITTING_ROOM, NONE);
	rms.at(WALKWAY2) = Room(WALKWAY2, "long beautiful walk way", NONE, GUEST_BEDROOM1, HALLWAY, WALKWAY1);	
	rms.at(TEA_ROOM) = Room(TEA_ROOM, "tea room", NONE, GRAND_ENTRYHALL, BALLROOM, LOUNGE); 	
	rms.at(GATEWAY) = Room(GATEWAY, "gateway", INTERROGATION_ROOM, NONE, JAIL, PRISON_STAIRS);	
	rms.at(JAIL) = Room(JAIL, "rows of basement jail cells", GATEWAY, NONE, NONE, NONE);	
	rms.at(INTERROGATION_ROOM) = Room(INTERROGATION_ROOM, "basement interrogation room", NONE, NONE, GATEWAY, NONE);
	rms.at(ENTERTAINMENT_ROOM) = Room(ENTERTAINMENT_ROOM, "fun large room", SERVANT_BEDROOM2, LAUNDRY_ROOM, GARDEN,GRAND_ENTRYHALL);	
	rms.at(GRAND_BALCONY) = Room(GRAND_BALCONY, "beautiful grand balcony", LOUNGE, BALLROOM, DINING_AREA, NONE);	
	rms.at(GUEST_BEDROOM2) = Room(GUEST_BEDROOM2, "second guest bedroom ", NONE, BALCONY, NONE, HALLWAY);
	rms.at(ROYAL_MASTER_BEDROOM) = Room(ROYAL_MASTER_BEDROOM, "royal master bedroom", NONE, ROYAL_BATH, ROYAL_QUARTERS,  NONE);
	rms.at(ROYAL_HALL) = Room(ROYAL_HALL, "royal hallway", ROYAL_BATH, WALKWAY3, NONE, ROYAL_QUARTERS);
	rms.at(HALLWAY) = Room(HALLWAY, "huge hallway", WALKWAY2, GUEST_BEDROOM2, WALKWAY3, NONE);	
	rms.at(BALCONY) = Room(BALCONY, "guest bedroom balcony", NONE, NONE, NONE, GUEST_BEDROOM2);
	rms.at(GUEST_BEDROOM3) = Room(GUEST_BEDROOM3, "third guest bedroom", NONE, NONE, NONE, WALKWAY3);
	rms.at(LOUNGE) = Room(LOUNGE, "lounge", SERVANT_QUARTERS, TEA_ROOM, GRAND_BALCONY, NONE);
	rms.at(ROYAL_QUARTERS) = Room(ROYAL_QUARTERS, "royal living quarters", ROYAL_MASTER_BEDROOM, ROYAL_HALL, NONE, NONE);
	rms.at(LAUNDRY_ROOM) = Room(LAUNDRY_ROOM, "laundry room", SERVANT_QUARTERS2, NONE, COURTYARD, ENTERTAINMENT_ROOM);	
	rms.at(SERVANTS_BEDROOM) = Room(SERVANTS_BEDROOM, "servent bedroom", NONE, NONE, NONE, SERVANT_QUARTERS);
	rms.at(SERVANT_QUARTERS2) = Room(SERVANT_QUARTERS2, "second servant living quarters", NONE, NONE, LAUNDRY_ROOM, SERVANT_BEDROOM2);
	rms.at(COURTYARD) = Room(COURTYARD, "little courtyard", LAUNDRY_ROOM, NONE, NONE, GARDEN);
	rms.at(SERVANT_QUARTERS) = Room(SERVANT_QUARTERS, "servent living quarters", NONE, SERVANTS_BEDROOM, LOUNGE, NONE);
	rms.at(SERVANT_BEDROOM2) = Room(SERVANT_BEDROOM2, "second servant bedroom", NONE, SERVANT_QUARTERS2, ENTERTAINMENT_ROOM, NONE);
	rms.at(BALLROOM) = Room(BALLROOM, "large ballroom", TEA_ROOM, CENTRAL_ROOM, KITCHEN, GRAND_BALCONY);
	rms.at(GARDEN) = Room(GARDEN, "garden", ENTERTAINMENT_ROOM, COURTYARD, TRAINING_ROOM, CENTRAL_ROOM);
	rms.at(SITTING_ROOM) = Room(SITTING_ROOM, "relaxing sitting room", DINING_AREA, NONE, GATEHOUSE, NONE);
	rms.at(GATEHOUSE) = Room(GATEHOUSE, "gatehouse", SITTING_ROOM, WALKWAY1, NONE, NONE);
}


void set_directions(vector<Word> &dir) {

	dir.at(NORTH) = Word(NORTH, "NORTH");
	dir.at(EAST) = Word(EAST, "EAST");
	dir.at(SOUTH) = Word(SOUTH, "SOUTH");
	dir.at(WEST) = Word(WEST, "WEST");
}


void set_verbs(vector<Word> &vbs) {

	vbs.at(GET) = Word(GET, "GET");
	vbs.at(DROP) = Word(DROP, "DROP");
	vbs.at(USE) = Word(USE, "USE");
	vbs.at(OPEN) = Word(OPEN, "OPEN");
	vbs.at(CLOSE) = Word(CLOSE, "CLOSE");
	vbs.at(EXAMINE) = Word(EXAMINE, "EXAMINE");
	vbs.at(INVENTORY) = Word(INVENTORY, "INVENTORY");
	vbs.at(LOOK) = Word(LOOK, "LOOK");

}


void set_nouns(vector<Noun> &nns) {

	nns[PRISON_DOOR] = Noun(PRISON_DOOR, "DOOR",     "a closed store room door", GUARD_ROOM,  false);
	nns[MAGNET]     = Noun(MAGNET,     "MAGNET",   "a magnet",                 GUEST_BEDROOM1,      false);
	nns[POTION]      = Noun(POTION,      "POTION",    "a potion bottle",       GUARD_ROOM,   false);
	nns[CHESS]   = Noun(CHESS,         "CHESS",    "a chess board",            ENTERTAINMENT_ROOM,    false);
	nns[MONEY]      = Noun(MONEY,      "MONEY",    "some money",               BALLROOM,      true);
	nns[GOBLET] = Noun(GOBLET,         "GOBLET",   "a silver goblet",            DINING_AREA, false);
	nns[LOCKET]     = Noun(LOCKET,     "LOCKET",        "a small gold locket",                      LAUNDRY_ROOM,     true);
	nns[FUZZ]       = Noun(FUZZ,       "FUZZ",        "a piece fuzz",                        GRAND_ENTRYHALL,     true);
	nns[RING]       = Noun(RING,       "RING",        "a tacky ring",                        LOUNGE,     true);
	nns[MATCH]      = Noun(MATCH,      "MATCH ",        "a single burnout match",                        KITCHEN,     true);
	nns[TORCH]      = Noun(TORCH,      "TORCH",        "a torch",                        TRAINING_ROOM,     false);
	nns[GEMS]       = Noun(GEMS,       "GEMS",     "a pile of gems",           INTERROGATION_ROOM,     true);
	nns[BOOK]       = Noun(BOOK,       "BOOK",        "a ornate book",                        SERVANTS_BEDROOM,     true);
	nns[DIAMOND]    = Noun(DIAMOND,    "DIAMOND",        "beautiful diamond",                        ROYAL_MASTER_BEDROOM,    true);
	nns[DRUM]       = Noun(DRUM,       "DRUM",        "a large drum",                        ENTERTAINMENT_ROOM,    false);
	nns[KEY]	    = Noun(KEY,        "KEY",      "a silver key",             INTERROGATION_ROOM,    true);
}


void section_command(string Cmd, string &wd1, string &wd2) {

	string sub_str;
	vector<string> words;
	char search = ' ';
	size_t i, j;

	for(i=0; i < Cmd.size(); i++) {

		if(Cmd.at(i) != search) {
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}

		if(i == Cmd.size()-1) {
			words.push_back(sub_str);
			sub_str.clear();
		}

		if(Cmd.at(i) == search) {
			words.push_back(sub_str);
			sub_str.clear();
		}

	}

	for(i=words.size()-1; i > 0; i--) {


		if(words.at(i)=="") {

			words.erase(words.begin() + i);

		}

	}

	for(i = 0; i < words.size(); i++) {

		for(j = 0; j < words.at(i).size(); j++) {

			if(islower(words.at(i).at(j))) {

				words.at(i).at(j) = toupper(words.at(i).at(j));

			}
		}
	}
	
	if(words.size() == 0) {


		cout<< "No command given" << endl;

	}

	if(words.size() == 1) {

		wd1 = words.at(0);

	}
	
	if(words.size() == 2) {

		wd1 = words.at(0);
		wd2 = words.at(1);

	}

	if(words.size() > 2) { 

		cout <<"Command is too long. Only type one or two words: direction or verb and noun" << endl;

	}

}

static vector<int> bag;
static int hand;

void look_around(int loc, vector<Room> &rms, vector<Word> &dir, vector<Noun> &nns) {

	int i;
	cout << "I am in a " << rms[loc].getDescription() << "." << endl;

	for(i=0; i < DIRS; i++) {

		if(rms[loc].getExitCode(i) != NONE) {
			
			cout << "There is an exit " << dir[i].getWord() << " to a " << rms[rms[loc].getExitCode(i)].getDescription() << "." << endl;

		}

	}

	for(i = 0; i < NOUNS; i++) {

		if(nns[i].getLocation() == loc) {
			cout << "I see " << nns[i].getDescription() << "." << endl;
		}

	}

}





void getIt(int locCode, int nounCode, vector<Noun> &nns) {
	int i;

	for (i = 0; i < NOUNS; i++) {

		if (nns[i].getLocation() == locCode) {
			if (nounCode == nns[i].getCode() || nounCode == NONE) {
				if (nns[i].getCanCarry()) {
					bag.push_back(i);
					nns[i].setLocation(NONE);
					cout << "You picked up " << nns[i].getDescription() << endl;
				} else {
					cout << "You cannot carry " << nns[i].getDescription() << "!" <<endl;
				}
			}
		}
	}
}

void dropIt(Room &loc, int nounCode, vector<Noun> &nns) {
	int i;
	Noun* noun;

	for (i = 0; i < bag.size(); i++) {
		
		if (bag.at(i) == nounCode) {
			bag.erase(bag.begin() + i);
			noun = &nns[nounCode];
			noun->setLocation(loc.getCode());
			cout << "You set down " << noun->getDescription() << " in a " << loc.getDescription() << endl;
		}
	}
}


void examine(int nounCode, vector<Noun> &nns) {
	int i;
	Noun* noun;

	for (i = 0; i < bag.size(); i++) {
		
		if (bag.at(i) == nounCode) {
			noun = &nns[nounCode];
			cout << noun->getDescription() << endl;
		}

	}
}



void useIt(int nounCode, vector<Noun> &nns) {
	int i;
	Noun* noun;

	for (i = 0; i < bag.size(); i++) {
		if (bag.at(i) == nounCode) {
			noun = &nns[nounCode];
			cout << "You have " << noun->getDescription() << " in your hand." << endl;
			hand = nounCode;
		}
	}
}




void display(vector<int> &bag, vector<Noun> &nns) {
    if (bag.size() > 0) {
        for (unsigned int i = 0; i < bag.size(); ++i)
        {
            cout << nns[bag[i]].getWord() << ": " <<nns[bag[i]].getDescription() << endl;
        }
    }
    else {
        cout << "My bag is empty." << endl;
    }
}




bool parser(int &loc, string wd1, string wd2, vector<Word> &dir, vector<Word> &vbs, vector<Room> &rms, vector<Noun> &nns) {

	static bool door_state = false;

	int i;

	for(i = 0; i < DIRS; i++) {

		if(wd1 == dir[i].getWord()) {

			if(rms[loc].getExitCode(i) != NONE) {

				loc = rms[loc].getExitCode(i);
				cout << "I am now in a " << rms[loc].getDescription() << "." << endl;

				if(loc == PRISON_STAIRS || loc == GUARD_ROOM) {

					nns[PRISON_DOOR].setLocation(loc);

				}

				return true;

			}

			else {
				
				cout << "No exit that way." << endl;

			}

		}
	}

	int NOUN_MATCH = NONE;

	int VERB_ACTION = NONE;

	for (i = 0; i < VERBS; i++) {

		if(wd1 == vbs[i].getWord()) {
			
			VERB_ACTION = vbs[i].getCode();
			break;

		}

	}


	if(wd2 != " ") {

		for(i = 0; i < NOUNS; i++) {

			if(wd2 == nns[i].getWord()) {
				NOUN_MATCH = nns[i].getCode();
				break;
			}

		}
	}

	if(VERB_ACTION == NONE) {

		cout << "No valid command entered." << endl;
		return true;

	}

	if(VERB_ACTION == LOOK) {

		look_around(loc, rms, dir, nns);
		return true;

	} 
	
	else if (VERB_ACTION == GET) {
		getIt(loc, NOUN_MATCH, nns);
		return true;
	} 
	
	else if (VERB_ACTION == DROP) {

		dropIt(rms[loc], NOUN_MATCH, nns);
		return true;
	} 
	
	else if (VERB_ACTION == USE) {

		useIt(NOUN_MATCH, nns);
		return true;

	} 
	
	else if (VERB_ACTION == CLOSE) {
		if(NOUN_MATCH == PRISON_DOOR) {

			if(loc == GUARD_ROOM || loc == PRISON_STAIRS) {

				if (door_state == true) {

					door_state = false;
					rms[GUARD_ROOM].setExitCode(EAST, NONE);
					rms[PRISON_STAIRS].setExitCode(WEST, NONE);
					nns[PRISON_DOOR].setDescription("a closed store room door");
					return true;

				}

			
				else if(door_state == false) {

					cout << "The door is already closed." << endl;
					return true;
				}

			}
		

			else {

				cout << "There is no door to closed here." << endl;
				return true;

			}

			
		}

		else {

			cout << "Closing that is not possible." << endl;
		}
	} 

	
	
	else if (VERB_ACTION == EXAMINE) {

		examine(NOUN_MATCH, nns);
		return true;

	} 
	
	else if (VERB_ACTION == INVENTORY) {

    	display(bag, nns);
		return true;

	
	}




	if(VERB_ACTION == OPEN) {

		if(NOUN_MATCH == PRISON_DOOR) {

			if(loc == GUARD_ROOM || loc == PRISON_STAIRS) {

				if (door_state == false) {

					if (hand != KEY) {
						cout << "You do not have a key in your hand." << endl;
						return true;
					}

					door_state = true;
					rms[GUARD_ROOM].setExitCode(EAST, PRISON_STAIRS);
					rms[PRISON_STAIRS].setExitCode(WEST, GUARD_ROOM);
					nns[PRISON_DOOR].setDescription("");
					nns[PRISON_DOOR].setDescription("an open store room door");

					return true;

				}

			
				else if(door_state == true) {

					cout << "The door is already open." << endl;
					return true;
				}

			}
		

			else {

				cout << "There is no door to open here." << endl;
				return true;

			}

			
		}

		else {

			cout << "Opening that is not possible." << endl;
		}

	}

	return false;
}

int main() {

	string command;
	string word_1;
	string word_2;

	vector<Room> rooms(ROOMS);
	set_rooms(rooms);

	vector<Word> direction(DIRS);
	set_directions(direction);

	vector<Word> verbs(VERBS);
	set_verbs(verbs);

	vector<Noun> nouns(NOUNS);
	set_nouns(nouns);

	int location = JAIL;

	while(word_1 != "Quit") {

		command.clear();
		cout << "What shall I do?";
		getline(cin, command);

		word_1.clear();
		word_2.clear();

		section_command(command, word_1, word_2);

		if(word_1 != "Quit") {
			parser(location, word_1, word_2, direction, verbs, rooms, nouns);
		}

		
	}
	
	return 0;
	
}