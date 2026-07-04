#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "../models/client.h"
#include "../models/utilisateur.h"
#include "../models/comptecourant.h"
#include "../models/compteepargne.h"
#include "../models/compteprofessionnel.h"
#include "../models/transaction.h"
#include "../models/pret.h"

class DataManager
{
private:
    QSqlDatabase database;

    // Constructeur privé (Singleton)
    DataManager();

    // Empêcher la copie
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

public:
    // Singleton
    static DataManager& getInstance();

    // Gestion de la base de données
    bool initialiser(const QString& cheminBase);
    bool creerTables();
    void fermer();

    QSqlDatabase getDatabase() const;

    // ==========================
    // Gestion des clients
    // ==========================
    bool sauvegarderClient(const Client& client);
    Client* rechercherClientParId(int id);

    // ==========================
    // Gestion des utilisateurs
    // ==========================
    bool sauvegarderUtilisateur(const Utilisateur& utilisateur);
    Utilisateur* rechercherUtilisateurParLogin(const QString& login);

    bool sauvegarderCompte(
        const CompteBancaire& compte,
        int clientId,
        const QString& type
        );

    bool sauvegarderTransaction(
        const Transaction& transaction,
        const QString& ibanCompte
        );

    bool sauvegarderPret(const Pret& pret, int clientId);
};

#endif // DATAMANAGER_H