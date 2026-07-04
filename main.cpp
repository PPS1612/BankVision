#include <QCoreApplication>
#include <QDebug>
#include <QCryptographicHash>

#include "models/utilisateur.h"
#include "controllers/authcontroller.h"

QString genererHash(const QString& motDePasse)
{
    QByteArray hash = QCryptographicHash::hash(
        motDePasse.toUtf8(),
        QCryptographicHash::Sha256
        );

    return hash.toHex();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString hashCorrect = genererHash("admin123");

    Utilisateur utilisateur(
        1,
        "admin",
        hashCorrect,
        "Administrateur BankVision",
        RoleUtilisateur::ADMIN,
        StatutUtilisateur::ACTIF
        );

    AuthController authController;

    qDebug() << "Test mauvais mot de passe :"
             << authController.connecter("admin", "mauvais", utilisateur);

    qDebug() << "Nombre essais :"
             << authController.getNombreEssais();

    qDebug() << "Test mauvais login :"
             << authController.connecter("user", "admin123", utilisateur);

    qDebug() << "Nombre essais :"
             << authController.getNombreEssais();

    qDebug() << "Test bon login + bon mot de passe :"
             << authController.connecter("admin", "admin123", utilisateur);

    qDebug() << "Nombre essais :"
             << authController.getNombreEssais();

    return 0;
}