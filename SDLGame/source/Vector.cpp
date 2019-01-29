#include "headers/Vector.h"

Vector::Vector()
{
	this->x = 0;
	this->y = 0;
}

Vector::Vector(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector::~Vector() = default;

int Vector::GetX() const
{
	return this->x;
}

int Vector::GetY() const
{
	return this->y;
}

void Vector::SetX(int value)
{
	this->x = value;
}

void Vector::SetY(int value)
{
	this->y = value;
}

Vector Vector::Up()
{
	return Vector(0, -1);
}

Vector Vector::Down()
{
	return Vector(0, 1);
}

Vector Vector::Left()
{
	return Vector(-1, 0);
}

Vector Vector::Right()
{
	return Vector(1, 0);
}

void Vector::Multiply(int mult)
{
	this->x *= mult;
	this->y *= mult;
}

bool Vector::operator==(const Vector & vec2) const
{
	return (this->x == vec2.GetX() && this->y == vec2.GetY());
}

bool Vector::operator!=(const Vector& vec2) const
{
	return !(this->x == vec2.GetX() && this->y == vec2.GetY());
}

Vector& Vector::operator+=(const Vector& vec2)
{

	this->x += vec2.x;
	this->y += vec2.y;
	return *this;
}

Vector& Vector::operator+(const Vector& vec2)
{
	Vector vec;
	vec.x = this->x + vec2.GetX();
	vec.y = this->y + vec2.GetY();
	return vec;
}

Vector& Vector::operator*(const Vector& vec2)
{
	Vector vec;
	vec.x = this->x * vec2.GetX();
	vec.y = this->y * vec2.GetY();
	return vec;
}
