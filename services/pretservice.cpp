#include "pretservice.h"
#include "../data/datamanager.h"

PretService::PretService()
{
}

bool PretService::ajouterPret(const Pret& pret, int clientId)
{
    return DataManager::getInstance().sauvegarderPret(pret, clientId);
}

Pret* PretService::rechercherPretParId(int id)
{
    return DataManager::getInstance().rechercherPretParId(id);
}

QVector<Pret*> PretService::getTousLesPrets()
{
    return DataManager::getInstance().getTousLesPrets();
}

bool PretService::accepterPret(int id)
{
    return DataManager::getInstance().modifierStatutPret(id, StatutPret::ACCEPTE);
}

bool PretService::refuserPret(int id)
{
    return DataManager::getInstance().modifierStatutPret(id, StatutPret::REFUSE);
}

bool PretService::rembourserPret(int id)
{
    return DataManager::getInstance().modifierStatutPret(id, StatutPret::REMBOURSE);
}

bool PretService::supprimerPret(int id)
{
    return DataManager::getInstance().supprimerPret(id);
}