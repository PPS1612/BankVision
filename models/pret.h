#ifndef PRET_H
#define PRET_H

#include <QString>

enum class StatutPret
{
    EN_ATTENTE,
    ACCEPTE,
    REFUSE,
    REMBOURSE
};

class Pret
{
private:
    int id;
    double montant;
    double tauxAnnuel;
    int dureeMois;
    double mensualite;
    StatutPret statut;

public:
    Pret(
        int id,
        double montant,
        double tauxAnnuel,
        int dureeMois);

    // Getters
    int getId() const;
    double getMontant() const;
    double getTauxAnnuel() const;
    int getDureeMois() const;
    double getMensualite() const;
    StatutPret getStatut() const;

    // Setter
    void setStatut(StatutPret statut);

    // Méthode métier propre à l'objet
    double calculerMensualite() const;
};

#endif