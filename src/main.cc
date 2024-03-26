#include <QApplication>

#include "controller/controller.h"
#include "view/mainwindow.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainCalculator model;
  CreditCalculator credit_model;
  DepositCalculator deposit_model;
  Controller controller(&model, &credit_model, &deposit_model);
  MainWindow w(&controller);
  w.show();
  return a.exec();
}
