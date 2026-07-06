#ifndef FENETRECOMPTES_H
#define FENETRECOMPTES_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class FenetreComptes : public QWidget
{
    Q_OBJECT

private:
    QLabel* labelNombreComptes;
    QLineEdit* champRecherche;
    QPushButton* boutonAjouter;
    QPushButton* boutonModifier;
    QPushButton* boutonFermer;
    QPushButton* boutonActualiser;
    QTableWidget* tableComptes;

    void construireInterface();
    void appliquerStyle();
    void chargerDonneesTest();

public:
    explicit FenetreComptes(QWidget *parent = nullptr);
};

#endif
