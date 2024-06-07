#pragma once
#include "vector3.h"

double angle(vector3 v1, vector3 v2);

double distance(vector3 v1, vector3 v2);

double* pos2angles(vector3 v2, double* ln);

double* intersection(double dist, double rad1, double rad2);

vector3 angles2pos(double* ang, double* ln);

vector3* makeCircle(vector3 p1, vector3 p2, double h, int num = 1);

vector3 transform(vector3 v, double a1, double a2, double a3);