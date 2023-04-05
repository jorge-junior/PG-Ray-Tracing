#include <iostream>

#include "Cor.hpp"
#include "Intersecoes.hpp"
#include "Normal.hpp"
#include "Ray.hpp"
#include "Vetor.hpp"
#include <cmath>

using namespace std;

// Struct para um ponto de luz
struct Light {
    Vec3 posicao;
    Cor cor;
};

struct Cena
{
    Cor cor;
    Light luz;
};

// Função do modelo de iluminação de Phong
Cor Phong(Cena cena, Esfera obj, Vec3 cameraposicao, Ponto p_intersec, float ka, float kd, float ks, float shininess) {
    // Vetor normalizado do ponto do objeto até a posição da câmera
    Vec3 viewDir = cameraposicao - p_intersec;
    viewDir.normalizar();

    // Vetor normalizado da posição do objeto até a posição da luz
    Vec3 lightDir = cena.luz.posicao - p_intersec;
    lightDir.normalizar();

    // Vetor normal do objeto
    Vec3 normal = p_intersec - obj.centro;
    normal.normalizar();

    // Reflexão da luz no objeto
    Vec3 reflectDir = lightDir - (normal * pr_esc(lightDir, normal) * 2);
    reflectDir.normalizar();

    // Intensidade da luz ambiente
    Cor ambientColor = cena.cor * ka;

    // Intensidade da luz difusa
    float diffuseFactor = pr_esc(lightDir, normal);
    Cor diffuseColor = (obj.cor + cena.luz.cor) * kd * max(diffuseFactor, 0.0f);

    // Intensidade da luz especular
    float specularFactor = pow(max(pr_esc(reflectDir, viewDir), 0.0f), shininess);
    Cor specularColor = cena.luz.cor * ks * specularFactor;

    // Intensidade total da luz
    Cor I = ambientColor + diffuseColor + specularColor;

    return I;
}