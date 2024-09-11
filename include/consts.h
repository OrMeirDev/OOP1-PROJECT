#pragma once 

#include <string>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 680;

const int MOUSE_MOVEMENTSPEED = 250;

const int TEXTURESIZE = 32;
const int FONTSINZE = 50;

const int ROWS = 15;
const int COLS = 40;

const int TIME_VALUE = 30;
const int FREEZE_TIMER = 5;

enum Direction {
	LEFT,
	UP,
	DOWN,
	RIGHT,
	STANDING
};

enum Types {
	KEYS,
	LIFE,
	SCORE,
	TIME, 
	LEVEL
};

// ============ Textures ============

const std::string MOUSE_TEXTURE = "mouse.png";
const std::string WALL_TEXTURE = "wall.png";
const std::string PATH_TEXTURE = "path.png";
const std::string NEWGAME_TEXTURE = "newgame.png";
const std::string HELP_TEXTURE = "helpbutton.png";
const std::string EXIT_TEXTURE = "exitbutton.png";
const std::string CHEESE_TEXTURE = "cheese.png";
const std::string PRESENT_TEXTURE = "present.png";
const std::string DOOR_TEXTURE = "door.png";
const std::string KEY_TEXTURE = "key.png";
const std::string BACKGROUND_TEXTURE = "background.png";
const std::string FREEZE_TEXTURE = "freezepresent.png";
const std::string LIFE_TEXTURE = "lifepresent.png";
const std::string TIME_TEXTURE = "timepresent.png";
const std::string KILLCAT_TEXTURE = "killcat.png";
const std::string CAT_TEXTURE = "cat.png";
const std::string CAT_CARTOON = "catcartoon.png";
const std::string HELPSCREEN_TEXTURE = "helpscreen.png";
const std::string GAMEOVER_TEXTURE = "gameover.png";
const std::string ENDGAME_TEXTURE = "endgame.png";
const std::string BACKTOMENU_TEXTURE = "menubutton.png";

// ============ Sounds ============

const std::string FREEZE_SOUND = "freeze.ogg";
const std::string KILL_SOUND = "kill.ogg";
const std::string TIME_SOUND = "time.ogg";
const std::string LIFE_SOUND = "life.ogg";
const std::string DEAD_SOUND = "dead.ogg";
const std::string DOOR_SOUND = "door.ogg";
const std::string KEY_SOUND = "key.ogg";
const std::string EAT_SOUND = "eat.ogg";