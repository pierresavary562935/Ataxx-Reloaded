#include "../headers/options.h"

/**
 * \brief       Constructeur de la classe options
 */
options::options(QWidget * parent):
    QDialog(parent)
{

    setWindowTitle("Ataxx Relaoded - Options");

    this->setMaximumSize(800, 800);
    this->setMinimumSize(800, 800);
    setWindowTitle(tr("Options"));

    //Image de fond
    QLabel * bg = new QLabel(this);
    bg->setPixmap(QPixmap(":/img/resources/img/options_bg.png"));
    bg->setMinimumSize(800,800);
    bg->setMaximumSize(800,800);

    this->volumes = 100;
    this->volumeMusic = 100;
    this->volumeSoundsEffects = 100;
    this->panelSize = 7;
    this->nbPlayer = 2;

    createOptionsWindow();

}

/**
 * \brief       Destructeur de la classe options
 */
options::~options(){}


/**
 * \brief       Initialise la fenêtre des options.
 */
void options::createOptionsWindow(){
    //QHBoxLayout * VolumeOptions = new QHBoxLayout();

    //QLabel "Options :"
    titleLabel = new QLabel(tr("Options :"));
    titleLabel->setFont(QFont("Commons", 22));
    titleLabel->setTextFormat(Qt::PlainText);
    titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
    titleLabel->setAlignment(Qt::AlignLeft);

    //Nombre de joueurs
    nbPlayerLabel = new QLabel(tr("Choose your rules :"));
    nbPlayerLabel->setFont(QFont("Commons", 14));
    oneplayer = new QRadioButton();
    oneplayer->setText("2 players");
    oneplayer->setFont(QFont("Commons", 12));
    oneplayer->setChecked(true);
    twoplayer = new QRadioButton();
    twoplayer->setText("4 players");
    twoplayer->setFont(QFont("Commons", 12));
    playerModeLayout = new QVBoxLayout();
    playerModeLayout->addWidget(oneplayer);
    playerModeLayout->addWidget(twoplayer);

    nbPlayerLayout = new QHBoxLayout();
    nbPlayerLayout->addWidget(nbPlayerLabel);
    nbPlayerLayout->addLayout(playerModeLayout);

    //Volume
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setFixedWidth(100);
    volumeSlider->setValue(volumes);
    volumeLabel = new QLabel(tr("Volumes :"));
    volumeLabel->setFont(QFont("Commons", 14));
    volumeDisplayer = new QLabel(this);
    volumeDisplayer->setFont(QFont("Commons", 12));
    volumeDisplayer->setTextFormat(Qt::PlainText);
    volumeDisplayer->setTextInteractionFlags(Qt::NoTextInteraction);
    volumeDisplayer->setAlignment(Qt::AlignCenter);
    volumeDisplayer->setNum(volumes);
    volumeLayout = new QHBoxLayout();
    volumeLayout->addWidget(volumeLabel);
    volumeLayout->addWidget(volumeSlider);
    volumeLayout->addWidget(volumeDisplayer);

    //Volume Music
    musicSlider = new QSlider(Qt::Horizontal, this);
    musicSlider->setRange(0, 100);
    musicSlider->setFixedWidth(100);
    musicSlider->setValue(volumeMusic);
    musicLabel = new QLabel(tr("Volume of the (great!) music :"));
    musicLabel->setFont(QFont("Commons", 10));
    musicDisplayer = new QLabel(this);
    musicDisplayer->setFont(QFont("Commons", 12));
    musicDisplayer->setTextFormat(Qt::PlainText);
    musicDisplayer->setTextInteractionFlags(Qt::NoTextInteraction);
    musicDisplayer->setAlignment(Qt::AlignCenter);
    musicDisplayer->setNum(volumeMusic);
    musicLayout = new QHBoxLayout();
    musicLayout->addWidget(musicLabel);
    musicLayout->addWidget(musicSlider);
    musicLayout->addWidget(musicDisplayer);

    //Volume sound effect
    soundsEffectsSlider = new QSlider(Qt::Horizontal, this);
    soundsEffectsSlider->setRange(0, 100);
    soundsEffectsSlider->setFixedWidth(100);
    soundsEffectsSlider->setValue(volumeSoundsEffects);
    soundsEffectsLabel = new QLabel(tr("Volume of the sound effects :"));
    soundsEffectsLabel->setFont(QFont("Commons", 10));
    soundsEffectsDisplayer = new QLabel(this);
    soundsEffectsDisplayer->setFont(QFont("Commons", 12));
    soundsEffectsDisplayer->setTextFormat(Qt::PlainText);
    soundsEffectsDisplayer->setTextInteractionFlags(Qt::NoTextInteraction);
    soundsEffectsDisplayer->setAlignment(Qt::AlignCenter);
    soundsEffectsDisplayer->setNum(volumeSoundsEffects);
    soundsEffectsLayout = new QHBoxLayout();
    soundsEffectsLayout->addWidget(soundsEffectsLabel);
    soundsEffectsLayout->addWidget(soundsEffectsSlider);
    soundsEffectsLayout->addWidget(soundsEffectsDisplayer);

    //Size panel
    panelSizeLabel = new QLabel(tr("Choose the size of the board :"));
    panelSizeLabel->setFont(QFont("Commons", 14));

    panelSizeSpinBox = new QSpinBox;
    panelSizeSpinBox->setFont(QFont("Commons", 14));
    panelSizeSpinBox->setRange(5, 12);
    panelSizeSpinBox->setSingleStep(1);
    panelSizeSpinBox->setValue(panelSize);
    panelSizeLayout = new QHBoxLayout();
    panelSizeLayout->addWidget(panelSizeLabel);
    panelSizeLayout->addWidget(panelSizeSpinBox);

    //Bouton "ok"
    buttonOk = new QPushButton(this);
    buttonOk->setIcon(QPixmap(":/img/resources/img/button_play.png"));
    //change color
    QString Buttonstyle = ("QPushButton {background-color: #BF4316; border:none; }");
    buttonOk->setStyleSheet(Buttonstyle);
    buttonOk->setIconSize(QSize(171,71));
    buttonOk->setMinimumSize(171,71);
    buttonOk->setMaximumSize(171,71);
    buttonOk->move(590,690);

    //Construction layout central
    QVBoxLayout * OptionsVLayout = new QVBoxLayout();
    OptionsVLayout->addWidget(titleLabel);
    OptionsVLayout->addLayout(nbPlayerLayout);
    OptionsVLayout->addLayout(volumeLayout);
    OptionsVLayout->addLayout(musicLayout);
    OptionsVLayout->addLayout(soundsEffectsLayout);
    OptionsVLayout->addLayout(panelSizeLayout);

    OptionsVLayout->setContentsMargins(200,200,200,200);
    this->setLayout(OptionsVLayout);

    setModal(true);

    //connect Volumes
    connect(volumeSlider, SIGNAL(sliderPressed()), this, SLOT(volumesSliderPressed()));
    connect(musicSlider, SIGNAL(sliderPressed()), this, SLOT(musicSliderPressed()));
    connect(soundsEffectsSlider, SIGNAL(sliderPressed()), this, SLOT(soundsEffectsSliderPressed()));

    connect(volumeSlider, SIGNAL(sliderReleased()), this, SLOT(volumesSliderReleased()));
    connect(musicSlider, SIGNAL(sliderReleased()), this, SLOT(musicSliderReleased()));
    connect(soundsEffectsSlider, SIGNAL(sliderReleased()), this, SLOT(soundsEffectsSliderReleased()));

    //connect nbPlayer
    connect(oneplayer, SIGNAL(clicked()), this, SLOT(updateNbPlayer1()));
    connect(twoplayer, SIGNAL(clicked()), this, SLOT(updateNbPlayer2()));
    //connect panelSize
    connect(panelSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updatePanelSize(int)));

    //connect buttonOk
    //connect(buttonOk,&QPushButton::clicked, this, &Ataxx_options::close);
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(closeOptions()));

    std::cout << std::endl;
    std::cout << "PREDEFINED OPTIONS :" << std::endl;
    std::cout << "nbPlayer : "<< this->nbPlayer << std::endl;
    std::cout << "volumes : " << this->volumeMusic << std::endl;
    std::cout << "volumeMusic : " << this->volumeMusic << std::endl;
    std::cout << "VolumeSoundEffect : " << this->volumeSoundsEffects << std::endl;
    std::cout << "panelSize : " << this->panelSize << std::endl;

}

