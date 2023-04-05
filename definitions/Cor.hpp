#ifndef Cor_h
#define Cor_h

struct Cor
{
	float r, g, b;

	Cor();
	Cor(float l);
	Cor(float r, float g, float b);

	virtual ~Cor();

	void clamp(float mini = 0.0f, float maxi = 1.0f);
	void correcaoGama(float exposicao, float gama);

	Cor& operator =(const Cor& c);
	Cor& operator +=(const Cor& c);
	Cor& operator *=(const Cor& c);
	Cor& operator *=(float f);
};

inline Cor operator +(const Cor& c1, const Cor& c2)
{
	return Cor(c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b);
}

inline Cor operator *(const Cor& c1, const Cor& c2)
{
	return Cor(c1.r * c2.r,
		c1.g * c2.g,
		c1.b * c2.b);
}

inline Cor operator *(const Cor& c, float f)
{
	return Cor(c.r * f,
		c.g * f,
		c.b * f);
}

inline Cor operator *(float f, const Cor& c)
{
	return Cor(f * c.r,
		f * c.g,
		f * c.b);
}

#endif