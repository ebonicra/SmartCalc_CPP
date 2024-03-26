#include "creditcalculator.h"

void s21::CreditCalculator::CalculateAnnuityCredit(double amount, int period,
                                                   double rate,
                                                   Date start_date) {
  credit_result_ = {};
  rate = rate / (100 * 12);
  credit_result_.payment = amount * (rate / (1 - pow((1 + rate), -period)));
  for (int i = 0; i < period; ++i) {
    credit_result_.monthly_payment.push_back(
        ConvertAccrualsToString(start_date.ConvertDateToString(),
                                std::to_string(credit_result_.payment)));
    start_date.Add(0, 1, 0);
  }
  credit_result_.total_payment = period * credit_result_.payment;
  credit_result_.overpayment = credit_result_.total_payment - amount;
}

void s21::CreditCalculator::CalculateDifferentiatedCredit(double amount,
                                                          int period,
                                                          double rate,
                                                          Date start_date) {
  credit_result_ = {};
  double remainder = amount;
  double debt_payment = amount / (double)period;
  double interest_payment = 0;
  double every_payment = 0;
  for (int i = 0; i < period; ++i) {
    interest_payment = (remainder * rate * start_date.GetDayInMonth()) /
                       (double)start_date.GetDayInYear() / 100;
    every_payment = debt_payment + interest_payment;
    credit_result_.monthly_payment.push_back(ConvertAccrualsToString(
        start_date.ConvertDateToString(), std::to_string(every_payment)));
    remainder -= debt_payment;
    credit_result_.total_payment += every_payment;
    start_date.Add(0, 1, 0);
  }
  credit_result_.overpayment = credit_result_.total_payment - amount;
}

std::string s21::CreditCalculator::ConvertAccrualsToString(
    const std::string& date, const std::string& amount) {
  std::ostringstream oss;
  oss << std::left << std::setw(15) << date << std::setw(20) << amount;
  return oss.str();
}
