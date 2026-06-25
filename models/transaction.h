#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

class Transaction
{
private:
    int id;
    QDateTime date;
    QString type;
    double montant;
    double soldeApres;
    QString description;

public:
    Transaction(
        int id,
        const QString& type,
        double montant,
        double soldeApres,
        const QString& description
        );

    int getId() const;
    QDateTime getDate() const;
    QString getType() const;
    double getMontant() const;
    double getSoldeApres() const;
    QString getDescription() const;
};

#endif // TRANSACTION_H