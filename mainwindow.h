#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bookroomdialog.h"
#include "checkoutdialog.h"
#include "roomavailabledialog.h"
#include "transaction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    RoomAvailableDialog * ptrRoomAvailableDlg;
    CheckOutDialog * ptrCheckOutDlg;
    BookRoomDialog * ptrRoomBookingDlg;
    transaction * ptrTransaction;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnRoomBooking_clicked();
    void on_btnRoomCheckout_clicked();
    void on_btnCheckAvailability_clicked();
    void on_bntTransaction_clicked();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
