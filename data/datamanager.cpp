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
    if (database.isOpen())
    {
        database.close();
        qDebug() << "Base de données fermée.";
    }
}

QSqlDatabase DataManager::getDatabase() const
{
    return database;
}

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

    if (!ok)
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

    if (!ok)
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
        "decouvert_autorise REAL,"
        "taux_interet REAL,"
        "nom_entreprise TEXT,"
        "plafond_retrait REAL,"
        "plafond_virement REAL,"
        "FOREIGN KEY(client_id) REFERENCES clients(id)"
        ")"
        );

    if (!ok)
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

    if (!ok)
    {
        qDebug() << "Erreur création table transactions :" << query.lastError().text();
        return false;
    }

    ok = query.exec(
        "CREATE TABLE IF NOT EXISTS prets ("
        "id INTEGER PRIMARY KEY,"
        "client_id INTEGER NOT NULL,"
        "montant REAL NOT NULL,"
        "taux_annuel REAL NOT NULL,"
        "duree_mois INTEGER NOT NULL,"
        "mensualite REAL NOT NULL,"
        "statut TEXT NOT NULL,"
        "FOREIGN KEY(client_id) REFERENCES clients(id)"
        ")"
        );

    if (!ok)
    {
        qDebug() << "Erreur création table prets :" << query.lastError().text();
        return false;
    }

    qDebug() << "Tables créées avec succès.";
    return true;
}

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

    if (!query.exec())
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
        "FROM clients WHERE id = :id"
        );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Erreur recherche client :" << query.lastError().text();
        return nullptr;
    }

    if (query.next())
    {
        Client* client = new Client(
            query.value("id").toInt(),
            query.value("nom").toString(),
            query.value("email").toString(),
            query.value("telephone").toString()
            );

        if (query.value("statut").toString() == "INACTIF")
            client->setStatut(StatutClient::INACTIF);

        return client;
    }

    return nullptr;
}

QVector<Client*> DataManager::getTousLesClients()
{
    QVector<Client*> clients;
    QSqlQuery query(database);

    if (!query.exec("SELECT id, nom, email, telephone, statut FROM clients"))
    {
        qDebug() << "Erreur chargement clients :" << query.lastError().text();
        return clients;
    }

    while (query.next())
    {
        Client* client = new Client(
            query.value("id").toInt(),
            query.value("nom").toString(),
            query.value("email").toString(),
            query.value("telephone").toString()
            );

        if (query.value("statut").toString() == "INACTIF")
            client->setStatut(StatutClient::INACTIF);

        clients.append(client);
    }

    return clients;
}

bool DataManager::modifierClient(const Client& client)
{
    QSqlQuery query(database);

    query.prepare(
        "UPDATE clients SET "
        "nom = :nom, "
        "email = :email, "
        "telephone = :telephone, "
        "statut = :statut "
        "WHERE id = :id"
        );

    query.bindValue(":id", client.getId());
    query.bindValue(":nom", client.getNom());
    query.bindValue(":email", client.getEmail());
    query.bindValue(":telephone", client.getTelephone());
    query.bindValue(":statut", client.estActif() ? "ACTIF" : "INACTIF");

    if (!query.exec())
    {
        qDebug() << "Erreur modification client :" << query.lastError().text();
        return false;
    }

    qDebug() << "Client modifié :" << client.getNom();
    return true;
}

bool DataManager::supprimerClient(int id)
{
    QSqlQuery query(database);

    query.prepare(
        "UPDATE clients SET statut = 'INACTIF' "
        "WHERE id = :id"
        );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression logique client :" << query.lastError().text();
        return false;
    }

    qDebug() << "Client désactivé ID :" << id;
    return true;
}

