#ifndef BANQUESERVICE_H
#define BANQUESERVICE_H

#include <QVector>

#include "../models/banque.h"
#include "../models/Client.h"
#include "../models/comptebancaire.h"
#include "../models/comptecourant.h"
#include "../models/compteepargne.h"
#include "../models/compteprofessionnel.h"

class BanqueService
{
public:
    BanqueService();

    bool ajouterClient(Banque& banque, Client* client);
    bool supprimerClient(Banque& banque, int idClient);
    Client* rechercherClient(Banque& banque, int idClient);

    int getNombreClients(const Banque& banque) const;
    int getNombreComptes(const Banque& banque) const;
    double calculerSoldeTotalBanque(const Banque& banque) const;

    CompteCourant* ouvrirCompteCourant(
        Client& client,
        const QString& iban,
        double soldeInitial,
        double decouvertAutorise
        );

    CompteEpargne* ouvrirCompteEpargne(
        Client& client,
        const QString& iban,
        double soldeInitial,
        double tauxInteret
        );

    CompteProfessionnel* ouvrirCompteProfessionnel(
        Client& client,
        const QString& iban,
        double soldeInitial,
        const QString& nomEntreprise,
        double plafondRetrait,
        double plafondVirement
        );
};

#endif