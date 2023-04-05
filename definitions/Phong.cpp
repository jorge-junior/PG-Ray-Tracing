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
    viewDir.normalizar();

    // Vetor normalizado da posição do objeto até a posição da luz
    Vec3 lightDir = cena.luz.posicao - p_intersec;
    p_intersec.print();
    lightDir.normalizar();

    // Vetor normal do objeto
    Vec3 normal = p_intersec - obj.centro;
    normal.normalizar();

    // Reflexão da luz no objeto
    Vec3 reflectDir = lightDir - (normal * pr_esc(lightDir, normal) * 2);
    reflectDir.print();
    reflectDir.normalizar();

    // Intensidade da luz ambiente
    Cor ambientColor = cena.cor * ka;

    // Intensidade da luz difusa
    float diffuseFactor = pr_esc(lightDir, normal);
    Cor difTempColor = pr_vet(obj.cor, cena.luz.cor);
    Cor diffuseColor = difTempColor * kd * max(diffuseFactor, 0.0f);
    cout << "d=" << diffuseColor.r << '/' << diffuseColor.g << '/' << diffuseColor.b << endl;

    // Intensidade da luz especular
    float specularFactor = pow(pr_esc(reflectDir, viewDir), shininess);
    cout << "sf=" << specularFactor << endl;
    Cor specularColor = cena.luz.cor * ks * specularFactor;
    cout << "s=" << specularColor.r << '/' << specularColor.g << '/' << specularColor.b << endl;

    // Intensidade total da luz
    Cor I = ambientColor + diffuseColor + specularColor;
    cout << "I=" << I.r << '/' << I.g << '/' << I.b << endl;
    I.clamp(0, 255);

    return I;
}