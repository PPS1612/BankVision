#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QString>

enum class RoleUtilisateur
{
    ADMIN,
    CONSEILLER,
    CLIENT
};

enum class StatutUtilisateur
{
    ACTIF,
    BLOQUE
};

class Utilisateur
{
private:
    int id;
    QString login;
    QString motDePasseHash;
    QString nomComplet;

    RoleUtilisateur role;
    StatutUtilisateur statut;

public:
    Utilisateur(
        int id,
        const QString& login,
        const QString& motDePasseHash,
        const QString& nomComplet,
        RoleUtilisateur role = RoleUtilisateur::CLIENT,
        StatutUtilisateur statut = StatutUtilisateur::ACTIF
        );

    // Getters
    int getId() const;
    QString getLogin() const;
    QString getMotDePasseHash() const;
    QString getNomComplet() const;
    RoleUtilisateur getRole() const;
    StatutUtilisateur getStatut() const;

    // Setters
    void setLogin(const QString& login);
    void setMotDePasseHash(const QString& hash);
    void setNomComplet(const QString& nom);
    void setRole(RoleUtilisateur role);
    void setStatut(StatutUtilisateur statut);

    bool estActif() const;
};

#endif