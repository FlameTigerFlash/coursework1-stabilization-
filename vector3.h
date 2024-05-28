class vector3
{
public:
	double x = 0;
	double y = 0;
	double z = 0;

	vector3(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vector3(const vector3& vec1);

	double len();
	vector3 operator +(const vector3& vec2);
	vector3 operator -(const vector3& vec2);
	vector3 operator *(double num);
	vector3& operator=(const vector3& vec2);
	vector3 normalized (double num);
	double distance(const vector3& vec2);
};