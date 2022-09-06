#include "../headers/graphicarray.h"

graphicArray::graphicArray(QWidget *parent) : QWidget(parent)
{
}

graphicArray::~graphicArray(){
    delete plateauQt;
}


void graphicArray::initPlateauQt(int panelSize, int color){
    this->panelSize = panelSize;
    this->nbPlayer = color;
    //Image de fond
    bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/img/resources/img/red_turn.png"));

    //Score
    scoreLabel2 = new QLabel(this);
    scoreLabel4 = new QLabel(this);
    if(color == 2)
    {
        QString score2 = "2";
        QString score1 = "2";
        QString newScoreLabel2 = "<font color=\"#2173a6\">" + score2 + "</font>" + "|" + "<font color=\"#bf4136\">" + score1 + "</font>";
        scoreLabel2->setText(newScoreLabel2);
        scoreLabel2->setFont(QFont("Commons", 22));
        scoreLabel2->setMinimumWidth(100);
        scoreLabel2->setMaximumWidth(100);
        scoreLabel2->move(55, 690);
    }
    if(color == 4)
    {
        QString score2 = "1";
        QString score1 = "1";
        QString score3 = "1";
        QString score4 = "1";
        QString newScoreLabel2 = "<font color=\"#2173a6\">" + score2 + "</font>" + "|" + "<font color=\"#bf4136\">" + score1 + "</font>";
        QString newScoreLabel4 = "<font color=\"#f2b33d\">" + score4 + "</font>" + "|" + "<font color=\"#027333\">" + score3 + "</font>";
        scoreLabel2->setText(newScoreLabel2);
        scoreLabel2->setFont(QFont("Commons", 22));
        scoreLabel2->setMinimumWidth(100);
        scoreLabel2->setMaximumWidth(100);
        scoreLabel2->move(55, 680);

        scoreLabel4->setText(newScoreLabel4);
        scoreLabel4->setFont(QFont("Commons", 22));
        scoreLabel4->setMinimumWidth(100);
        scoreLabel4->setMaximumWidth(100);
        scoreLabel4->move(55, 705);
    }


    //Bouton quit
    quitButton = new QPushButton(this);
    quitButton->setIcon(QPixmap(":/img/resources/img/stop_icon.png"));
    //change color
    QString Buttonstyle = ("QPushButton {background-color: white; border:none; }");
    quitButton->setStyleSheet(Buttonstyle);
    quitButton->setIconSize(QSize(50,50));
    quitButton->setMinimumSize(50,50);
    quitButton->setMaximumSize(50,50);
    quitButton->move(740,10);

    //Plateau de jeu
    plateauQt = new QTableWidget(this);
    plateauQt->setMinimumSize(500,500);
    plateauQt->setMaximumSize(500,500);

    plateauQt->setColumnCount(panelSize);
    plateauQt->setRowCount(panelSize);
    int iconX,iconY;
    iconX = 500/panelSize;
    iconY = 500/panelSize;
    plateauQt->setIconSize(QSize(iconX-2, iconY-2)); //QSize(53, 53
    plateauQt->setShowGrid(false);
    plateauQt->horizontalHeader()->setVisible(false);
    plateauQt->verticalHeader()->setVisible(false);
    plateauQt->setFrameStyle(QFrame::NoFrame);

    plateauQt->setEditTriggers(QAbstractItemView::NoEditTriggers);
    plateauQt->setSelectionMode(QAbstractItemView::NoSelection);
    plateauQt->setSelectionBehavior(QAbstractItemView::SelectRows);
    plateauQt->horizontalHeader()->setDefaultSectionSize(iconX);
    plateauQt->verticalHeader()->setDefaultSectionSize(iconY);
    QPalette p = plateauQt->palette();
    p.setColor(QPalette::Base, Qt::black);
    plateauQt->setPalette(p);

    //Rempli le plateau de case blanche
    for (int r = 0; r < plateauQt->rowCount(); ++r){
            for (int c = 0; c < plateauQt->columnCount(); ++c){
                plateauQt->setItem(r, c, createItem(3));
            }
    }

    if(color == 2)initTable2();
    if(color == 4)initTable4();
    plateauQt->move(150,150);

    endWindowRed = new QLabel(this);
    endWindowRed->setPixmap(QPixmap(":/img/resources/img/gameOverRed.png"));
    endWindowRed->move(1000,1000);
    endWindowBlue = new QLabel(this);
    endWindowBlue->setPixmap(QPixmap(":/img/resources/img/gameOverBlue.png"));
    endWindowBlue->move(1000,1000);
    endWindow2Equal = new QLabel(this);
    endWindow2Equal->setPixmap(QPixmap(":/img/resources/img/gameOverEqual.png"));
    endWindow2Equal->move(1000,1000);
    endWindowGreen = new QLabel(this);
    endWindowGreen->setPixmap(QPixmap(":/img/resources/img/gameOverGreen.png"));
    endWindowGreen->move(1000,1000);
    endWindowYellow = new QLabel(this);
    endWindowYellow->setPixmap(QPixmap(":/img/resources/img/gameOverYellow.png"));
    endWindowYellow->move(1000,1000);
    endWindow4Equal = new QLabel(this);
    endWindow4Equal->setPixmap(QPixmap(":/img/resources/img/gameOver4Equal.png"));
    endWindow4Equal->move(1000,1000);

    //Bouton quit
    endButton = new QPushButton(this);
    endButton->setIcon(QPixmap(":/img/resources/img/stop_icon.png"));
    //change color
    endButton->setStyleSheet(Buttonstyle);
    endButton->setIconSize(QSize(25,25));
    endButton->setMinimumSize(25,25);
    endButton->setMaximumSize(25,25);
    endButton->move(1000,1000);

     //Detect click on button
    connect(quitButton, SIGNAL(clicked()), this, SLOT(gameStop()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(gameOverShow()));


    //Detect click on cell
    connect(plateauQt, SIGNAL(cellClicked(int,int)), this, SLOT(cellClickedSlot(int, int)));
}

void graphicArray::initTable2(){
    plateauQt->setItem(0, 0, createItem(2));//pion bleu haut gauche
    plateauQt->setItem(0, panelSize-1, createItem(1));//pion rouge haut droit
    plateauQt->setItem(panelSize-1, panelSize-1, createItem(2));//pion bleu bas droit
    plateauQt->setItem(panelSize-1, 0, createItem(1));//pion rouge bas gauche
}

void graphicArray::initTable4(){
    plateauQt->setItem(0, 0, createItem(2));//pion bleu haut gauche
    plateauQt->setItem(0, panelSize-1, createItem(7));//pion vert haut droit
    plateauQt->setItem(panelSize-1, panelSize-1, createItem(1));//pion rouge bas droit
    plateauQt->setItem(panelSize-1, 0, createItem(8));//pion jaune gauche
}

void graphicArray::gameStop(){
    emit gameStopSignal();
}

void graphicArray::gameOverShow(){
    endWindowRed->move(1000,1000);
    endWindowBlue->move(1000,1000);
    endWindow2Equal->move(1000,1000);
    endWindowGreen->move(1000,1000);
    endWindowYellow->move(1000,1000);
    endWindow4Equal->move(1000,1000);
    endButton->move(1000,1000);

}


void graphicArray::cellClickedSlot(int x, int y){
    emit cellClickedSignal(x,y);

}

void graphicArray::changeBG(int style){
    switch (style){
    case 1 :
        bg->setPixmap(QPixmap(":/img/resources/img/blue_turn.png"));
    break;

    case 2 :
        bg->setPixmap(QPixmap(":/img/resources/img/red_turn.png"));
    break;

    case 3 :
        endWindowBlue->move(0,248);
        endButton->move(770,250);
    break;

    case 4 :
        endWindowRed->move(0,248);
        endButton->move(770,250);
    break;

    case 5 :
        endWindow2Equal->move(0,248);
        endButton->move(770,250);
    break;

    case 6 :
        bg->setPixmap(QPixmap(":/img/resources/img/green_turn.png"));
    break;
    case 7 :
        bg->setPixmap(QPixmap(":/img/resources/img/yellow_turn.png"));
    break;

    case 8 :
        endWindowGreen->move(0,248);
        endButton->move(770,250);
    break;

    case 9 :
        endWindowYellow->move(0,248);
        endButton->move(770,250);
    break;

    case 10 :
        endWindow4Equal->move(0,248);
        endButton->move(770,250);
    break;
    }


}

void graphicArray::changeScore(QString score2, QString score4){
       if(nbPlayer == 2) scoreLabel2->setText(score2);
       if(nbPlayer == 4){
           scoreLabel2->setText(score2);
           scoreLabel4->setText(score4);
       }
}


QTableWidgetItem * graphicArray::createItem(int style){

    QTableWidgetItem * item = new QTableWidgetItem;
    switch (style) {
        case 1 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/pion2.png")));
        break;

        case 2 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/pion.png")));
        break;

        case 3 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/pion1.png")));
        break;

        case 4 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/pion_selected.png")));
        break;

        case 5 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/red_selected.png")));
        break;

        case 6 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/blue_selected.png")));
        break;

        case 7 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/green_pion.png")));
        break;

        case 8 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/yellow_pion.png")));
        break;

        case 9 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/green_selected.png")));
        break;

        case 10 :
        item->setIcon(QIcon(QPixmap(":/img/resources/img/yellow_selected.png")));
        break;
    }
    item->setSizeHint(QSize(25, 25));
    item->setTextAlignment(Qt::AlignCenter);
    item->setBackgroundColor(Qt::black);

    return item;

}

void graphicArray::setItemInTable(int x, int y, int style){
    plateauQt->setItem(x,y,createItem(style));
}


QTableWidget & graphicArray::getPanel(){
    return *plateauQt;
}
