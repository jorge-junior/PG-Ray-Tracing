#ifndef Intersecoes_h
#define Intersecoes_h

#include <iostream>
#include <vector>
#include "Ray.cpp"

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
	float ka, kd, ks, eta;
	Vec3 posicao;
	Vec3 normal;
	Cor cor;

public:
	Plano(float ka, float kd, float ks, float eta,
		  const Vec3 &posicao, const Vec3 &normal,
		  const Cor &cor = Cor(1.0f, 1.0f, 1.0f));

	virtual ~Plano();

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

class Esfera : public Forma
{
public:
	float ka, kd, ks, eta;
	Vec3 centro;
	float raio;
	Cor cor;

public:
	Esfera(float ka, float kd, float ks, float eta,
		   const Vec3 &centro, float raio,
		   const Cor &cor = Cor(1.0f, 1.0f, 1.0f));

	virtual ~Esfera();

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

class Triangulo : public Forma
{
protected:
	float ka, kd, ks, eta;
	vector<Vec3> vertices;
	Vec3 normal;
	Cor cor;

public:
	Triangulo(float ka, float kd, float ks, float eta,
			  const vector<Vec3> &vertices, const Vec3 &normal,
			  const Cor &cor = Cor(1.0f, 1.0f, 1.0f));

	virtual ~Triangulo();

	virtual bool intersecta(Intersecao &intersecao);
	virtual bool INTERSECTA(const Ray &ray);
};

#endif