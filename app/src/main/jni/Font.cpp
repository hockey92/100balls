#include "Font.h"
#include "DrawUtils.h"
#include <set>
#include <queue>
#include <vecmath.h>

Font::Font(TGAImage *image) : image(image) {
    for (int i = 0; i < 300; i++) {
        fontBuff[i] = std::pair<VertexBuff *, float>(NULL, 0);
    }
}

void Font::bfs(char firstSymbol, size_t count, int yPosition) {

    int initX = 0;
    int initY = yPosition;
    int right, left, up, down;

    for (int k = 0; k < count; k++) {
        std::set<std::pair<int, int> > used;
        std::queue<std::pair<int, int> > que;

        while (image->getPixel(initY, initX).alpha == 0) {
            initX++;
        }

        used.insert(std::pair<int, int>(initX, initY));
        que.push(std::pair<int, int>(initX, initY));

        std::pair<int, int> d[] = {std::pair<int, int>(1, 0),
                                   std::pair<int, int>(-1, 0),
                                   std::pair<int, int>(0, 1),
                                   std::pair<int, int>(0, -1)};

        right = left = initX;
        up = down = initY;

        while (!que.empty()) {
            std::pair<int, int> front = que.front();
            que.pop();

            right = front.first > right ? front.first : right;
            left = front.first < left ? front.first : left;
            up = front.second > up ? front.second : up;
            down = front.second < down ? front.second : down;

            for (int i = 0; i < 4; i++) {
                std::pair<int, int> newCoords = std::pair<int, int>(front.first + d[i].first,
                                                                    front.second + d[i].second);
                if (checkRange(newCoords.first, 0, image->getW() - 1) ||
                    checkRange(newCoords.second, 0, image->getH() - 1)) {
                    continue;
                }

                if (used.find(newCoords) == used.end() &&
                    image->getPixel(newCoords.second, newCoords.first).alpha != 0) {
                    que.push(newCoords);
                    used.insert(newCoords);
                }
            }
        }

        float texUp = ((float) (up + 5)) / ((float) image->getH());
        float texDown = ((float) (down - 5)) / ((float) image->getH());
        float texLeft = ((float) (left - 5)) / ((float) image->getW());
        float texRight = ((float) (right + 5)) / ((float) image->getW());

        float coeff = 720.0f;
        float h = (float) (up - down) / coeff;
        float w = (float) (right - left) / coeff;

        maxLetterHigh = std::max(maxLetterHigh, h);

        fontBuff[firstSymbol + k] = std::pair<VertexBuff *, float>(new VertexBuff(
                DrawUtils::createCoordsForTextureShader(-h, h, -w, w, texDown, texUp, texLeft,
                                                        texRight), 24 * sizeof(float)), h);

        initX = right + 2;
    }
}

Font::~Font() {
    if (image) {
        delete image;
    }

    for (int i = 0; i < 300; i++) {
        if (fontBuff[i].first) {
            delete fontBuff[i].first;
        }
    }

    if (texture) {
        delete texture;
    }
}

bool Font::checkRange(int value, int lower, int upper) {
    return value < lower || value > upper;
}

void Font::init() {

    texture = new Texture(*image);

    maxLetterHigh = 0;
//    bfs('a', 26, 140);
    bfs('A', 26, 200);
    bfs('0', 10, 100);
}

void Font::renderInteger(unsigned int num, TextureShader *shader, float *mvp, float x, float y) {
    char intStr[20];
    sprintf(intStr, "%u", num);
    renderText(std::string(intStr), shader, mvp, x, y);
}

void Font::renderInteger(unsigned int num, TextureShader *shader, float *mvp, const Vec2 &pos) {
    renderInteger(num, shader, mvp, pos.x(), pos.y());
}

void Font::renderText(const std::string &text, TextureShader *shader, float *mvp, float x,
                      float y) {
    float distBetweenSymbols = 0.15f;
    ndk_helper::Mat4 mvpMat4 = ndk_helper::Mat4(mvp);
    int tokensCount = text.size();
    float dx = distBetweenSymbols * (float) ((tokensCount - 1) / 2) +
               (tokensCount % 2 == 0 ? distBetweenSymbols / 2.0f : 0.0f);
    mvpMat4 *= ndk_helper::Mat4::Translation(x + dx, y, 0.0f);
    for (int i = 0; i < tokensCount; i++) {
        char ch = text[(tokensCount - 1) - i];
        if (ch == ' ') {
//            float dY = (maxLetterHigh - fontBuff[ch].second) / 2.0f;
            mvpMat4 *= ndk_helper::Mat4::Translation(-distBetweenSymbols, 0.0f, 0.0f);
            continue;
        }
        shader->beginRender(fontBuff[ch].first, 4, 6);
        shader->setTexture(texture);
        shader->setColor(color);
        shader->setMVP(mvpMat4.Ptr());
        shader->render();
        shader->endRender();

        mvpMat4 *= ndk_helper::Mat4::Translation(-distBetweenSymbols, 0.0f, 0.0f);
    }
}

void Font::renderText(const std::string &text, TextureShader *shader, float *mvp, const Vec2 &pos) {
    renderText(text, shader, mvp, pos.x(), pos.y());
}

void Font::setColor(const Color &color) {
    this->color = color;
}
