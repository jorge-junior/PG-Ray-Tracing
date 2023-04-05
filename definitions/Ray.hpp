#ifndef Ray_h
#define Ray_h

#include "Vetor.hpp"
#include "Cor.hpp"

// raios refletidos nao intersectarem com eles mesmos
#define rayTMin 0.0001f

// distancia infinita valor padrao
#define rayTMax 1.0e30f

struct Ray
{
	Ponto origem;
	Vec3 direcao;
	float tMax;

	Ray();
	Ray(const Ray& r);
	Ray(const Ponto& origem, const Vec3& direcao,
		float tMax = rayTMax);

	virtual ~Ray();

	Ray& operator =(const Ray& r);

	Ponto calcular(float t) const;
};

class Forma;

struct Intersecao
{
	Ray ray;
	float t;
	Forma *pForma;
	Cor cor;

	Intersecao();
	Intersecao(const Intersecao& i);
	Intersecao(const Ray& ray);

	virtual ~Intersecao();

	Intersecao& operator =(const Intersecao& i);

	bool intersectou() const;
	Ponto posicao() const;
};

#endif