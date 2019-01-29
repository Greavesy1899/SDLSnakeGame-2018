#pragma once
#ifndef VectorFile
#define VectorFile
class Vector
{
public:
	//constructors/deconstructors
	Vector();
	Vector(int x, int y);
	~Vector();

	//accessors
	int GetX() const;
	int GetY() const;
	void SetX(int value);
	void SetY(int value);

	//already defined vectors;
	static Vector Up();
	static Vector Down();
	static Vector Left();
	static Vector Right();

	//functions
	void Multiply(int mult);

	bool operator ==(const Vector& vec2) const;
	bool operator !=(const Vector& vec2) const;
	Vector& operator+=(const Vector& vec2);
	Vector& operator+(const Vector& vec2);
	Vector& operator*(const Vector& vec2);
private:
	int x;
	int y;
};
#endif