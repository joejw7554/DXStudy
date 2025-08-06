#pragma once

class FColor
{
public:
	FColor();
	FColor(float value);
	FColor(float r, float g, float b, float a = 1.0f);
	FColor(UINT rgba);
	FColor(int rgba);
	FColor(float* values);

	operator float* ();
	operator const float* ();

	bool operator ==(const FColor& value2) const;
	bool operator !=(const FColor& value2) const;

	FColor operator +(const FColor& value2) const;
	FColor operator -(const FColor& value2) const;
	FColor operator *(const FColor& value2) const;
	FColor operator *(const float& scaleFactor) const;
	FColor operator /(const FColor& value2) const;
	FColor operator /(const float& divider) const;

	void operator +=(const FColor& value2);
	void operator -=(const FColor& value2);
	void operator *=(const FColor& value2);
	void operator *=(const float& scaleFactor);
	void operator /=(const FColor& value2);
	void operator /=(const float& divider);

	int ToRgba();
	int ToBgra();
	void ToBgra(byte& r, byte& g, byte& b, byte& a);

	std::string ToString();


	static FColor Add(FColor left, FColor right);
	static FColor Subtract(FColor left, FColor right);
	static FColor Modulate(FColor left, FColor right);
	static FColor Scale(FColor value, float scale);
	static FColor Negate(FColor value);

	static FColor Clamp(FColor val, FColor min, FColor max);
	static FColor Max(FColor left, FColor right);
	static FColor Min(FColor left, FColor right);

public:
	union
	{
		struct
		{
			float R, G, B, A;
		};

		float RGBA[4];
	};

	///////////////////////////////////////////////////////////////////////////////

public:
	static const FColor Aqua;
	static const FColor Black;
	static const FColor Blue;
	static const FColor Cyan;
	static const FColor Gray;
	static const FColor Green;
	static const FColor Magenta;
	static const FColor Red;
	static const FColor White;
	static const FColor Yellow;
};