#include "Framework.h"
#include "Color.h"

FColor::FColor()
{
	A = R = G = B = 0.0f;
}

FColor::FColor(float value)
{
	A = R = G = B = value;
}

FColor::FColor(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

FColor::FColor(UINT rgba)
{
	R = ((rgba >> 24) & 255) / 255.0f;
	G = ((rgba >> 16) & 255) / 255.0f;
	B = ((rgba >> 8) & 255) / 255.0f;
	A = (rgba & 255) / 255.0f;
}

FColor::FColor(int rgba)
{
	R = ((rgba >> 24) & 255) / 255.0f;
	G = ((rgba >> 16) & 255) / 255.0f;
	B = ((rgba >> 8) & 255) / 255.0f;
	A = (rgba & 255) / 255.0f;
}

FColor::FColor(float* values)
{
	R = values[0];
	G = values[1];
	B = values[2];
	A = values[3];
}

FColor::operator float* ()
{
	return RGBA;
}

FColor::operator const float* ()
{
	return RGBA;
}

bool FColor::operator==(const FColor& value2) const
{
	if (R == value2.R && G == value2.G && B == value2.B)
		return A == value2.A;
	else
		return false;
}

bool FColor::operator!=(const FColor& value2) const
{
	if (R == value2.R && G == value2.G && B == value2.B)
		return A != value2.A;
	else
		return true;
}

FColor FColor::operator+(const FColor& value2) const
{
	FColor color;
	color.R = R + value2.R;
	color.G = G + value2.G;
	color.B = B + value2.B;
	color.A = A + value2.A;

	return color;
}

FColor FColor::operator-(const FColor& value2) const
{
	FColor color;
	color.R = R - value2.R;
	color.G = G - value2.G;
	color.B = B - value2.B;
	color.A = A - value2.A;

	return color;
}

FColor FColor::operator*(const FColor& value2) const
{
	FColor color;
	color.R = R * value2.R;
	color.G = G * value2.G;
	color.B = B * value2.B;
	color.A = A * value2.A;

	return color;
}

FColor FColor::operator*(const float& scaleFactor) const
{
	FColor color;
	color.R = R * scaleFactor;
	color.G = G * scaleFactor;
	color.B = B * scaleFactor;
	color.A = A * scaleFactor;

	return color;
}

FColor FColor::operator/(const FColor& value2) const
{
	FColor color;
	color.R = R / value2.R;
	color.G = G / value2.G;
	color.B = B / value2.B;
	color.A = A / value2.A;

	return color;
}

FColor FColor::operator/(const float& divider) const
{
	float num = 1.0f / divider;

	FColor color;
	color.R = R * num;
	color.G = G * num;
	color.B = B * num;
	color.A = A * num;

	return color;
}

void FColor::operator+=(const FColor& value2)
{
	*this = *this + value2;
}

void FColor::operator-=(const FColor& value2)
{
	*this = *this - value2;
}

void FColor::operator*=(const FColor& value2)
{
	*this = *this * value2;
}

void FColor::operator*=(const float& scaleFactor)
{
	*this = *this * scaleFactor;
}

void FColor::operator/=(const FColor& value2)
{
	*this = *this / value2;
}

void FColor::operator/=(const float& divider)
{
	*this = *this / divider;
}

int FColor::ToRgba()
{
	UINT a = (UINT)(A * 255.0f) & 255;
	UINT r = (UINT)(R * 255.0f) & 255;
	UINT g = (UINT)(G * 255.0f) & 255;
	UINT b = (UINT)(B * 255.0f) & 255;

	UINT value = a;
	value |= b << 8;
	value |= g << 16;
	value |= r << 24;

	return (int)value;
}


int FColor::ToBgra()
{
	UINT a = (UINT)(A * 255.0f) & 255;
	UINT r = (UINT)(R * 255.0f) & 255;
	UINT g = (UINT)(G * 255.0f) & 255;
	UINT b = (UINT)(B * 255.0f) & 255;

	UINT value = a;
	value |= r << 8;
	value |= g << 16;
	value |= b << 24;

	return (int)value;
}

void FColor::ToBgra(byte& r, byte& g, byte& b, byte& a)
{
	a = (byte)(A * 255.0f);
	r = (byte)(B * 255.0f);
	g = (byte)(G * 255.0f);
	b = (byte)(R * 255.0f);
}

std::string FColor::ToString()
{
	std::string temp = "";
	temp += std::to_string(R);
	temp += "," + std::to_string(G);
	temp += "," + std::to_string(B);
	temp += "," + std::to_string(A);

	return temp;
}

FColor FColor::Add(FColor left, FColor right)
{
	return FColor(left.R + right.R, left.G + right.G, left.B + right.B, left.A + right.A);
}

FColor FColor::Subtract(FColor left, FColor right)
{
	return FColor(left.R - right.R, left.G - right.G, left.B - right.B, left.A - right.A);
}

FColor FColor::Modulate(FColor left, FColor right)
{
	return FColor(left.R * right.R, left.G * right.G, left.B * right.B, left.A * right.A);
}

FColor FColor::Scale(FColor value, float scale)
{
	return FColor(value.R * scale, value.G * scale, value.B * scale, value.A * scale);
}

FColor FColor::Negate(FColor value)
{
	return FColor(1.0f - value.R, 1.0f - value.G, 1.0f - value.B, 1.0f - value.A);
}

FColor FColor::Clamp(FColor val, FColor min, FColor max)
{
	float alpha = val.A;
	alpha = (alpha > max.A) ? max.A : alpha;
	alpha = (alpha < min.A) ? min.A : alpha;

	float red = val.R;
	red = (red > max.R) ? max.R : red;
	red = (red < min.R) ? min.R : red;

	float green = val.G;
	green = (green > max.G) ? max.G : green;
	green = (green < min.G) ? min.G : green;

	float blue = val.B;
	blue = (blue > max.B) ? max.B : blue;
	blue = (blue < min.B) ? min.B : blue;

	return FColor(red, green, blue, alpha);
}

FColor FColor::Max(FColor left, FColor right)
{
	FColor color;
	color.A = (left.A > right.A) ? left.A : right.A;
	color.R = (left.R > right.R) ? left.R : right.R;
	color.G = (left.G > right.G) ? left.G : right.G;
	color.B = (left.B > right.B) ? left.B : right.B;

	return color;
}

FColor FColor::Min(FColor left, FColor right)
{
	FColor color;
	color.A = (left.A < right.A) ? left.A : right.A;
	color.R = (left.R < right.R) ? left.R : right.R;
	color.G = (left.G < right.G) ? left.G : right.G;
	color.B = (left.B < right.B) ? left.B : right.B;

	return color;
}

///////////////////////////////////////////////////////////////////////////////

const FColor FColor::Aqua = FColor(0.0f, 1.0f, 1.0f);
const FColor FColor::Black = FColor(0.0f, 0.0f, 0.0f);
const FColor FColor::Blue = FColor(0.0f, 0.0f, 1.0f);
const FColor FColor::Cyan = FColor(0.0f, 1.0f, 1.0f);
const FColor FColor::Gray = FColor(0.5f, 0.5f, 0.5f);
const FColor FColor::Green = FColor(0.0f, 1.0f, 0.0f);
const FColor FColor::Magenta = FColor(1.0f, 0.0f, 1.0f);
const FColor FColor::Red = FColor(1.0f, 0.0f, 0.0f);
const FColor FColor::White = FColor(1.0f, 1.0f, 1.0f);
const FColor FColor::Yellow = FColor(1.0f, 1.0f, 0.0f);