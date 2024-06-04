#pragma once
#include "vector3.h"

enum states { straight, stable, unstable };

template<typename T> T clamp(T, T, T);

vector3* stabilize(vector3* cur);