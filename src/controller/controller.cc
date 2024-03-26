#include "controller.h"

s21::Controller::Controller(MainCalculator* m, CreditCalculator* c,
                            DepositCalculator* d)
    : calculator_model_(m), credit_model_(c), deposit_model_(d) {}

double s21::Controller::CalculatorAnswer(std::string expression,
                                         double expression_x) {
  calculator_model_->Calculator(expression);
  return calculator_model_->CalculateAnswer(expression_x);
}

s21::MainCalculator::CoordinatesXY& s21::Controller::DrawGraph(
    std::string expression, int amount_of_points, double x_min, double x_max,
    double y_min, double y_max) {
  calculator_model_->Calculator(expression);
  calculator_model_->CalculateGraph(amount_of_points, x_min, x_max, y_min,
                                    y_max);
  return calculator_model_->GetGraph();
}

s21::CreditCalculator::CreditResult s21::Controller::CalculateCredit(
    double credit_amount, int period, double rate, bool type, Date start_date) {
  if (type) {
    credit_model_->CalculateAnnuityCredit(credit_amount, period, rate,
                                          start_date);
  } else {
    credit_model_->CalculateDifferentiatedCredit(credit_amount, period, rate,
                                                 start_date);
  }
  return credit_model_->GetResult();
}

s21::DepositCalculator::DepositResult s21::Controller::CalculateDeposit(
    double deposit_amount, Date start_date, int deposit_term, int type_term,
    double interest_rate, double tax_rate, int periodicity, bool capitalization,
    DepositCalculator::ChangeList& replenisments,
    DepositCalculator::ChangeList& withdrawals) {
  deposit_model_->CalculateDeposit(
      deposit_amount, start_date, deposit_term, type_term, interest_rate,
      tax_rate, periodicity, capitalization, replenisments, withdrawals);
  return deposit_model_->GetResult();
}
