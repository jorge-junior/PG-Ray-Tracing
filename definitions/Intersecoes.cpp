#include "Intersecoes.hpp"
#include "Vetor.cpp"

using namespace std;

formatar::formatar() {}

formatar::~formatar() {}

void formatar::addForma(Forma *forma)
{
	formas.push_back(forma);
}

bool formatar::intersecta(Intersecao &intersecao)
{
	bool INTERSECTA = false;
	for (vector<Forma *>::iterator iter = formas.begin();
		 iter != formas.end();
		 ++iter)
	{
		Forma *formaAtual = *iter;
		if (formaAtual->intersecta(intersecao))
			INTERSECTA = true;
	}
	return INTERSECTA;
}

bool formatar::INTERSECTA(const Ray &ray)
{
	for (vector<Forma *>::iterator iter = formas.begin();
		 iter != formas.end();
		 ++iter)
	{
		Forma *formaAtual = *iter;
		if (formaAtual->INTERSECTA(ray))
			return true;
	}

	return false;
}

Plano::Plano(const Ponto &posicao, const Vec3 &normal,
			 const Cor &cor) : posicao(posicao),
							   normal(normal),
							   cor(cor)
{
}

Plano::~Plano() {}

bool Plano::intersecta(Intersecao &intersecao)
{
	// verifica se intersecta
	float prodEscDirNor = pr_esc(intersecao.ray.direcao, normal);
	if (prodEscDirNor == 0.0f)
	{
		return false;
	}

	// acha ponto de intersecao
	float t = pr_esc(posicao - intersecao.ray.origem, normal) / prodEscDirNor;
	if (t <= rayTMin || t >= intersecao.t)
	{
		return false;
	}
	intersecao.t = t;
	intersecao.pForma = this;
	intersecao.cor = cor;
	return true;
}

bool Plano::INTERSECTA(const Ray &ray)
{
	// verifica se intersecta
	float prodEscDirNor = pr_esc(ray.direcao, normal);
	if (prodEscDirNor == 0.0f)
	{
		return false;
	}
	// acha o ponto de intersecao
	float t = pr_esc(posicao - ray.origem, normal) / prodEscDirNor;
	if (t <= rayTMin || t >= ray.tMax)
	{
		return false;
	}
	return true;
}

Esfera::Esfera(const Ponto &centro, float raio,
			   const Cor &cor)
	: centro(centro),
	  raio(raio),
	  cor(cor)
{
}

Esfera::~Esfera() {}

bool Esfera::intersecta(Intersecao &intersecao)
{
	// transformacao pra considerar o centro da esfera na origem
	Ray localRay = intersecao.ray;
	localRay.origem -= centro;
	// calcula os coeficientes
	float a = localRay.direcao.comp2();
	float b = 2 * pr_esc(localRay.direcao, localRay.origem);
	float c = localRay.origem.comp2() - qdd(raio);
	// verifica se intersecta
	float discriminante = qdd(b) - 4 * a * c;
	if (discriminante < 0.0f)
	{
		return false;
	}
	// acha dois pontos de intersecao t1 perto t2 longe
	float t1 = (-b - sqrt(discriminante)) / (2 * a);
	float t2 = (-b + sqrt(discriminante)) / (2 * a);

	// verifica se há um valor de t válido
	if ((t1 < rayTMin || t1 > intersecao.t) && (t2 < rayTMin || t2 > intersecao.t))
	{
		return false;
	}
	// verifica se t1 eh valido
	if (t1 > rayTMin && t1 < intersecao.t)
	{
		intersecao.t = t1;
	}
	// verifica se t2 eh valido e menor que t1
	if (t2 > rayTMin && t2 < intersecao.t && t2 < t1)
	{
		intersecao.t = t2;
	}

	intersecao.pForma = this;
	intersecao.cor = cor;
	return true;
}

bool Esfera::INTERSECTA(const Ray &ray)
{
	// transformacao pra considerar o centro da esfera na origem
	Ray localRay = ray;
	localRay.origem -= centro;
	// calcula coefcientes
	float a = localRay.direcao.comp2();
	float b = 2 * pr_esc(localRay.direcao, localRay.origem);
	float c = localRay.origem.comp2() - qdd(raio);
	// verifica se intersecta
	float discriminante = qdd(b) - 4 * a * c;
	if (discriminante < 0.0f)
	{
		return false;
	}
	// dois pontos de intersecao t1 perto t2 longe
	float t1 = (-b - sqrt(discriminante)) / (2 * a);
	if (t1 > rayTMin && t1 < ray.tMax)
		return true;
	float t2 = (-b + sqrt(discriminante)) / (2 * a);
	if (t2 > rayTMin && t2 < ray.tMax)
		return true;
	return false;
}

Triangulo::Triangulo(const vector<Ponto> &vertices, const Vec3 &normal,
					 const Cor &cor)
	: vertices(vertices),
	  normal(normal),
	  cor(cor)
{
}

Triangulo::~Triangulo() {}

bool Triangulo::intersecta(Intersecao &intersecao)
{
	// triangle edge vectors

	Vec3 edge1 = vertices[1] - vertices[0];
	Vec3 edge2 = vertices[2] - vertices[0];
	Vec3 h = pr_vet(intersecao.ray.direcao, edge2);

	// check if ray is parallel

	float a = pr_esc(edge1, h);
	if (a == 0)
		return false; // ray is parallel

	// find beta coordinate

	float f = 1.0 / a;
	Vec3 s = Vec3(intersecao.ray.origem) - Vec3(vertices[0]);
	float beta = f * pr_esc(s, h);
	if (beta < 0.0 || beta > 1.0)
		return false; // outside triangle

	// find gamma coordinate

	Vec3 q = pr_vet(s, edge1);
	float gamma = f * pr_esc(intersecao.ray.direcao, q);
	if (gamma < 0.0 || beta + gamma > 1.0)
		return false; // outside triangle

	// find the intersection point

	float _t = f * pr_esc(edge2, q);
	if (_t > rayTMin && _t < intersecao.t) // point intersection
	{
		intersecao.t = _t;
		return true;
	}
	else // line intersection
		return false;
}

bool Triangulo::INTERSECTA(const Ray &ray)
{
	// triangle edge vectors

	Vec3 edge1 = vertices[1] - vertices[0];
	Vec3 edge2 = vertices[2] - vertices[0];
	Vec3 h = pr_vet(ray.direcao, edge2);

	// check if ray is parallel

	float a = pr_esc(edge1, h);
	if (a == 0)
		return false; // ray is parallel

	// find beta coordinate

	float f = 1.0 / a;
	Vec3 s = Vec3(ray.origem) - Vec3(vertices[0]);
	float beta = f * pr_esc(s, h);
	if (beta < 0.0 || beta > 1.0)
		return false; // outside triangle

	// find gamma coordinate

	Vec3 q = pr_vet(s, edge1);
	float gamma = f * pr_esc(ray.direcao, q);
	if (gamma < 0.0 || beta + gamma > 1.0)
		return false; // outside triangle

	// find the intersection point

	float _t = f * pr_esc(edge2, q);
	if (_t > rayTMin && _t < ray.tMax) // point intersection
	{
		return true;
	}
	else // line intersection
	{
		return false;
	}
}