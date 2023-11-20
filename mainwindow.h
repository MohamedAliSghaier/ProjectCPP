#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <normes.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_exporter_clicked();

    void onComboBoxIndexChanged(int );

    void on_pb_rechercher_id_clicked();

    void on_pb_rechercher_nom_clicked();

private:
    Ui::MainWindow *ui;
    Normes N;
};

#endif // MAINWINDOW_H
