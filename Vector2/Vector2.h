//
//  Vector2.h
//  Vector2
//
//  Created by Евгений Дьячков on 28.02.17.


#include <iostream>
#include <cmath>

/*
Старайтесь никогда в с++ не использовать define
Пишите const float PI = 3.14159265f;
*/

#define PI 3.14159265

struct Vector2 {
    float x;
    float y;
    Vector2(float x, float y);
    Vector2();
    float operator ^ (const Vector2& other) const;
    float operator * (const Vector2& other) const;
    float len() const;
    float squareLen() const;
    Vector2 perpendicular() const;
    Vector2 norm() const;
    Vector2& rotate(float degree);
    Vector2 getRotated(float degree) const;
    Vector2 operator * (float k) const;
    Vector2 operator / (float k) const;
    Vector2 operator - () const;
    Vector2 operator + (const Vector2& other) const;
    Vector2& operator += (const Vector2& other);
    Vector2 operator - (const Vector2& other) const;
    Vector2& operator -= (const Vector2& other);
    
};

Vector2 operator*(float k, const Vector2& v);

std::ostream& operator <<(std::ostream& stream, const Vector2& v);
std::istream& operator >> (std::istream& stream, Vector2& v);
