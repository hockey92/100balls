#include "Font.h"
#include "GameCoords.h"
#include "Tokenizer.h"
#include <set>
#include <queue>
#include <vecmath.h>

Font::Font(TGAImage *image) : image(image) {
    for (int i = 0; i < 300; i++) {
        fontBuf[i] = NULL;
    }
}

void Font::bfs() {

    int initX = 0;
    int initY = 80;
    int right, left, up, down;

    for (int k = 0; k < 26; k++) {
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

        float texUp = ((float) (up + 2)) / ((float) image->getH());
        float texDown = ((float) (down - 2)) / ((float) image->getH());
        float texLeft = ((float) (left - 2)) / ((float) image->getW());
        float texRight = ((float) (right + 2)) / ((float) image->getW());

        float coeff = 300.0f;
        float h = (float) (up - down) / coeff;
        float w = (float) (right - left) / coeff;

        fontBuf['A' + k] = new VertexBuf(
                GameCoordsData::createCoordsForShader(-h, h, -w, w, texDown, texUp, texLeft,
                                                      texRight), 24 * sizeof(float));

        initX = right + 2;
    }
}

Font::~Font() {
    if (image) {
        delete image;
    }

    for (int i = 0; i < 300; i++) {
        delete fontBuf[i];
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

    bfs();
}

void Font::renderInteger(unsigned int num, TextureShader *shader, float *mvp, float x, float y) {
    float distBetweenSymbols = 0.15f;
    ndk_helper::Mat4 mvpMat4 = ndk_helper::Mat4(mvp);
    Tokenizer tokenizer(num);
    int tokensCount = tokenizer.getTokensCount();
    float dx = distBetweenSymbols * (float) ((tokensCount - 1) / 2) +
               (tokensCount % 2 == 0 ? distBetweenSymbols / 2.0f : 0.0f);
    mvpMat4 *= ndk_helper::Mat4::Translation(x + dx, y, 0.0f);
    while (tokenizer.hasNext()) {
        shader->beginRender(fontBuf[tokenizer.nextToken() + '0'], 4, 6);
        shader->setTexture(texture);
        shader->setMVP(mvpMat4.Ptr());
        shader->render();
        shader->endRender();

        mvpMat4 *= ndk_helper::Mat4::Translation(-distBetweenSymbols, 0.0f, 0.0f);
    }
}

void Font::renderInteger(unsigned int num, TextureShader *shader, float *mvp, const Vec2& pos) {
    renderInteger(num, shader, mvp, pos.x(), pos.y());
}

void Font::renderText(const std::string& text, TextureShader *shader, float *mvp, float x, float y) {
    float distBetweenSymbols = 0.35f;
    ndk_helper::Mat4 mvpMat4 = ndk_helper::Mat4(mvp);
    int tokensCount = text.size();
    float dx = distBetweenSymbols * (float) ((tokensCount - 1) / 2) +
               (tokensCount % 2 == 0 ? distBetweenSymbols / 2.0f : 0.0f);
    mvpMat4 *= ndk_helper::Mat4::Translation(x + dx, y, 0.0f);
    for (int i = 0; i < tokensCount; i++) {
        char ch = text[(tokensCount - 1) - i];
        if (ch == ' ') {
            mvpMat4 *= ndk_helper::Mat4::Translation(-distBetweenSymbols, 0.0f, 0.0f);
            continue;
        }
        shader->beginRender(fontBuf[ch], 4, 6);
        shader->setTexture(texture);
        shader->setMVP(mvpMat4.Ptr());
        shader->render();
        shader->endRender();

        mvpMat4 *= ndk_helper::Mat4::Translation(-distBetweenSymbols, 0.0f, 0.0f);
    }
}

void Font::renderText(const std::string& text, TextureShader *shader, float *mvp, const Vec2 &pos) {
    renderText(text, shader, mvp, pos.x(), pos.y());
}
