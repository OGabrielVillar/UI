#pragma once

#ifdef HZ_PLATFORM_WINDOWS
 #include <Windows.h>
#endif

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <cmath>
#include <utility>
#include <stack>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <random>

//

#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <entt/entt.hpp>

//

#undef CreateWindow

#include "Core/Base.h"

#include "Core/Time/Timer.h"

#include "Core/Data/Flags.h"
#include "Core/Data/Stack.h"
#include "Core/Data/SliderEnumeration.h"
#include "Core/Data/Tree.h"
#include "Core/Data/UUID.h"

#include "Core/Debug/Profiler.h"
#include "Core/Debug/Log.h"
#include "Core/Debug/Dummy.h"

#include "Core/Math/MathCommon.h"
#include "Core/Math/Random.h"

#include "Core/Geometry/Rect.h"
#include "Core/Geometry/Polygon.h"
#include "Core/Geometry/Angle.h"
#include "Core/Geometry/Circle.h"
#include "Core/Geometry/Transformation.h"

#include "Core/Using.h"


