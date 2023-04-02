#include <iostream>

#include "Ray.hpp"
#include "Vetor.hpp"

using namespace std;

Ray::Ray()
	: origem(0.0f, 0.0f, 0.0f),
	direcao(),
	tMax(rayTMax)
{}

Ray::Ray(const Ray& r)
	: origem(r.origem),
	direcao(r.direcao),
	tMax(r.tMax)
{}

Ray::Ray(const Ponto& origem, const Vec3& direcao, float tMax)
	: origem(origem),
	direcao(direcao),
	tMax(tMax)
{}

Ray::~Ray(){}

Ray& Ray::operator =(const Ray& r)
{
	origem = r.origem;
	direcao = r.direcao;
	tMax = r.tMax;
	return *this;
}

Ponto Ray::calcular(float t) const
{
	return origem + direcao * t;
}


Intersecao::Intersecao()
	: ray(),
	t(rayTMax),
	pForma(NULL)
{}

Intersecao::Intersecao(const Intersecao& i)
	: ray(i.ray),
	t(i.t),
	pForma(i.pForma)
{}

Intersecao::Intersecao(const Ray& ray)
	: ray(ray),
	t(ray.tMax),
	pForma(NULL)
{}

Intersecao::~Intersecao(){}

Intersecao& Intersecao::operator =(const Intersecao& i)
{
	ray = i.ray;
	t = i.t;
	pForma = i.pForma;
	return *this;
}

bool Intersecao::intersectou() const
{
	return (pForma != NULL);
}

Ponto Intersecao::posicao() const
{
	return ray.calcular(t);
}