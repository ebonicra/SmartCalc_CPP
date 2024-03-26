#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QAbstractButton>
#include <QDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QVector>

#include "../controller/controller.h"
#include "credit.h"
#include "deposit.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *c);
  ~MainWindow();

  QString expression;
  void button(QAbstractButton *btn);

 private slots:
  void on_main_line_textEdited(const QString &arg1);
  void on_smallClean_but_clicked();
  void on_bigClean_but_clicked();
  void on_enter_but_clicked();
  bool eventFilter(QObject *obj, QEvent *event);
  void on_graph_but_clicked();
  int GetXMin();
  int GetXMax();
  int GetYMin();
  int GetYMax();
  double GetXValue();
  int GetAmountOfpoints();
  void on_credit_but_clicked();
  void on_deposit_but_clicked();

 private:
  Ui::MainWindow *ui;
  Controller *controller_;
};

}  // namespace s21

#endif  // VIEW_MAINWINDOW_H
