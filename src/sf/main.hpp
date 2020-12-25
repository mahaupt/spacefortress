#pragma once

#include "game.hpp"
#include "tools/config.hpp"
#include "tools/console.hpp"
#include "tools/lang.hpp"
#include "tools/log.hpp"
#include "ui/inputtext.hpp"
#include "ui/menu.hpp"
#include "ui/menuitem.hpp"
#include "ui/text.hpp"

#ifdef WIN32
#include <Windows.h>
#pragma execution_character_set("utf-8")
#endif

enum MainState { MAIN_MENU, CREW_CREATE, CREW_JOIN, GAME };

/**
 * Callbacks
 */
void main_endProgram(void);
void main_startCrewCreate(void);
void main_startCrewJoin(void);
void main_stopGame(void);
void main_backToMenu(void);
void main_startGameCreate(void);
void main_startGameJoin(void);
void main_setError(const char* error);
