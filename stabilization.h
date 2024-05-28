struct pos
{
	double x = 0;
	double y = 0;
	double z = 0;
};

enum states { straight, stable, unstable };


template<typename T> T clamp(T, T, T);

pos* stabilize(pos* cur);