//CONNECT SLOTS

void options::volumesSliderPressed(){
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(updateVolumes(int)));
}

void options::musicSliderPressed(){
    connect(musicSlider, SIGNAL(valueChanged(int)), this, SLOT(updateVolumeMusic(int)));
}
void options::soundsEffectsSliderPressed(){
    connect(soundsEffectsSlider, SIGNAL(valueChanged(int)), this, SLOT(updateVolumeSoundsEffects(int)));
}

void options::volumesSliderReleased(){
    disconnect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(updateVolumes(int)));
}
void options::musicSliderReleased(){
    disconnect(musicSlider, SIGNAL(valueChanged(int)), this, SLOT(updateVolumeMusic(int)));
}
void options::soundsEffectsSliderReleased(){
    disconnect(soundsEffectsSlider, SIGNAL(valueChanged(int)), this, SLOT(updateVolumeSoundsEffects(int)));
}

/**
 * \brief       Slots récupérant les options choisis par l'utilisateur
 */

void options::updateVolumes(int value) {
   std::cout << "Volumes :" << value << std::endl;
   volumeDisplayer->setNum(value);

   musicDisplayer->setNum((volumeMusic + value)/2);
   soundsEffectsDisplayer->setNum((volumeSoundsEffects + value)/2);

   musicSlider->setValue((volumeMusic + value)/2);
   soundsEffectsSlider->setValue((volumeSoundsEffects + value)/2);

   volumeMusic = (volumeMusic + value)/2;
   volumeSoundsEffects = (volumeSoundsEffects + value)/2;
   volumes = value;
}

void options::updateVolumeSoundsEffects(int value) {
   std::cout << "Volume sounds effects :" << value << std::endl;
   soundsEffectsDisplayer->setNum(value);

   volumes = (value + volumeMusic)/2;
   volumeDisplayer->setNum(volumes);
   volumeSlider->setValue(volumes);
   volumeSoundsEffects = value;
}
void options::updateVolumeMusic(int value) {
   std::cout << "Volume music :" << value << std::endl;
   musicDisplayer->setNum(value);
   volumes = (value + volumeSoundsEffects)/2;
   volumeDisplayer->setNum(volumes);
   volumeSlider->setValue(volumes);
   volumeMusic = value;
}

void options::updateNbPlayer1() {
   std::cout << "radioButton playerVSbot" << std::endl;
   nbPlayer = 2;
}
void options::updateNbPlayer2() {
   std::cout << "radioButton playerVSplayer" << std::endl;
   nbPlayer = 4;
}

void options::updatePanelSize(int value) {
   std::cout << "panelSize :" << value << std::endl;
   panelSize = value;
}

void options::closeOptions() {

    emit optionsHaveBeenClosed();
}
