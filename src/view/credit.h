#ifndef VIEW_CREDIT_H
#define VIEW_CREDIT_H

#include <QDate>
#include <QDialog>
#include <ctime>

#include "../controller/controller.h"
#include "../model/creditcalculator.h"

namespace Ui {
class Credit;
}

namespace s21 {
class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr, Controller *c = nullptr);
  ~Credit();
  double GetAmount();
  int GetMonths();
  double GetRate();
  bool GetType();
  Date GetStartDate();

 private slots:
  void on_calculCredit_clicked();
  void on_calculCredit_2_clicked();

 private:
  void ClearFields();
  Ui::Credit *ui;
  Controller *credit_controller_;
};

}  // namespace s21

#endif  // VIEW_CREDIT_H
