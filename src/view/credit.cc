#include "credit.h"

#include "ui_credit.h"

using namespace s21;

Credit::Credit(QWidget *parent, Controller *c)
    : QDialog(parent), ui(new Ui::Credit), credit_controller_(c) {
  ui->setupUi(this);
  ui->payment->setReadOnly(true);
  ui->overpayment->setReadOnly(true);
  ui->totalPayment->setReadOnly(true);
  this->setFixedSize(this->geometry().width(), this->geometry().height());
}

Credit::~Credit() { delete ui; }

double Credit::GetAmount() { return ui->amount_of_credit->text().toDouble(); }

int Credit::GetMonths() { return ui->amount_months->text().toInt(); }

double Credit::GetRate() { return ui->interest_rate->text().toDouble(); }

bool Credit::GetType() { return ui->Annuity->isChecked(); }

Date Credit::GetStartDate() {
  QDate temp = ui->start_date->date();
  return Date(temp.day(), temp.month(), temp.year());
}

void Credit::on_calculCredit_clicked() {
  ClearFields();
  CreditCalculator::CreditResult result = credit_controller_->CalculateCredit(
      GetAmount(), GetMonths(), GetRate(), GetType(), GetStartDate());
  std::vector<std::string> m = result.monthly_payment;
  auto it = m.begin();
  while (it != m.end()) {
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QString::fromStdString(*it));
    ui->mon_pay->addItem(item);
    ++it;
  }
  ui->totalPayment->setText((QString::number(result.total_payment, 'd', 2)));
  ui->overpayment->setText((QString::number(result.overpayment, 'd', 2)));
  ui->payment->setText((QString::number(result.payment, 'd', 2)));
}

void Credit::ClearFields() {
  ui->mon_pay->clear();
  ui->payment->clear();
  ui->overpayment->clear();
  ui->totalPayment->clear();
}

void Credit::on_calculCredit_2_clicked() { ClearFields(); }
