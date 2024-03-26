#include "deposit.h"

#include "ui_deposit.h"

using namespace s21;

Deposit::Deposit(QWidget *parent, Controller *d)
    : QDialog(parent), ui(new Ui::Deposit), deposit_controller_(d) {
  ui->setupUi(this);
  ui->accrued_interest->setReadOnly(true);
  ui->tax_amount->setReadOnly(true);
  ui->end_amount->setReadOnly(true);
  ClearValues();
  this->setFixedSize(this->geometry().width(), this->geometry().height());
}

Deposit::~Deposit() { delete ui; }

void Deposit::SetValues(DepositCalculator::DepositResult result) {
  ui->end_amount->clear();
  ui->tax_amount->clear();
  ui->accrued_interest->clear();
  ui->deposit_table->clear();
  ui->end_amount->setText(
      QString::number(result.deposit_amount_by_end, 'd', 2));
  ui->tax_amount->setText(QString::number(result.tax_amount, 'd', 2));
  ui->accrued_interest->setText(
      QString::number(result.accrued_interest, 'd', 2));
}

void Deposit::ClearValues() {
  ui->end_amount->clear();
  ui->tax_amount->clear();
  ui->accrued_interest->clear();
  ui->deposit_table->clear();
  ui->rep_table->clear();
  ui->wit_table->clear();
  count_replenishment_ = -1;
  count_withdrawal_ = -1;
  replenishment_ = {};
  withdrawal_ = {};
}

void Deposit::on_clear_clicked() { ClearValues(); }

double Deposit::GetDepositAmount() { return ui->amount->text().toDouble(); }

int Deposit::GetDepositTerm() { return ui->deposit_term->value(); }

int Deposit::GetTypeTerm() { return ui->type_term->currentIndex(); }

double Deposit::GetInterestRate() {
  return ui->interest_rate->text().toDouble();
}

double Deposit::GetTaxRate() { return ui->tax_rate->text().toDouble(); }

int Deposit::GetPeriodicity() { return ui->periodicity->currentIndex(); }

Date Deposit::GetStartDate() {
  QDate temp = ui->start_date->date();
  return Date(temp.day(), temp.month(), temp.year());
}

bool Deposit::GetCapitalization() { return ui->capitalization->isChecked(); }

void Deposit::on_rep_add_clicked() {
  ++count_replenishment_;
  ui->rep_table->insertRow(count_replenishment_);
  QTableWidgetItem *dateItem =
      new QTableWidgetItem(ui->rep_date->date().toString());
  ui->rep_table->setItem(count_replenishment_, 0, dateItem);
  double amount = ui->rep_amount->text().toDouble();
  QTableWidgetItem *amountItem =
      new QTableWidgetItem(QString::number(amount, 'f', 2));
  ui->rep_table->setItem(count_replenishment_, 1, amountItem);
}

void Deposit::on_wit_add_clicked() {
  ++count_withdrawal_;
  ui->wit_table->insertRow(count_withdrawal_);
  QTableWidgetItem *dateItem =
      new QTableWidgetItem(ui->wit_date->date().toString());
  ui->wit_table->setItem(count_withdrawal_, 0, dateItem);
  double amount = ui->wit_amount->text().toDouble();
  QTableWidgetItem *amountItem =
      new QTableWidgetItem(QString::number(amount, 'f', 2));
  ui->wit_table->setItem(count_withdrawal_, 1, amountItem);
}

DepositCalculator::ChangeList &Deposit::GetReplenishment() {
  QDate date_temp = {};
  double number_temp = 0;
  for (int i = count_replenishment_; i >= 0; --i) {
    date_temp = QDate::fromString(ui->rep_table->item(i, 0)->text());
    number_temp = ui->rep_table->item(i, 1)->text().toDouble();
    replenishment_.insert(std::make_pair(
        Date(date_temp.day(), date_temp.month(), date_temp.year()),
        number_temp));
  }
  return replenishment_;
}

DepositCalculator::ChangeList &Deposit::GetWithdrawal() {
  QDate date_temp = {};
  double number_temp = 0;
  for (int i = count_withdrawal_; i >= 0; --i) {
    date_temp = QDate::fromString(ui->wit_table->item(i, 0)->text());
    number_temp = ui->wit_table->item(i, 1)->text().toDouble();
    withdrawal_.insert(std::make_pair(
        Date(date_temp.day(), date_temp.month(), date_temp.year()),
        number_temp));
  }
  return withdrawal_;
}

void Deposit::on_calculate_clicked() {
  DepositCalculator::DepositResult result =
      deposit_controller_->CalculateDeposit(
          GetDepositAmount(), GetStartDate(), GetDepositTerm(), GetTypeTerm(),
          GetInterestRate(), GetTaxRate(), GetPeriodicity(),
          GetCapitalization(), GetReplenishment(), GetWithdrawal());
  SetValues(result);
  std::vector<std::string> m = result.period_payment;
  auto it = m.begin();
  while (it != m.end()) {
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QString::fromStdString(*it));
    ui->deposit_table->addItem(item);
    ++it;
  }
}
