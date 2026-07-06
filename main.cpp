#include <QApplication>
#include <QFile>
#include <QIODevice>

#include "data/datamanager.h"
#include "views/FenetreConnexion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialisation de la base de données
    DataManager &dataManager = DataManager::getInstance();

    if (!dataManager.initialiser("banque.db"))
    {
        return -1;
    }

    // Chargement du style global
    QFile styleFile(":/style.qss");

    if (styleFile.open(QIODevice::ReadOnly))
    {
        QString style = styleFile.readAll();
        app.setStyleSheet(style);
        styleFile.close();
    }

    // Fenêtre principale
    FenetreConnexion fenetre;
    fenetre.show();

    int resultat = app.exec();

    dataManager.fermer();

    return resultat;
}