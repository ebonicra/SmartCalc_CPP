#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include <iostream>
#include <vector>

#include "../model/creditcalculator.h"
#include "../model/depositcalculator.h"
#include "../model/maincalculator.h"

namespace s21 {

class Controller {
 public:
  Controller(MainCalculator *m, CreditCalculator *c, DepositCalculator *d);
  ~Controller() = default;

  double CalculatorAnswer(std::string expression, double expression_x);
  MainCalculator::CoordinatesXY &DrawGraph(std::string expression,
                                           int amount_of_points, double x_min,
                                           double x_max, double y_min,
                                           double y_max);

  CreditCalculator::CreditResult CalculateCredit(double credit_amount,
                                                 int period, double rate,
                                                 bool type, Date start_date);

  DepositCalculator::DepositResult CalculateDeposit(
      double deposit_amount, Date start_date, int deposit_term, int type_term,
      double interest_rate, double tax_rate, int periodicity,
      bool capitalization, DepositCalculator::ChangeList &replenisments,
      DepositCalculator::ChangeList &withdrawals);

 private:
  MainCalculator *calculator_model_;
  CreditCalculator *credit_model_;
  DepositCalculator *deposit_model_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_
