#ifndef FENETREOPERATIONS_H
#define FENETREOPERATIONS_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QTextEdit;

class FenetreOperations : public QWidget
{
    Q_OBJECT

private:
    QComboBox* comboTypeOperation;
    QComboBox* comboCompteSource;
    QComboBox* comboCompteDestination;

    QLineEdit* champMontant;
    QTextEdit* champDescription;

    QPushButton* boutonValider;
    QPushButton* boutonAnnuler;

    QLabel* labelMessage;

    void construireInterface();
    void appliquerStyle();
    void chargerDonneesTest();

private slots:
    void validerOperation();

public:
    explicit FenetreOperations(QWidget *parent = nullptr);
};

#endif