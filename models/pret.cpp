#include "pret.h"

#include <cmath>

Pret::Pret(
    int id,
    double montant,
    double tauxAnnuel,
    int dureeMois)
    : id(id),
    montant(montant),
    tauxAnnuel(tauxAnnuel),
    dureeMois(dureeMois),
    statut(StatutPret::EN_ATTENTE)
{
    mensualite = calculerMensualite();
}

int Pret::getId() const
{
    return id;
}

double Pret::getMontant() const
{
    return montant;
}

double Pret::getTauxAnnuel() const
{
    return tauxAnnuel;
}

int Pret::getDureeMois() const
{
    return dureeMois;
}

double Pret::getMensualite() const
{
    return mensualite;
}

StatutPret Pret::getStatut() const
{
    return statut;
}

void Pret::setStatut(StatutPret statut)
{
    this->statut = statut;
}

double Pret::calculerMensualite() const
{
    double tauxMensuel = tauxAnnuel / 100.0 / 12.0;

    if (tauxMensuel == 0)
    {
        return montant / dureeMois;
    }

    return montant *
           tauxMensuel /
           (1 - std::pow(1 + tauxMensuel, -dureeMois));
}