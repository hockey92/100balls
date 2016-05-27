#include "GameOverScreen.h"
#include "FileBuf.h"
#include "SimpleButtonDrawable.h"
#include "Context.h"

GameOverScreen::GameOverScreen() {
    font = new Font(new TGAImage(FileBuf::getInstance()->getFontImage()));

    AABB buttonAABB = AABB(-0.90f, -0.15f, 0.90f, 0.15f);
    Button *restartButton = new Button(buttonAABB, Vec2(0, -0.5f), (new SimpleButtonDrawable())->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f)), "gameOverRestartButton");
    restartButton->setText("RESTART");

    Button *menuButton = new Button(buttonAABB, Vec2(0, -0.9f), (new SimpleButtonDrawable())->setColor(Color(0.0f, 0.5f, 0.0f, 1.0f)), "gameOverMenuButton");
    menuButton->setText("MENU");

    addScreenElement(restartButton);
    addScreenElement(menuButton);
}

GameOverScreen::~GameOverScreen() {
    delete font;
}

bool GameOverScreen::init() {

    font->init();

    return ScreenElement::init();
}

void GameOverScreen::draw(float *projMat, Shader *simpleShader, TextureShader *textureShader) {
    ScreenElement::draw(projMat, simpleShader, textureShader);

    setFinalScore(Context::getInstance()->getScoreService()->getTotal());

    font->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
    font->renderText("GAME OVER", textureShader, projMat, 0, 0.9f);

//    char scoreText[40];
//    sprintf(scoreText, "SCORE %d", finalScore);
//    font->renderText(std::string(scoreText), textureShader, projMat, 0, 0.6f);

    font->renderText(finalScore, textureShader, projMat, 0, 0.6f);

}

bool GameOverScreen::doOperation(void *data) {
    return ScreenElement::doOperation(data);
}

void GameOverScreen::setFinalScore(unsigned int finalScore) {
    this->finalScore = finalScore;
}
