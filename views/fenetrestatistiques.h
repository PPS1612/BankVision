#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>

// ─── Widget : Courbe d'évolution du solde (QPainter) ───────────────────────
class GraphiqueCourbe : public QWidget
{
    Q_OBJECT
public:
    explicit GraphiqueCourbe(QWidget* parent = nullptr);
    void setDonnees(const QVector<double>& valeurs, const QVector<QString>& etiquettes);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QVector<double>  valeurs;
    QVector<QString> etiquettes;
};

// ─── Widget : Camembert des dépenses par catégorie ─────────────────────────
class GraphiqueCamembert : public QWidget
{
    Q_OBJECT
public:
    explicit GraphiqueCamembert(QWidget* parent = nullptr);
    void setDonnees(const QVector<QString>& labels, const QVector<double>& parts);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QVector<QString> labels;
    QVector<double>  parts;
    QVector<QColor>  couleurs;
};

// ─── Widget : Histogramme recettes / dépenses ──────────────────────────────
class GraphiqueHistogramme : public QWidget
{
    Q_OBJECT
public:
    explicit GraphiqueHistogramme(QWidget* parent = nullptr);
    void setDonnees(const QVector<double>& recettes, const QVector<double>& depenses,
                    const QVector<QString>& mois);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QVector<double>  recettes;
    QVector<double>  depenses;
    QVector<QString> mois;
};

// ─── Fenêtre principale Statistiques ───────────────────────────────────────
class FenetreStatistiques : public QWidget
{
    Q_OBJECT
public:
    explicit FenetreStatistiques(QWidget* parent = nullptr);

private:
    GraphiqueCourbe*       graphiqueCourbe;
    GraphiqueCamembert*    graphiqueCamembert;
    GraphiqueHistogramme*  graphiqueHistogramme;

    QLabel* labelSoldeMoyen;
    QLabel* labelDepenseMax;
    QLabel* labelTauxEpargne;
    QLabel* labelSoldeActuel;

    void construireInterface();
    void appliquerStyle();
    void chargerDonneesTest();
};
