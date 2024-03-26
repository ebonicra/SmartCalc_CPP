#include "depositcalculator.h"

void s21::DepositCalculator::CalculateDeposit(
    double deposit_amount, Date start_date, int deposit_term, int type_term,
    double interest_rate, double tax_rate, int periodicity, bool capitalization,
    ChangeList& replenisments, ChangeList& withdrawals) {
  result_ = {};
  double accruals = 0;
  double accruals_per = 0;
  deposit_ = deposit_amount;
  end_date_ = start_date;
  payment_date_ = start_date;
  result_.period_payment.push_back(ConvertAccrualsToString(
      start_date.ConvertDateToString(), "   -   ",
      std::to_string(deposit_amount), std::to_string(deposit_amount)));
  SetEndDate(deposit_term, type_term);
  AddReplenisments(replenisments, start_date, deposit_amount);
  AddWithdrawals(withdrawals, start_date, deposit_amount);
  SetNextPaymentDate(periodicity);
  start_date.Add(1, 0, 0);
  while (end_date_ >= start_date) {
    AddAccruedInterest(deposit_amount, interest_rate, start_date);
    if (start_date == payment_date_) {
      accruals_per = round(result_.accrued_interest * 100.) / 100.;
      if (capitalization)
        deposit_amount += accruals_per;
      else
        accruals += accruals_per;
      result_.accrued_interest = 0;
      SetNextPaymentDate(periodicity);
      result_.period_payment.push_back(ConvertAccrualsToString(
          start_date.ConvertDateToString(), std::to_string(accruals_per),
          "   -   ", std::to_string(deposit_amount)));
    }
    AddReplenisments(replenisments, start_date, deposit_amount);
    AddWithdrawals(withdrawals, start_date, deposit_amount);
    start_date.Add(1, 0, 0);
  }
  result_.accrued_interest = accruals + deposit_amount - deposit_;
  if (capitalization)
    result_.deposit_amount_by_end = deposit_amount;
  else
    result_.deposit_amount_by_end = deposit_amount + result_.accrued_interest;
  result_.tax_amount =
      round(((result_.accrued_interest) * tax_rate / 100.) * 100.) / 100.;
}

void s21::DepositCalculator::SetEndDate(int deposit_term, int type_term) {
  switch (type_term) {
    case kDays:
      end_date_.Add(deposit_term, 0, 0);
      break;
    case kMonths:
      end_date_.Add(0, deposit_term, 0);
      break;
    case kYears:
      end_date_.Add(0, 0, deposit_term);
      break;
  }
}

void s21::DepositCalculator::AddAccruedInterest(double deposit_amount,
                                                double interest_rate,
                                                Date start_date) {
  result_.accrued_interest +=
      deposit_amount * interest_rate / 100.0 / start_date.GetDayInYear();
}

void s21::DepositCalculator::AddReplenisments(ChangeList& replenisments,
                                              Date current_date,
                                              double& deposit_amount) {
  auto it = replenisments.find(current_date);
  if (it != replenisments.end()) {
    deposit_amount += it->second;
    deposit_ += it->second;
    result_.period_payment.push_back(ConvertAccrualsToString(
        current_date.ConvertDateToString(), "   -   ",
        std::to_string(it->second), std::to_string(deposit_amount)));
    replenisments.erase(it);
  }
}

void s21::DepositCalculator::AddWithdrawals(ChangeList& withdrawals,
                                            Date current_date,
                                            double& deposit_amount) {
  auto it = withdrawals.find(current_date);
  if (it != withdrawals.end()) {
    deposit_amount -= it->second;
    deposit_ -= it->second;
    result_.period_payment.push_back(ConvertAccrualsToString(
        current_date.ConvertDateToString(), "   -   ",
        std::to_string(it->second), std::to_string(deposit_amount)));
    withdrawals.erase(it);
  }
}

void s21::DepositCalculator::SetNextPaymentDate(int type_term) {
  switch (type_term) {
    case kDaily:
      payment_date_.Add(1, 0, 0);
      break;
    case kWeekly:
      payment_date_.Add(7, 0, 0);
      break;
    case kMonthly:
      payment_date_.Add(0, 1, 0);
      break;
    case kQuarterly:
      payment_date_.Add(0, 3, 0);
      break;
    case kHalfYear:
      payment_date_.Add(0, 6, 0);
      break;
    case kAnnually:
      payment_date_.Add(0, 0, 1);
      break;
    case kAtTheEnd:
      payment_date_ = end_date_;
      break;
  }
  if (payment_date_ >= end_date_) {
    payment_date_ = end_date_;
  }
}

std::string s21::DepositCalculator::ConvertAccrualsToString(
    const std::string& date, const std::string& separator,
    const std::string& interest, const std::string& amount) {
  std::ostringstream oss;
  oss << std::left << std::setw(15) << date << std::setw(20) << separator
      << std::setw(20) << interest << std::setw(20) << amount;
  return oss.str();
}
