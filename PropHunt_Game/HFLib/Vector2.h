#pragma once
#include <math.h>

class Vector2{
public:
	float x, y;
	Vector2(){
		x = y = 0.0f;
	}
	Vector2(float p_x, float p_y){
		x = p_x;
		y = p_y;
	}
	~Vector2(){

	}

	void Translate(float p_x, float p_y){
		x += p_x;
		y += p_y;
	}

	Vector2 operator=(float other[2]){
		x = other[0];
		y = other[1];
	}

	bool operator==(float other[2]){
		return(x == other[0] && y == other[1]);
	}

	bool operator!=(float other[2]){
		return(x != other[0] || y != other[1]);
	}

	bool operator==(Vector2 other){
		return(x == other.x || y == other.y);
	}

	bool operator!=(Vector2 other){
		return(x != other.x || y != other.y);
	}

	void operator+=(float other[2]){
		this->x += other[0];
		this->y += other[1];
	}

	void operator+=(Vector2 other){
		this->x += other.x;
		this->y += other.y;
	}

	void operator-=(float other[2]){
		this->x -= other[0];
		this->y -= other[1];
	}

	void operator-=(Vector2 other){
		this->x -= other.x;
		this->y -= other.y;
	}

	Vector2 operator+(float other[2]){
		Vector2 newVec;
		newVec.x = this->x + other[0];
		newVec.y = this->y + other[1];
		return newVec;
	}

	Vector2 operator+(Vector2 other){
		Vector2 newVec;
		newVec.x = this->x + other.x;
		newVec.y = this->y + other.y;
		return newVec;
	}

	Vector2 operator-(float other[2]){
		Vector2 newVec;
		newVec.x = this->x - other[0];
		newVec.y = this->y - other[1];
		return newVec;
	}

	Vector2 operator-(Vector2 other){
		Vector2 newVec;
		newVec.x = this->x - other.x;
		newVec.y = this->y - other.y;
		return newVec;
	}

	Vector2 operator-(){
		Vector2 newVec;
		newVec.x = -this->x;
		newVec.y = -this->y;
	}

	Vector2 operator*(float other){
		Vector2 newVec;
		newVec.x = this->x * other;
		newVec.y = this->y * other;
		return newVec;
	}

	void operator*=(float other){
		this->x *= other;
		this->y *= other;
	}

	Vector2 operator/(float other){
		Vector2 newVec;
		newVec.x = this->x / other;
		newVec.y = this->y / other;
		return newVec;
	}

	void operator/=(float other){
		this->x /= other;
		this->y /= other;
	}

	float Magnitude(){
		return (pow(this->x, 2) + pow(this->y, 2));
	}

	static float SqrDistance(Vector2 vec1, Vector2 vec2){
		Vector2 vec = vec1 - vec2;
		return(pow(vec.x, 2) + pow(vec.y, 2));
	}

	static float Distance(Vector2 vec1, Vector2 vec2){
		return sqrtf(SqrDistance(vec1, vec2));
	}

	static Vector2 Lerp(Vector2& vec1, Vector2& vec2, float factor){
		factor = factor > 1.0f ? 1.0f : factor;
		factor = factor < 0.0f ? 0.0f : factor;
		return Vector2::LerpUnclamped(vec1, vec2, factor);
	}

	static Vector2 LerpUnclamped(Vector2& vec1, Vector2& vec2, float factor){
		Vector2 newVec = vec1 * (1.0f - factor) + vec2 * factor;
		return newVec;
	}

	static Vector2 Up(){
		Vector2 vec(0.0f, 1.0f);
		return vec;
	}

	static Vector2 Down(){
		return -Vector2::Up();
	}

	static Vector2 Right(){
		Vector2 vec(1.0f, 0.0f);
		return vec;
	}

	static Vector2 Left(){
		return -Vector2::Right();
	}
};