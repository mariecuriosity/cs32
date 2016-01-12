#ifndef CONSTANTS_INCLUDED
#define CONSTANTS_INCLUDED

using namespace std;
#include <string>

struct Coord
{
public:
	Coord(int rr, int cc, int dd, char dir) : m_r(rr), m_c(cc), m_d(dd), m_dir(dir){}
	int r() const { return m_r; }
	int c() const { return m_c; }
	int d() const { return m_d; }
	char dir() const { return m_dir; }
private:
	int m_r;
	int m_c;
	int m_d;
	char m_dir;
};

const Coord DEFAULT_COORD = Coord(0, 0, 0, 'f');


const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const string HIT = "hits";
const string MISS = "misses";
const string W_SS = "short sword";
const string W_LS = "long sword";
const string W_M = "mace";
const string W_MA = "magic axe";
const string W_MF = "magic fangs of sleep";
const string W_SSAc = "slashes"; //short sword action = slashes
const string W_LSAc = "swings";
const string W_MFAc = "strikes";
const string W_MAc = "swings";
const string W_MAAc = "swings";
const string S_ED = "scroll of enhance dexterity";
const string S_EH = "scroll of enhance health";
const string S_IA = "scroll of improve armor";
const string S_RS = "scroll of raise strength";
const string S_T = "scroll of teleportation";
const string DUNGEON_OBJECT_LIST[7] = { W_SS, W_LS, W_M ,S_ED,S_EH,S_IA,S_RS};
const string SCROLL_LIST[5] = { S_ED, S_EH, S_IA, S_RS, S_T };
const string DEFAULT_STRING;
const string GOBLIN_DROP_LIST[2] = { W_MA, W_MF };
const int LEVEL_ROWS = 18;
const int LEVEL_COLS = 70;
const int NUM_ROOMS = 5;
const int MIN_ROOM_ROW = 4;
const int MIN_ROOM_COL = 7;
const int MAX_ROOM_ROW = 10;
const int MAX_ROOM_COL = 12;
const int MAX_MONSTERS = 26;
const char M_S = 'S'; //snakewomen
const char M_G = 'G'; //goblins
const char M_B = 'B'; //bogeyman
const char M_D = 'D'; //dragons
const char M_P = 'P'; //player
const char MONSTER_LIST[5] = { M_S, M_G, M_B, M_D, M_P };
const char EMPTY_SPACE = ' ';
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const double PLAYERS_HP_REGAIN_PROB = .1;
const double DRAGONS_HP_REGAIN_PROB = .1;
const double SNAKEWOMEN_HP_REGAIN_PROB = 0;
const double GOBLINS_HP_REGAIN_PROB = 0;
const double BOGEYMEN_HP_REGAIN_PROB = 0;
const int PLAYER_MAX_INVENTORY = 25;
const int MAX_OBJECTS = 65;
const int W_SS_D = 2;
const int W_LS_D = 4;
const int W_M_D = 2;
const int W_MA_D = 5;
const int W_MF_D = 2;
const int W_SS_DB = 0;
const int W_LS_DB = 2;
const int W_M_DB = 0;
const int W_MA_DB = 5;
const int W_MF_DB = 3;

#endif CONSTANTS_INCLUDED