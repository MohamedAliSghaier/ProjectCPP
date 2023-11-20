#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "normes.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(100, 999999, this));
    ui->comboBoxSort->addItem("Tri Par date d'ajout (Sans Tri)");
    ui->comboBoxSort->addItem("Trier par Identifiant");
    ui->comboBoxSort->addItem("Trier par Nom");
    ui->comboBoxSort->addItem("Trier par Description");
    ui->tab_normes->setSortingEnabled(true);
    ui->tab_normes->setModel(N.afficher());
    connect(ui->comboBoxSort, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onComboBoxIndexChanged);



}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pb_ajouter_clicked()
{
  int id=ui->le_id->text().toInt();
  QString nom=ui->le_nom->text();
  QString description=ui->le_description->text();
  QString date=ui->le_date->text();
  Normes N(id,nom,description,date);
  bool test=N.ajouter();
  if(test)
  {
      QMessageBox::information(nullptr, QObject::tr("OK"),
                  QObject::tr("Ajout effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tab_normes->setModel(N.afficher());


}
  else
      QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                  QObject::tr("Ajout non effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_clicked()
{
    Normes N1;
    N1.setid(ui->le_id_supp->text().toInt());
    bool test=N1.supprimer(N1.getid());
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_normes->setModel(N.afficher());

  }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                    QObject::tr("Suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_exporter_clicked()
{
    QSqlQuery query("SELECT * FROM normes"); // Change this to your actual table name

            // Set up the PDF file dialog
            QString fileName = QFileDialog::getSaveFileName(this, "Export to PDF", "", "PDF Files (*.pdf)");

            if (!fileName.isEmpty()) {
                QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);

                QPainter painter;
                painter.begin(&printer);

                // Print data to PDF
                N.printTableToPDF(&painter, &query);

                painter.end();

                QMessageBox::information(this, "Export PDF", "Data exported to PDF successfully!");
            }
}


void MainWindow::onComboBoxIndexChanged(int index)
{
    // Determine the sorting column based on the selected item in the comboBox
    QString columnName;

    // Assuming the comboBox items represent column names, adjust this part based on your comboBox content
    switch (index) {
        case 0:
               { ui->tab_normes->setModel(N.afficher());}

        case 1: // For example, if the first item is selected
            columnName = "idnormes";
            break;
        case 2: // For example, if the second item is selected
            columnName = "nom";
            break;
        case 3: // If you want to sort by a QString column, adjust this part
            columnName = "description";
            break;
        // Add more cases as needed
    }
    if (index!=0)
    {
    // Call the function to repopulate the table view with sorting by the selected column
    ui->tab_normes->setModel(N.afficherSortedByColumn(columnName));
    }
}

void MainWindow::on_pb_rechercher_id_clicked()
{
    int enteredId = ui->le_id_recherche->text().toInt();

        // Perform a SQL query to fetch the corresponding "norme" based on the entered ID
    QSqlQueryModel* searchResult = N.searchNormeById(enteredId);
    if (searchResult->rowCount() == 0) {
            QMessageBox::information(this, "Search Result", "No norme found for the entered ID.");
        }
    else
    {
        // Set the model for the table view to display the search result
        ui->tab_recherche_id->setModel(searchResult);
    }
}

void MainWindow::on_pb_rechercher_nom_clicked()
{
    QString enteredNom = ui->le_nom_recherche->text();

        // Perform a SQL query to fetch the corresponding "norme" based on the entered ID
    QSqlQueryModel* searchResult = N.searchNormeByNom(enteredNom);
    if (searchResult->rowCount() == 0) {
            QMessageBox::information(this, "Search Result", "No norme found for the entered Nom.");
        }
    else
    {
        // Set the model for the table view to display the search result
        ui->tab_recherche_nom->setModel(searchResult);
    }
}
