#ifndef COMPTECOURANT_H
#define COMPTECOURANT_H

#include "comptebancaire.h"

class CompteCourant : public CompteBancaire
{
private:
    double decouvertAutorise;

public:
    CompteCourant(
        const QString& iban,
        double soldeInitial,
        double decouvertAutorise
        );

    double getDecouvertAutorise() const;

    bool retirer(
        double montant,
        const QString& description = ""
        ) override;
};

#endif