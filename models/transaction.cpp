#include "transaction.h"

Transaction::Transaction(

    int id,
    const QString& type,
    double montant,
    double soldeApres,
    const QString& description)
    : id(id),
      date(QDateTime::currentDateTime()),
      type(type),
      montant(montant),
      soldeApres(soldeApres),
      description(description)
{
}

int Transaction::getId() const{
    return id;
}


QDateTime Transaction::getDate() const{
    return date;
}


QString Transaction::getType() const{
    return type;
}


double Transaction::getMontant() const{
    return montant;
}


double Transaction::getSoldeApres() const{
    return soldeApres;
}


QString Transaction::getDescription() const{
    return description;
}
