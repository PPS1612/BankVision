#include "utilisateur.h"

Utilisateur::Utilisateur(
    int id,
    const QString& login,
    const QString& motDePasseHash,
    const QString& nomComplet,
    RoleUtilisateur role,
    StatutUtilisateur statut)
    : id(id),
    login(login),
    motDePasseHash(motDePasseHash),
    nomComplet(nomComplet),
    role(role),
    statut(statut)
{
}

// Getters

int Utilisateur::getId() const
{
    return id;
}

QString Utilisateur::getLogin() const
{
    return login;
}

QString Utilisateur::getMotDePasseHash() const
{
    return motDePasseHash;
}

QString Utilisateur::getNomComplet() const
{
    return nomComplet;
}

RoleUtilisateur Utilisateur::getRole() const
{
    return role;
}

StatutUtilisateur Utilisateur::getStatut() const
{
    return statut;
}

// Setters

void Utilisateur::setLogin(const QString& login)
{
    this->login = login;
}

void Utilisateur::setMotDePasseHash(const QString& hash)
{
    motDePasseHash = hash;
}

void Utilisateur::setNomComplet(const QString& nom)
{
    nomComplet = nom;
}

void Utilisateur::setRole(RoleUtilisateur role)
{
    this->role = role;
}

void Utilisateur::setStatut(StatutUtilisateur statut)
{
    this->statut = statut;
}

bool Utilisateur::estActif() const
{
    return statut == StatutUtilisateur::ACTIF;
}