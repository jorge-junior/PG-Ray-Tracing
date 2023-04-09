#include <iostream>

#include "Intersecoes.cpp"
#include <cmath>

using namespace std;

// Struct para um ponto de luz
struct Light
{
    Vec3 posicao;
    Cor cor;
    Light(Vec3 pos, Cor c) : posicao(pos), cor(c){};
};

struct Cena
{
    Cor cor;
    Light luz;
    Cena(Cor c, Light l) : cor(c), luz(l){};
};

// Função do modelo de iluminação de Phong
Cor Phong(Cena cena, Esfera obj, Vec3 cameraposicao, Vec3 p_intersec, float ka, float kd, float ks, float shininess)
{
    // Vetor normalizado do ponto do objeto até a posição da câmera
    Vec3 viewDir = cameraposicao - p_intersec;
    viewDir = viewDir.normalizar();

    // Vetor normalizado que chega da luz
    Vec3 lightDir = cena.luz.posicao - p_intersec;
    lightDir = lightDir.normalizar();

    // Vetor normal do objeto
    Vec3 normal = p_intersec - obj.centro;
    normal = normal.normalizar();

    // Reflexão da luz no objeto
    Vec3 reflectDir = -lightDir - (normal * pr_esc(-lightDir, normal)) * 2;
    reflectDir = reflectDir.normalizar();

    // Intensidade da luz ambiente
    Cor ambientColor = cena.cor * ka;
    ambientColor.clamp(0, 255);

    // Intensidade da luz difusa
    float diffuseFactor = pr_esc(lightDir, normal);
    Cor diffTempColor = pr_hd(cena.luz.cor, obj.cor);
    diffTempColor.clamp(0, 255);
    Cor diffuseColor = diffTempColor * kd * max(diffuseFactor, 0.0f);
    diffuseColor.clamp(0, 255);

    // Intensidade da luz especular
    float specularFactor = pow(pr_esc(reflectDir, viewDir), shininess);
    Cor specularColor = cena.luz.cor * ks * specularFactor;
    specularColor.clamp(0, 255);

    // Intensidade total da luz
    Cor I = ambientColor + diffuseColor + specularColor;
    I.clamp(0, 255);

    return I;
}