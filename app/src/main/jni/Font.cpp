#include "Font.h"
#include "DrawUtils.h"
#include <set>
#include <queue>

Font::Font(RendererFactory *rendererFactory, ObjectAccessor<File> *fileAccessor)
        : rendererFactory(rendererFactory) {
    for (int i = 0; i < 300; i++) {
        symbolRenderers[i] = NULL;
    }
    image = new TGAImage(fileAccessor->getObject("font.tga"));
    bfs('A', 26, 200);
    bfs('0', 10, 100);
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

        std::pair<int, int> d[] = {std::pair<int, int>(1, 0), std::pair<int, int>(-1, 0),
                                   std::pair<int, int>(0, 1), std::pair<int, int>(0, -1)};

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

        float coefficient = 720.0f;
        float h = (float) (up - down) / coefficient;
        float w = (float) (right - left) / coefficient;

        maxLetterHigh = std::max(maxLetterHigh, h);

        float *vertices = DrawUtils::createCoordinatesForTextureShader(-h, h,
                                                                       -w, w,
                                                                       texDown, texUp,
                                                                       texLeft, texRight);
        symbolRenderers[firstSymbol + k] = rendererFactory->createTextureRenderer(vertices,
                                                                                  "font.tga");
        delete[] vertices;

        initX = right + 2;
    }
}

Font::~Font() {
    if (image) {
        delete image;
    }

    for (int i = 0; i < 300; i++) {
        if (symbolRenderers[i]) {
            delete symbolRenderers[i];
        }
    }
}

bool Font::checkRange(int value, int lower, int upper) {
    return value < lower || value > upper;
}

void Font::renderText(const std::string &text, float x, float y) {
    float distBetweenSymbols = 0.15f;
    int tokensCount = text.size();
    x += distBetweenSymbols * (float) ((tokensCount - 1) / 2)
         + (tokensCount % 2 == 0 ? distBetweenSymbols / 2.0f : 0.0f);
    for (int i = 0; i < tokensCount; i++) {
        char ch = text[(tokensCount - 1) - i];
        if (ch == ' ') {
            x -= distBetweenSymbols;
            continue;
        }
        Renderer *currentRenderer = symbolRenderers[ch];
        currentRenderer->setColor(Color(1, 1, 1, 1));
        currentRenderer->setPosition(x, y);
        currentRenderer->render();
        x -= distBetweenSymbols;
    }
}

void Font::setColor(const Color &color) {
    this->color = color;
}
