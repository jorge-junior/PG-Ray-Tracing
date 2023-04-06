#include <iostream>
#include <vector>
#include "lodepng.cpp"

#include "definitions/Phong.cpp"

using namespace std;

Cena cena = Cena(Cor(100, 100, 100), Light(Vec3(40, 400, 100), Cor(255, 255, 255)));

float ka = 0.8f;
float kd = 0.5f;
float ks = 0.0f;
float eta = 1;

Vec3 camPos = Vec3(0, 0, 0);
Vec3 camDir = Vec3(1, 0, 0);

Vec3 vUp = Vec3(0, 0, 1);
float camToS = 100.0f;

int pixelsX = 1920;
int pixelsY = 1080;
int Hy = pixelsY / 2;
int Hx = pixelsX / 2;

Esfera esf = Esfera(Vec3(1000, 0, 0), 900, Cor(0, 255, 0));

Cor rayCasting(const Vec3 &camPos, const Vec3 &camDir, const Vec3 &vUp, float camToS, int hx, int hy, int telaPx, int telaPy, int py, int px, Esfera e)
{
    // Calcula dimensões do pixel
    int alturapixel = hy * 2 / telaPy;
    int largurapixel = hx * 2 / telaPx;

    // Encontra o centro da tela
    Vec3 centroTela = camPos + (camDir * camToS);

    // Calcula os vetores de movimentação
    Vec3 vetorDireita = -Vec3(0, 1, 0) * largurapixel;
    Vec3 vetorBaixo = -Vec3(0, 0, 1) * alturapixel;

    // Encontra o centro do pixel superior esquerdo (0, 0)
    Vec3 cantoSupEsq = centroTela + (Vec3(0, 1, 0) * hx) - (Vec3(0, 0, -1) * hy);
    Vec3 pixelSupEsq = cantoSupEsq + 0.5 * vetorDireita + 0.5 * vetorBaixo;

    // Encontra o pixel (px, py) na tela
    const Vec3 pixelAtual = pixelSupEsq + py * vetorBaixo + px * vetorDireita;

    Ray raioPixelAtual = Ray(camPos, pixelAtual);
    Intersecao intersec = Intersecao(raioPixelAtual);

    bool intersecao = e.intersecta(intersec);
    // cout << '-' << intersecao << endl;

    if (intersecao)
    {
        Vec3 ponto_intersec = intersec.posicao();
        return Phong(cena, e, intersec.ray.origem, ponto_intersec, ka, kd, ks, eta);
    }
    return cena.cor;
}

int main()
{
    // Create a vector of RGBA pixels
    vector<unsigned char> image(pixelsX * pixelsY * 4);

    for (int y = 0; y < pixelsY; y++)
    {
        for (int x = 0; x < pixelsX; x++)
        {
            int index = (y * pixelsX + x) * 4;
            // cout << y << ',' << x;
            Cor corPixel = rayCasting(camPos, camDir, vUp, camToS, Hx, Hy, pixelsX, pixelsY, y, x, esf);
            image[index + 0] = corPixel.r; // R channel
            image[index + 1] = corPixel.g; // G channel
            image[index + 2] = corPixel.b; // B channel
            image[index + 3] = 255;        // Alpha channel
        }
    }
    cout << image[0] << endl;

    // Save the image as a PNG file
    unsigned error = lodepng::encode("image.png", image, pixelsX, pixelsY);
    if (error)
    {
        cout << "PNG encoder error: " << lodepng_error_text(error) << endl;
        return 1;
    }

    cout << "Image saved to 'image.png'" << endl;
    return 0;
}
