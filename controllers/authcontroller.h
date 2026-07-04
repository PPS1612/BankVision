#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QString>

#include "../models/utilisateur.h"

class AuthController
{
private:
    int nombreEssais;
    int maxEssais;

    QString hasherMotDePasse(const QString& motDePasse) const;

public:
    AuthController();

    bool verifierMotDePasse(
        const QString& motDePasseSaisi,
        const Utilisateur& utilisateur
        );

    bool connecter(
        const QString& login,
        const QString& motDePasse,
        const Utilisateur& utilisateur
        );

    bool estBloque() const;
    int getNombreEssais() const;
};

#endif
