#ifndef COMPTEPROFESSIONNEL_H
#define COMPTEPROFESSIONNEL_H

#include "comptebancaire.h"

class CompteProfessionnel : public CompteBancaire
{
private:
    QString nomEntreprise;
    double plafondRetrait;
    double plafondVirement;

public:
    CompteProfessionnel(
        const QString& iban,
        double soldeInitial,
        const QString& nomEntreprise,
        double plafondRetrait,
        double plafondVirement
        );

    QString getNomEntreprise() const;
    double getPlafondRetrait() const;
    double getPlafondVirement() const;

    bool retirer(
        double montant,
        const QString& description = ""
        ) override;

    bool virer(
        CompteBancaire& destination,
        double montant,
        const QString& description = ""
        ) override;
};

#endif