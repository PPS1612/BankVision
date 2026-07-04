#include "authcontroller.h"

#include <QCryptographicHash>

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

bool AuthController::verifierMotDePasse(
    const QString& motDePasseSaisi,
    const Utilisateur& utilisateur
    )
{
    QString hashSaisi = hasherMotDePasse(motDePasseSaisi);

    return hashSaisi == utilisateur.getMotDePasseHash();
}

bool AuthController::connecter(
    const QString& login,
    const QString& motDePasse,
    const Utilisateur& utilisateur
    )
{
    if (estBloque())
        return false;

    if (!utilisateur.estActif())
        return false;

    if (login != utilisateur.getLogin())
    {
        nombreEssais++;
        return false;
    }

    if (!verifierMotDePasse(motDePasse, utilisateur))
    {
        nombreEssais++;
        return false;
    }

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