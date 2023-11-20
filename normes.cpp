#include "normes.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>



Normes::Normes()
{
    id=0; nom=" "; description=" ";date=" ";
}
Normes::Normes(int id,QString nom,QString description,QString date)
{
    this->id=id; this->nom=nom; this->description=description; this->date=date;
}
int Normes::getid(){return id;}
QString Normes:: getnom(){return nom;}
QString Normes:: getdescription(){return description;}
QString Normes::getdate(){return date;}
void Normes:: setid(int id){this->id=id;}
void Normes:: setnom(QString nom){this->nom=nom;}
void Normes:: setdescription(QString description){this->description=description;}
void Normes::setdate(QString date){this->date=date;}
bool Normes::ajouter()
{



    QString id_string=QString::number(id);
    QSqlQuery query;
    query.prepare("INSERT INTO normes (idnormes, nom, description,datecreation) "
                  "VALUES (:id, :forename, :surname, :date)");
    query.bindValue(":id", id_string);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", description);
    query.bindValue(":date", date);
    return query.exec();


}

QSqlQueryModel* Normes::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM normes");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DateCreation"));







    return model;

}

bool Normes::supprimer(int id)
{
       QSqlQuery query;
        query.prepare("Delete from normes where idnormes=:id");
        query.bindValue(0,id);
        return query.exec();

}

void Normes::printTableToPDF(QPainter *painter, QSqlQuery *query) {
        int row = 0;
        int col = 0;
        int columnCount = query->record().count();

        // Set up the table header
        for (col = 0; col < columnCount; ++col) {
            painter->drawText(col * 100, row * 20, query->record().fieldName(col));
        }

        // Move to the next row
        row++;

        // Fetch and print data
        while (query->next()) {
            for (col = 0; col < columnCount; ++col) {
                painter->drawText(col * 100, row * 20, query->value(col).toString());
            }
            // Move to the next row
            row++;
        }
    }

QSqlQueryModel* Normes::afficherSortedByColumn(const QString &columnName)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Use ORDER BY to specify sorting by the selected column
    model->setQuery(QString("SELECT * FROM normes ORDER BY %1").arg(columnName));

    // Set header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DateCreation"));

    return model;
}


QSqlQueryModel* Normes::searchNormeById(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Perform a SQL query to fetch the "norme" based on the entered ID
    QString query = QString("SELECT * FROM normes WHERE idnormes = %1").arg(id);
       model->setQuery(query);

    // Set header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DateCreation"));

    return model;
}

QSqlQueryModel* Normes::searchNormeByNom(const QString& nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    // Perform a SQL query to fetch the "norme" based on the entered ID
    QString query = QString("SELECT * FROM normes WHERE nom = '%1'").arg(nom);
       model->setQuery(query);

    // Set header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DateCreation"));

    return model;
}
