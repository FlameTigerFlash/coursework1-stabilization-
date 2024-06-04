#pragma once
#include "vector3.h"

double angle(vector3 v1, vector3 v2);

double distance(vector3 v1, vector3 v2);

double* moveData(vector3 v2, double rad);

vector3* makeCircle(vector3 p1, vector3 p2, double h, int num = 1);

double* transform(double v[3], double a1, double a2, double a3);