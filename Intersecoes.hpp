#ifndef Intersecoes_h
#define Intersecoes_h

#include <iostream>
#include <vector>
#include "Vetor.hpp"
#include "Ray.hpp"

using namespace std;

// interseções de planos e esferas apenas

class Forma
{
public:
	virtual ~Forma() {}

	virtual bool intersecta(Intersecao &intersecao) = 0;
	virtual bool INTERSECTA(const Ray &ray) = 0;
};

class formatar : public Forma
{
protected:
	vector<Forma *> formas;

public:
	formatar();

	virtual ~formatar();

	void addForma(Forma *forma);

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

class Plano : public Forma
{
protected:
	Ponto posicao;
	Vec3 normal;
	Cor cor;

public:
	Plano(const Ponto &posicao, const Vec3 &normal,
		  const Cor &cor = Cor(1.0f, 1.0f, 1.0f));

	virtual ~Plano();

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

class Esfera : public Forma
{
protected:
	Ponto centro;
	float raio;
	Cor cor;

public:
	Esfera(const Ponto &centro, float raio,
		   const Cor &cor = Cor(1.0f, 1.0f, 1.0f));

	virtual ~Esfera();

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

class Triangulo : public Forma
{
protected:
	vector<Ponto> vertices;
	Vec3 normal;
	Cor cor;

public:
	Triangulo(const vector<Ponto> &vertices, const Vec3 &normal,
			  const Cor &cor = Cor(1.0f, 1.0f, 1.0f));

	virtual ~Triangulo();

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

#endif