#pragma once


#include "Core.h"
// std
#include <iostream>
#include <time.h>
#include <math.h>
#include <functional>
#include <random>
#include <unordered_set>
#include <fstream>
#include <codecvt>

// 자료구조
#include <unordered_map>
#include <queue>
#include <cassert>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "Singleton.h"

#include "json.hpp"
using json = nlohmann::json;
#include "InputManager.h"
#include "ResourcesManager.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "ColliderManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SoundManger.h"
#include "SaveLoadManger.h"

#include "Defines.h"
#include "Utils.h"
#include "DataTable.h"
#include "StringTable.h"

#include "DataTableManager.h"
// Utils

// Objec
#include "GameObject.h"
#include "Entity.h"

#include "SaveData.h"