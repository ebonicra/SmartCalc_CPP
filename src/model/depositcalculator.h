#ifndef MODEL_DEPOSITCALCULATOR_H_
#define MODEL_DEPOSITCALCULATOR_H_

#include <cmath>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "date.h"

namespace s21 {

enum periodicity {
  kDaily,
  kWeekly,
  kMonthly,
  kQuarterly,
  kHalfYear,
  kAnnually,
  kAtTheEnd
};
enum DateType { kDays, kMonths, kYears };

class DepositCalculator {
 public:
  using ChangeList = std::map<Date, double>;
  typedef struct {
    double accrued_interest;
    double tax_amount;
    double deposit_amount_by_end;
    std::vector<std::string> period_payment;
  } DepositResult;

  DepositCalculator() = default;
  ~DepositCalculator() = default;

  void CalculateDeposit(double deposit_amount, Date start_date,
                        int deposit_term, int type_term, double interest_rate,
                        double tax_rate, int periodicity, bool capitalization,
                        ChangeList& replenisments, ChangeList& withdrawals);
  DepositResult GetResult() { return result_; };

 private:
  void SetEndDate(int deposit_term, int type_term);
  void SetNextPaymentDate(int type_term);
  void CheckPaymentDate(double& payment_date, double& current_date);
  void AddAccruedInterest(double deposit_amount, double interest_rate,
                          Date start_date);
  void AddReplenisments(ChangeList& replenisments, Date current_date,
                        double& deposit_amount);
  void AddWithdrawals(ChangeList& withdrawals, Date current_date,
                      double& deposit_amount);
  std::string ConvertAccrualsToString(const std::string& date,
                                      const std::string& separator,
                                      const std::string& interest,
                                      const std::string& amount);
  Date end_date_;
  Date payment_date_;
  double deposit_;
  DepositResult result_;
};

}  // namespace s21

#endif  // MODEL_DEPOSITCALCULATOR_H_
