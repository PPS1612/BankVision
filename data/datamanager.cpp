#include "datamanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

DataManager::DataManager()
{
}

DataManager& DataManager::getInstance()
{
    static DataManager instance;
    return instance;
}

//=====================================================
// Gestion de la base de données
//=====================================================

bool DataManager::initialiser(const QString& cheminBase)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(cheminBase);

    if (!database.open())
    {
        qDebug() << "Erreur ouverture base :" << database.lastError().text();
        return false;
    }

    qDebug() << "Base de données ouverte avec succès.";

    return creerTables();
}

void DataManager::fermer()
{
    if(database.isOpen())
    {
        database.close();
        qDebug() << "Base de données fermée.";
    }
}

QSqlDatabase DataManager::getDatabase() const
{
    return database;
}

//=====================================================
// Création des tables
//=====================================================

bool DataManager::creerTables()
{
    QSqlQuery query(database);

    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS clients ("
        "id INTEGER PRIMARY KEY,"
        "nom TEXT NOT NULL,"
        "email TEXT NOT NULL,"
        "telephone TEXT NOT NULL,"
        "statut TEXT NOT NULL"
        ")"
        );

    if(!ok)
    {
        qDebug() << "Erreur création table clients :" << query.lastError().text();
        return false;
    }

    ok = query.exec(
        "CREATE TABLE IF NOT EXISTS utilisateurs ("
        "id INTEGER PRIMARY KEY,"
        "login TEXT NOT NULL UNIQUE,"
        "mot_de_passe_hash TEXT NOT NULL,"
        "nom_complet TEXT NOT NULL,"
        "role TEXT NOT NULL,"
        "statut TEXT NOT NULL"
        ")"
        );

    if(!ok)
    {
        qDebug() << "Erreur création table utilisateurs :" << query.lastError().text();
        return false;
    }

    ok = query.exec(
        "CREATE TABLE IF NOT EXISTS comptes ("
        "iban TEXT PRIMARY KEY,"
        "client_id INTEGER NOT NULL,"
        "type TEXT NOT NULL,"
        "solde REAL NOT NULL,"
        "statut TEXT NOT NULL,"
        "FOREIGN KEY(client_id) REFERENCES clients(id)"
        ")"
        );

    if(!ok)
    {
        qDebug() << "Erreur création table comptes :" << query.lastError().text();
        return false;
    }

    ok = query.exec(
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "iban TEXT NOT NULL,"
        "date TEXT NOT NULL,"
        "type TEXT NOT NULL,"
        "montant REAL NOT NULL,"
        "solde_apres REAL NOT NULL,"
        "description TEXT,"
        "FOREIGN KEY(iban) REFERENCES comptes(iban)"
        ")"
        );

    if(!ok)
    {
        qDebug() << "Erreur création table transactions :" << query.lastError().text();
        return false;
    }

    qDebug() << "Tables créées avec succès.";

    return true;
}

//=====================================================
// Gestion des clients
//=====================================================

bool DataManager::sauvegarderClient(const Client& client)
{
    QSqlQuery query(database);

    query.prepare(
        "INSERT OR REPLACE INTO clients "
        "(id, nom, email, telephone, statut) "
        "VALUES (:id, :nom, :email, :telephone, :statut)"
        );

    query.bindValue(":id", client.getId());
    query.bindValue(":nom", client.getNom());
    query.bindValue(":email", client.getEmail());
    query.bindValue(":telephone", client.getTelephone());
    query.bindValue(":statut", client.estActif() ? "ACTIF" : "INACTIF");

    if(!query.exec())
    {
        qDebug() << "Erreur sauvegarde client :" << query.lastError().text();
        return false;
    }

    qDebug() << "Client sauvegardé :" << client.getNom();

    return true;
}

Client* DataManager::rechercherClientParId(int id)
{
    QSqlQuery query(database);

    query.prepare(
        "SELECT id, nom, email, telephone, statut "
        "FROM clients "
        "WHERE id = :id"
        );

    query.bindValue(":id", id);

    if(!query.exec())
    {
        qDebug() << "Erreur recherche client :" << query.lastError().text();
        return nullptr;
    }

    if(query.next())
    {
        Client* client = new Client(
            query.value("id").toInt(),
            query.value("nom").toString(),
            query.value("email").toString(),
            query.value("telephone").toString()
            );

        if(query.value("statut").toString() == "INACTIF")
        {
            client->setStatut(StatutClient::INACTIF);
        }

        return client;
    }

    return nullptr;
}

//=====================================================
// Gestion des utilisateurs
//=====================================================

bool DataManager::sauvegarderUtilisateur(const Utilisateur& utilisateur)
{
    QSqlQuery query(database);

    query.prepare(
        "INSERT OR REPLACE INTO utilisateurs "
        "(id, login, mot_de_passe_hash, nom_complet, role, statut) "
        "VALUES (:id, :login, :mot_de_passe_hash, :nom_complet, :role, :statut)"
        );

    QString role = "CLIENT";

    if(utilisateur.getRole() == RoleUtilisateur::ADMIN)
        role = "ADMIN";
    else if(utilisateur.getRole() == RoleUtilisateur::CONSEILLER)
        role = "CONSEILLER";

    QString statut = utilisateur.estActif() ? "ACTIF" : "BLOQUE";

    query.bindValue(":id", utilisateur.getId());
    query.bindValue(":login", utilisateur.getLogin());
    query.bindValue(":mot_de_passe_hash", utilisateur.getMotDePasseHash());
    query.bindValue(":nom_complet", utilisateur.getNomComplet());
    query.bindValue(":role", role);
    query.bindValue(":statut", statut);

    if(!query.exec())
    {
        qDebug() << "Erreur sauvegarde utilisateur :" << query.lastError().text();
        return false;
    }

    qDebug() << "Utilisateur sauvegardé :" << utilisateur.getLogin();

    return true;
}

Utilisateur* DataManager::rechercherUtilisateurParLogin(const QString& login)
{
    QSqlQuery query(database);

    query.prepare(
        "SELECT * FROM utilisateurs WHERE login = :login"
        );

    query.bindValue(":login", login);

    if(!query.exec())
    {
        qDebug() << "Erreur recherche utilisateur :" << query.lastError().text();
        return nullptr;
    }

    if(query.next())
    {
        RoleUtilisateur role = RoleUtilisateur::CLIENT;

        if(query.value("role").toString() == "ADMIN")
            role = RoleUtilisateur::ADMIN;
        else if(query.value("role").toString() == "CONSEILLER")
            role = RoleUtilisateur::CONSEILLER;

        StatutUtilisateur statut = StatutUtilisateur::ACTIF;

        if(query.value("statut").toString() == "BLOQUE")
            statut = StatutUtilisateur::BLOQUE;

        return new Utilisateur(
            query.value("id").toInt(),
            query.value("login").toString(),
            query.value("mot_de_passe_hash").toString(),
            query.value("nom_complet").toString(),
            role,
            statut
            );
    }

    return nullptr;
}