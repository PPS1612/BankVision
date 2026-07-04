#include "authcontroller.h"

#include <QCryptographicHash>
#include <QDebug>

#include "../data/datamanager.h"
#include "../models/utilisateur.h"

AuthController::AuthController()
    : nombreEssais(0),
    maxEssais(3)
{
}

QString AuthController::hasherMotDePasse(const QString& motDePasse) const
{
    QByteArray hash = QCryptographicHash::hash(
        motDePasse.toUtf8(),
        QCryptographicHash::Sha256
        );

    return hash.toHex();
}

bool AuthController::connecter(
    const QString& login,
    const QString& motDePasse
    )
{
    if (estBloque())
    {
        qDebug() << "Compte temporairement bloqué.";
        return false;
    }

    DataManager& dataManager = DataManager::getInstance();

    Utilisateur* utilisateur =
        dataManager.rechercherUtilisateurParLogin(login);

    if (utilisateur == nullptr)
    {
        nombreEssais++;
        qDebug() << "Utilisateur introuvable.";
        return false;
    }

    if (!utilisateur->estActif())
    {
        delete utilisateur;
        qDebug() << "Utilisateur bloqué.";
        return false;
    }

    QString hashSaisi = hasherMotDePasse(motDePasse);

    if (hashSaisi != utilisateur->getMotDePasseHash())
    {
        nombreEssais++;
        delete utilisateur;
        qDebug() << "Mot de passe incorrect.";
        return false;
    }

    qDebug() << "Connexion réussie pour :" << utilisateur->getLogin();

    delete utilisateur;
    nombreEssais = 0;

    return true;
}

bool AuthController::estBloque() const
{
    return nombreEssais >= maxEssais;
}

int AuthController::getNombreEssais() const
{
    return nombreEssais;
}