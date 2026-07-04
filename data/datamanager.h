#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "../models/client.h"
#include "../models/utilisateur.h"

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
};

#endif // DATAMANAGER_H