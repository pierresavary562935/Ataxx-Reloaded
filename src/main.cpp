#include "headers/mainwindow.h"
#include "headers/console.h"

#include <QApplication>
#include <QPushButton>
#include <iostream>


int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        console c;

        QMap<QString, QString> arguments;

        arguments = readArguments(argc, argv, arguments);

        if(arguments.value("mode") == "console"){
            cout << "CONSOLE MODE" << endl << endl;
            //w.setMode(1);
            //w.changeWindowGame();
            c.launch();
        }else if(arguments.value("mode") == "graphic"){
            cout << "GRAPHIC MODE" << endl << endl;
            w.setMode(2);
            w.show();
            }else if(arguments.value("mode") == "mixed"){
            cout << "MIXED MODE" << endl<< endl;
            w.setMode(3);
        }else{
            w.setMode(2);
            w.show();
        }



        return a.exec();

}
