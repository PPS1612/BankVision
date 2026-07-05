#ifndef PRETSERVICE_H
#define PRETSERVICE_H

#include <QVector>

#include "../models/pret.h"

class PretService
{
public:
    PretService();

    bool ajouterPret(const Pret& pret, int clientId);

    Pret* rechercherPretParId(int id);
    QVector<Pret*> getTousLesPrets();

    bool accepterPret(int id);
    bool refuserPret(int id);
    bool rembourserPret(int id);

    bool supprimerPret(int id);
};

#endif
