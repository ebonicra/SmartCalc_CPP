#ifndef MODEL_CREDIRCALCULATOR_H_
#define MODEL_CREDIRCALCULATOR_H_

#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "date.h"

namespace s21 {
class CreditCalculator {
 public:
  typedef struct {
    double payment;
    double overpayment;
    double total_payment;
    std::vector<std::string> monthly_payment;
  } CreditResult;

  CreditCalculator() = default;
  ~CreditCalculator() = default;

  void CalculateAnnuityCredit(double amount, int period, double rate,
                              Date start_date);
  void CalculateDifferentiatedCredit(double amount, int period, double rate,
                                     Date start_date);
  CreditResult GetResult() { return credit_result_; };

 private:
  CreditResult credit_result_;
  std::string ConvertAccrualsToString(const std::string& date,
                                      const std::string& amount);
};
}  // namespace s21

#endif  // MODEL_CREDIRCALCULATOR_H_
