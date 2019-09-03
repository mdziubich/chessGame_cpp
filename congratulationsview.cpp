#include "congratulationsview.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include "actionbutton.h"
#include "constants.h"
#include "gameview.h"
#include "utils.h"

extern GameView *game;

CongratulationsView::CongratulationsView(PlayerType winner) {
    // set title
    QGraphicsTextItem *titleItem = Utils::createTextItem("Congratulations!", 50, Constants::defaultTextColor, this);

    double titleXPosition = 600 - titleItem->boundingRect().width()/2;
    double titleYPosition = 100;
    titleItem->setPos(titleXPosition, titleYPosition);

    // set image
    QString imagePath = ":Images/confetti.svg";
    QPixmap image(imagePath);
    QLabel *imageLabel = new QLabel();
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(this);

    imageLabel->setPixmap(image.scaled(200, 200, Qt::KeepAspectRatio));
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);
    pMyProxy->setPos(500, 180);

    // set winner label
    QString winnerName = winner == PlayerType::black ? "Player black" : "Player white";
    QGraphicsTextItem *descriptionItem = Utils::createTextItem(winnerName + " has won!", 25, Constants::defaultTextColor, this);

    double descriptionXPosition = 600 - descriptionItem->boundingRect().width()/2;
    double descriptionYPosition = 400;
    descriptionItem->setPos(descriptionXPosition, descriptionYPosition);

    // add action button
    ActionButton *actionButton = new ActionButton("Quit game");
    double buttonXPosition = 600 - actionButton->boundingRect().width()/2;
    double buttonYPosition = 500;
    actionButton->setPos(buttonXPosition, buttonYPosition);

    connect(actionButton, SIGNAL(buttonPressed()), game, SLOT(quitGame()));
    game->scene->addItem(actionButton);
    game->scene->addItem(this);
}
