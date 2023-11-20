#ifndef NORMES_H
#define NORMES_H
#include <QString>
#include<QSqlQueryModel>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QMessageBox>


class Normes
{
public:
    Normes();
    Normes(int,QString,QString,QString);
    int getid();
    QString getnom();
    QString getdescription();
    QString getdate();
    void setid(int);
    void setnom(QString);
    void setdescription(QString);
    void setdate(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
   void printTableToPDF(QPainter *, QSqlQuery *);
   QSqlQueryModel* afficherSortedByColumn(const QString &columnName);
   QSqlQueryModel*  searchNormeById  (int id);
   QSqlQueryModel*  searchNormeByNom(const QString &nom);


private:
    int id;
    QString nom,description,date;

};

#endif // NORMES_H
