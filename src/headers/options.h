/**
 * \file          options.h
 * \author      Pierre Savary
 * \version     1.0
 * \date        3 mai 2019
 * \brief       Génère la fenêtre d'options en mode graphique
 *
 * \details    Cette classe s'occupe de générer les options dans une fenêtre
 *
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <iostream>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QRadioButton>

class options : public QDialog
{
    Q_OBJECT

public:

    explicit options(QWidget *parent = nullptr);
    ~options();

    void createOptionsWindow();

    int getNbPlayer(){return nbPlayer;}
    int getVolumes(){return volumes;}
    int getVolumeSoundsEffects(){return volumeSoundsEffects;}
    int getVolumeMusic(){return volumeMusic;}
    int getPanelSize(){return panelSize;}

public slots :

    void volumesSliderPressed();
    void musicSliderPressed();
    void soundsEffectsSliderPressed();

    void volumesSliderReleased();
    void musicSliderReleased();
    void soundsEffectsSliderReleased();


    void updateVolumes(int value);
    void updateVolumeSoundsEffects(int value);
    void updateVolumeMusic(int value);
    void updateNbPlayer1();
    void updateNbPlayer2();
    void updatePanelSize(int value);
    void closeOptions();

signals:
    void optionsHaveBeenClosed();

private:
     QLabel * titleLabel;

     QHBoxLayout * nbPlayerLayout;
     QVBoxLayout * playerModeLayout;
     QLabel * nbPlayerLabel;
     QRadioButton * oneplayer;
     QRadioButton * twoplayer;

     QHBoxLayout * volumeLayout;
     QSlider * volumeSlider;
     QLabel * volumeLabel;
     QLabel * volumeDisplayer;

     QHBoxLayout * musicLayout;
     QSlider * musicSlider;
     QLabel * musicLabel;
     QLabel * musicDisplayer;

     QHBoxLayout * soundsEffectsLayout;
     QSlider * soundsEffectsSlider;
     QLabel * soundsEffectsLabel;
     QLabel * soundsEffectsDisplayer;

     QHBoxLayout * panelSizeLayout;
     QSpinBox * panelSizeSpinBox;
     QLabel * panelSizeLabel;

     QPushButton * buttonOk;

     int volumes;
     int volumeMusic;
     int volumeSoundsEffects;
     int nbPlayer;
     int panelSize;

};

#endif // OPTIONS_H
