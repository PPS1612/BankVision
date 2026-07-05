#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H

#include <QVector>

#include "../models/transaction.h"

class TransactionService
{
public:
    TransactionService();

    bool ajouterTransaction(const Transaction& transaction,
                            const QString& ibanCompte);

    QVector<Transaction> getHistoriqueCompte(const QString& ibanCompte);
};

#endif
