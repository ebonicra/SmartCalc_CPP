#ifndef VIEW_DEPOSIT_H
#define VIEW_DEPOSIT_H

#include <QDate>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <numeric>

#include "../controller/controller.h"

namespace Ui {
class Deposit;
}

namespace s21 {

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr, Controller *d = nullptr);
  ~Deposit();

 private slots:
  void on_clear_clicked();
  void on_rep_add_clicked();
  void on_wit_add_clicked();
  void on_calculate_clicked();

 private:
  double GetDepositAmount();
  int GetDepositTerm();
  int GetTypeTerm();
  double GetInterestRate();
  double GetTaxRate();
  int GetPeriodicity();
  Date GetStartDate();
  bool GetCapitalization();
  DepositCalculator::ChangeList &GetReplenishment();
  DepositCalculator::ChangeList &GetWithdrawal();

  void SetValues(s21::DepositCalculator::DepositResult result);
  void ClearValues();

  DepositCalculator::ChangeList replenishment_;
  DepositCalculator::ChangeList withdrawal_;
  int count_replenishment_;
  int count_withdrawal_;

  Ui::Deposit *ui;
  Controller *deposit_controller_;
};

}  // namespace s21

#endif  // VIEW_DEPOSIT_H