bool DataManager::sauvegarderUtilisateur(const Utilisateur& utilisateur)
{
    QSqlQuery query(database);

    query.prepare(
        "INSERT OR REPLACE INTO utilisateurs "
        "(id, login, mot_de_passe_hash, nom_complet, role, statut) "
        "VALUES (:id, :login, :mot_de_passe_hash, :nom_complet, :role, :statut)"
        );

    QString role = "CLIENT";

    if (utilisateur.getRole() == RoleUtilisateur::ADMIN)
        role = "ADMIN";
    else if (utilisateur.getRole() == RoleUtilisateur::CONSEILLER)
        role = "CONSEILLER";

    QString statut = utilisateur.estActif() ? "ACTIF" : "BLOQUE";

    query.bindValue(":id", utilisateur.getId());
    query.bindValue(":login", utilisateur.getLogin());
    query.bindValue(":mot_de_passe_hash", utilisateur.getMotDePasseHash());
    query.bindValue(":nom_complet", utilisateur.getNomComplet());
    query.bindValue(":role", role);
    query.bindValue(":statut", statut);

    if (!query.exec())
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

    query.prepare("SELECT * FROM utilisateurs WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec())
    {
        qDebug() << "Erreur recherche utilisateur :" << query.lastError().text();
        return nullptr;
    }

    if (query.next())
    {
        RoleUtilisateur role = RoleUtilisateur::CLIENT;

        if (query.value("role").toString() == "ADMIN")
            role = RoleUtilisateur::ADMIN;
        else if (query.value("role").toString() == "CONSEILLER")
            role = RoleUtilisateur::CONSEILLER;

        StatutUtilisateur statut = StatutUtilisateur::ACTIF;

        if (query.value("statut").toString() == "BLOQUE")
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

bool DataManager::sauvegarderCompte(
    const CompteBancaire& compte,
    int clientId,
    const QString& type
    )
{
    QSqlQuery query(database);

    query.prepare(
        "INSERT OR REPLACE INTO comptes "
        "(iban, client_id, type, solde, statut, decouvert_autorise, taux_interet, "
        "nom_entreprise, plafond_retrait, plafond_virement) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
        );

    QString statut = "ACTIF";

    if (compte.getStatut() == StatutCompte::BLOQUE)
        statut = "BLOQUE";
    else if (compte.getStatut() == StatutCompte::FERME)
        statut = "FERME";

    QVariant decouvert;
    QVariant taux;
    QVariant entreprise;
    QVariant plafondRetrait;
    QVariant plafondVirement;

    if (const CompteCourant* c = dynamic_cast<const CompteCourant*>(&compte))
    {
        decouvert = c->getDecouvertAutorise();
    }
    else if (const CompteEpargne* e = dynamic_cast<const CompteEpargne*>(&compte))
    {
        taux = e->getTauxInteret();
    }
    else if (const CompteProfessionnel* p = dynamic_cast<const CompteProfessionnel*>(&compte))
    {
        entreprise = p->getNomEntreprise();
        plafondRetrait = p->getPlafondRetrait();
        plafondVirement = p->getPlafondVirement();
    }

    query.addBindValue(compte.getIBAN());
    query.addBindValue(clientId);
    query.addBindValue(type);
    query.addBindValue(compte.getSolde());
    query.addBindValue(statut);
    query.addBindValue(decouvert);
    query.addBindValue(taux);
    query.addBindValue(entreprise);
    query.addBindValue(plafondRetrait);
    query.addBindValue(plafondVirement);

    if (!query.exec())
    {
        qDebug() << "Erreur sauvegarde compte :" << query.lastError().text();
        return false;
    }

    qDebug() << "Compte sauvegardé :" << compte.getIBAN();
    return true;
}

CompteBancaire* DataManager::rechercherCompteParIBAN(const QString& iban)
{
    QSqlQuery query(database);

    query.prepare("SELECT * FROM comptes WHERE iban = :iban");
    query.bindValue(":iban", iban);

    if (!query.exec())
    {
        qDebug() << "Erreur recherche compte :" << query.lastError().text();
        return nullptr;
    }

    if (query.next())
    {
        QString type = query.value("type").toString();

        if (type == "COURANT")
        {
            return new CompteCourant(
                query.value("iban").toString(),
                query.value("solde").toDouble(),
                query.value("decouvert_autorise").toDouble()
                );
        }

        if (type == "EPARGNE")
        {
            return new CompteEpargne(
                query.value("iban").toString(),
                query.value("solde").toDouble(),
                query.value("taux_interet").toDouble()
                );
        }

        if (type == "PROFESSIONNEL")
        {
            return new CompteProfessionnel(
                query.value("iban").toString(),
                query.value("solde").toDouble(),
                query.value("nom_entreprise").toString(),
                query.value("plafond_retrait").toDouble(),
                query.value("plafond_virement").toDouble()
                );
        }
    }

    return nullptr;
}

QVector<CompteBancaire*> DataManager::getTousLesComptes()
{
    QVector<CompteBancaire*> comptes;
    QSqlQuery query(database);

    if (!query.exec("SELECT iban FROM comptes"))
    {
        qDebug() << "Erreur liste comptes :" << query.lastError().text();
        return comptes;
    }

    while (query.next())
    {
        CompteBancaire* compte =
            rechercherCompteParIBAN(query.value("iban").toString());

        if (compte != nullptr)
            comptes.append(compte);
    }

    return comptes;
}

bool DataManager::modifierCompte(const CompteBancaire& compte, const QString& type)
{
    QSqlQuery query(database);

    query.prepare(
        "UPDATE comptes SET "
        "type = :type, "
        "solde = :solde "
        "WHERE iban = :iban"
        );

    query.bindValue(":iban", compte.getIBAN());
    query.bindValue(":type", type);
    query.bindValue(":solde", compte.getSolde());

    if (!query.exec())
    {
        qDebug() << "Erreur modification compte :" << query.lastError().text();
        return false;
    }

    qDebug() << "Compte modifié :" << compte.getIBAN();
    return true;
}

bool DataManager::supprimerCompte(const QString& iban)
{
    QSqlQuery query(database);

    query.prepare(
        "UPDATE comptes SET statut = 'FERME' "
        "WHERE iban = :iban"
        );

    query.bindValue(":iban", iban);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression logique compte :" << query.lastError().text();
        return false;
    }

    qDebug() << "Compte fermé :" << iban;
    return true;
}

bool DataManager::sauvegarderTransaction(
    const Transaction& transaction,
    const QString& ibanCompte
    )
{
    QSqlQuery query(database);

    query.prepare(
        "INSERT INTO transactions "
        "(iban, date, type, montant, solde_apres, description) "
        "VALUES "
        "(:iban, :date, :type, :montant, :solde_apres, :description)"
        );

    query.bindValue(":iban", ibanCompte);
    query.bindValue(":date", transaction.getDate().toString(Qt::ISODate));
    query.bindValue(":type", transaction.getType());
    query.bindValue(":montant", transaction.getMontant());
    query.bindValue(":solde_apres", transaction.getSoldeApres());
    query.bindValue(":description", transaction.getDescription());

    if (!query.exec())
    {
        qDebug() << "Erreur sauvegarde transaction :" << query.lastError().text();
        return false;
    }

    qDebug() << "Transaction enregistrée.";
    return true;
}

bool DataManager::sauvegarderPret(const Pret& pret, int clientId)
{
    QSqlQuery query(database);

    query.prepare(
        "INSERT OR REPLACE INTO prets "
        "(id, client_id, montant, taux_annuel, duree_mois, mensualite, statut) "
        "VALUES "
        "(:id, :client_id, :montant, :taux_annuel, :duree_mois, :mensualite, :statut)"
        );

    QString statut = "EN_ATTENTE";

    if (pret.getStatut() == StatutPret::ACCEPTE)
        statut = "ACCEPTE";
    else if (pret.getStatut() == StatutPret::REFUSE)
        statut = "REFUSE";
    else if (pret.getStatut() == StatutPret::REMBOURSE)
        statut = "REMBOURSE";

    query.bindValue(":id", pret.getId());
    query.bindValue(":client_id", clientId);
    query.bindValue(":montant", pret.getMontant());
    query.bindValue(":taux_annuel", pret.getTauxAnnuel());
    query.bindValue(":duree_mois", pret.getDureeMois());
    query.bindValue(":mensualite", pret.getMensualite());
    query.bindValue(":statut", statut);

    if (!query.exec())
    {
        qDebug() << "Erreur sauvegarde prêt :" << query.lastError().text();
        return false;
    }

    qDebug() << "Prêt sauvegardé ID :" << pret.getId();
    return true;
}

QVector<Transaction*> DataManager::getTransactionsCompte(const QString& iban)
{
    QVector<Transaction*> transactions;

    QSqlQuery query(database);

    query.prepare(
        "SELECT id, type, montant, solde_apres, description "
        "FROM transactions "
        "WHERE iban = :iban "
        "ORDER BY date DESC"
        );

    query.bindValue(":iban", iban);

    if (!query.exec())
    {
        qDebug() << "Erreur chargement transactions :"
                 << query.lastError().text();
        return transactions;
    }

    while (query.next())
    {
        Transaction* transaction = new Transaction(
            query.value("id").toInt(),
            query.value("type").toString(),
            query.value("montant").toDouble(),
            query.value("solde_apres").toDouble(),
            query.value("description").toString()
            );

        transactions.append(transaction);
    }

    return transactions;
}

Pret* DataManager::rechercherPretParId(int id)
{
    QSqlQuery query(database);

    query.prepare(
        "SELECT * FROM prets WHERE id = :id"
        );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Erreur recherche prêt :" << query.lastError().text();
        return nullptr;
    }

    if (query.next())
    {
        Pret* pret = new Pret(
            query.value("id").toInt(),
            query.value("montant").toDouble(),
            query.value("taux_annuel").toDouble(),
            query.value("duree_mois").toInt()
            );

        QString statutTexte = query.value("statut").toString();

        if (statutTexte == "ACCEPTE")
            pret->setStatut(StatutPret::ACCEPTE);
        else if (statutTexte == "REFUSE")
            pret->setStatut(StatutPret::REFUSE);
        else if (statutTexte == "REMBOURSE")
            pret->setStatut(StatutPret::REMBOURSE);

        return pret;
    }

    return nullptr;
}

QVector<Pret*> DataManager::getTousLesPrets()
{
    QVector<Pret*> prets;
    QSqlQuery query(database);

    if (!query.exec("SELECT id FROM prets"))
    {
        qDebug() << "Erreur liste prêts :" << query.lastError().text();
        return prets;
    }

    while (query.next())
    {
        Pret* pret = rechercherPretParId(query.value("id").toInt());

        if (pret != nullptr)
            prets.append(pret);
    }

    return prets;
}

bool DataManager::modifierStatutPret(int id, StatutPret statut)
{
    QSqlQuery query(database);

    QString statutTexte = "EN_ATTENTE";

    if (statut == StatutPret::ACCEPTE)
        statutTexte = "ACCEPTE";
    else if (statut == StatutPret::REFUSE)
        statutTexte = "REFUSE";
    else if (statut == StatutPret::REMBOURSE)
        statutTexte = "REMBOURSE";

    query.prepare(
        "UPDATE prets SET statut = :statut WHERE id = :id"
        );

    query.bindValue(":id", id);
    query.bindValue(":statut", statutTexte);

    if (!query.exec())
    {
        qDebug() << "Erreur modification statut prêt :" << query.lastError().text();
        return false;
    }

    qDebug() << "Statut prêt modifié ID :" << id;
    return true;
}

bool DataManager::supprimerPret(int id)
{
    QSqlQuery query(database);

    query.prepare(
        "UPDATE prets SET statut = 'REFUSE' WHERE id = :id"
        );

    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression logique prêt :" << query.lastError().text();
        return false;
    }

    qDebug() << "Prêt supprimé logiquement ID :" << id;
    return true;
}