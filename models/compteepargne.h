#ifndef COMPTEEPARGNE_H
#define COMPTEEPARGNE_H

#include "comptebancaire.h"

class CompteEpargne : public CompteBancaire
{
private:
    double tauxInteret;

public:
    CompteEpargne(
        const QString& iban,
        double soldeInitial,
        double tauxInteret
        );

    double getTauxInteret() const;

    bool retirer(
        double montant,
        const QString& description = ""
        ) override;

    void appliquerInterets();
};

#endif
