#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QString>

class AuthController
{
private:
    int nombreEssais;
    int maxEssais;

    QString hasherMotDePasse(const QString& motDePasse) const;

public:
    AuthController();

    bool connecter(
        const QString& login,
        const QString& motDePasse
        );

    bool estBloque() const;
    int getNombreEssais() const;
};

#endif