#include "comptecontroller.h"

CompteController::CompteController()
{
}

bool CompteController::deposer(
    CompteBancaire& compte,
    double montant,
    const QString& description
    )
{
    return compteService.deposer(compte, montant, description);
}

bool CompteController::retirer(
    CompteBancaire& compte,
    double montant,
    const QString& description
    )
{
    return compteService.retirer(compte, montant, description);
}

bool CompteController::virer(
    CompteBancaire& source,
    CompteBancaire& destination,
    double montant,
    const QString& description
    )
{
    return compteService.virer(source, destination, montant, description);
}

CompteCourant* CompteController::ouvrirCompteCourant(
    Client& client,
    const QString& iban,
    double soldeInitial,
    double decouvertAutorise
    )
{
    return banqueService.ouvrirCompteCourant(
        client,
        iban,
        soldeInitial,
        decouvertAutorise
        );
}

CompteEpargne* CompteController::ouvrirCompteEpargne(
    Client& client,
    const QString& iban,
    double soldeInitial,
    double tauxInteret
    )
{
    return banqueService.ouvrirCompteEpargne(
        client,
        iban,
        soldeInitial,
        tauxInteret
        );
}

CompteProfessionnel* CompteController::ouvrirCompteProfessionnel(
    Client& client,
    const QString& iban,
    double soldeInitial,
    const QString& nomEntreprise,
    double plafondRetrait,
    double plafondVirement
    )
{
    return banqueService.ouvrirCompteProfessionnel(
        client,
        iban,
        soldeInitial,
        nomEntreprise,
        plafondRetrait,
        plafondVirement
        );
}