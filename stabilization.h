#pragma once

enum states { straight, stable, unstable };

template<typename T> T clamp(T, T, T);

//pos* stabilize(pos* cur);