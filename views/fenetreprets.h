#ifndef FENETREPRETS_H
#define FENETREPRETS_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;
class QComboBox;

class FenetrePrets : public QWidget
{
    Q_OBJECT

private:
    QLabel* labelNombrePrets;
    QLineEdit* champRecherche;
    QPushButton* boutonNouveauPret;
    QPushButton* boutonAccepter;
    QPushButton* boutonRefuser;
    QPushButton* boutonRembourser;
    QPushButton* boutonSupprimer;
    QPushButton* boutonFermer;
    QPushButton* boutonActualiser;
    QTableWidget* tablePrets;

    void construireInterface();
    void appliquerStyle();
    void chargerDonneesTest();
    void mettreAJourStatutLigne(int ligne, const QString& statut);
    double calculerMensualite(double montant, double tauxAnnuel, int dureeMois) const;

private slots:
    void ouvrirFormulaireNouveauPret();
    void accepterPretSelectionne();
    void refuserPretSelectionne();
    void rembourserPretSelectionne();
    void supprimerPretSelectionne();
    void filtrerPrets(const QString& texte);

public:
    explicit FenetrePrets(QWidget *parent = nullptr);
};

#endif
