#include <gtest/gtest.h>

#include "../model/creditcalculator.h"
#include "../model/depositcalculator.h"
#include "../model/maincalculator.h"

#define kAcc 1e-6

TEST(calculation, kek_add) {
  s21::MainCalculator calc;
  calc.Calculator("8+3");
  ASSERT_NEAR(calc.CalculateAnswer(0), 11, kAcc);
}

TEST(calculation, add) {
  s21::MainCalculator calc;
  calc.Calculator("5.53234+1032.42342");
  ASSERT_NEAR(calc.CalculateAnswer(0), 1037.95576, kAcc);
}

TEST(calculation, sum) {
  s21::MainCalculator calc;
  calc.Calculator("1037.95576-234.234");
  ASSERT_NEAR(calc.CalculateAnswer(0), 803.72176, kAcc);
}

TEST(calculation, mul) {
  s21::MainCalculator calc;
  calc.Calculator("803.72176*423.234");
  ASSERT_NEAR(calc.CalculateAnswer(0), 340162.375372, kAcc);
}

TEST(calculation, div) {
  s21::MainCalculator calc;
  calc.Calculator("340162.375372/342.32");
  ASSERT_NEAR(calc.CalculateAnswer(0), 993.697053552, kAcc);
}

TEST(calculation, mod) {
  s21::MainCalculator calc;
  calc.Calculator("993.697053552mod423.234");
  ASSERT_NEAR(calc.CalculateAnswer(0), 147.229053552, kAcc);
}

TEST(calculation, parenthesis) {
  s21::MainCalculator calc;
  calc.Calculator("423.23*(23-4.3)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 7914.401, kAcc);
}

TEST(calculation, sin) {
  s21::MainCalculator calc;
  calc.Calculator("sin(54.5)");
  ASSERT_NEAR(calc.CalculateAnswer(0), -0.88797583833, kAcc);
}

TEST(calculation, cos) {
  s21::MainCalculator calc;
  calc.Calculator("cos(32.32)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 0.61841396583, kAcc);
}

TEST(calculation, tan) {
  s21::MainCalculator calc;
  calc.Calculator("tan(34.23)");
  ASSERT_NEAR(calc.CalculateAnswer(0), -0.33975534786, kAcc);
}

TEST(calculation, log) {
  s21::MainCalculator calc;
  calc.Calculator("log(23.23)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 1.3660492098, kAcc);
}

TEST(calculation, ln) {
  s21::MainCalculator calc;
  calc.Calculator("ln(48.234)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 3.87606416657, kAcc);
}

TEST(calculation, sqrt) {
  s21::MainCalculator calc;
  calc.Calculator("sqrt(423)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 20.5669638012, kAcc);
}

TEST(calculation, asin) {
  s21::MainCalculator calc;
  calc.Calculator("asin(0.324)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 0.329954518, kAcc);
}

TEST(calculation, acos) {
  s21::MainCalculator calc;
  calc.Calculator("acos(0.324)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 1.24084181, kAcc);
}

TEST(calculation, atan) {
  s21::MainCalculator calc;
  calc.Calculator("atan(-0.324)");
  ASSERT_NEAR(calc.CalculateAnswer(0), -0.313327168, kAcc);
}

TEST(calculation, pow) {
  s21::MainCalculator calc;
  calc.Calculator("423.32^(2.432^(1/5))");
  ASSERT_NEAR(calc.CalculateAnswer(0), 1372.787322, kAcc);
}

TEST(calculation, expression_1) {
  s21::MainCalculator calc;
  calc.Calculator("cos(sin(3.14))");
  ASSERT_NEAR(calc.CalculateAnswer(0), 0.999998, kAcc);
}

TEST(calculation, expression_2) {
  s21::MainCalculator calc;
  calc.Calculator("(cos(sin(3.14))+3.12)^-5.14e-3");
  ASSERT_NEAR(calc.CalculateAnswer(0), 0.9927489, kAcc);
}

TEST(calculation, expression_3) {
  s21::MainCalculator calc;
  calc.Calculator("sqrt(cos(sin(3.14))+3.12)^-5.14e-3");
  ASSERT_NEAR(calc.CalculateAnswer(0), 0.9963678, kAcc);
}

TEST(calculation, expression_5) {
  s21::MainCalculator calc;
  calc.Calculator("(-(-(+(+5))))");
  ASSERT_NEAR(calc.CalculateAnswer(0), 5, kAcc);
}

TEST(calculation, expression_6) {
  s21::MainCalculator calc;
  calc.Calculator("0^(-1)");
  ASSERT_DOUBLE_EQ(calc.CalculateAnswer(0), INFINITY);
}

TEST(calculation, expression_7) {
  s21::MainCalculator calc;
  calc.Calculator("2^(3+4*5)*(2*2)+2+6/3");
  ASSERT_NEAR(calc.CalculateAnswer(0), 33554436, kAcc);
}

TEST(calculation, expression_8) {
  s21::MainCalculator calc;
  calc.Calculator("sin(2-1)*2^2+6^2*2");
  ASSERT_NEAR(calc.CalculateAnswer(0), 75.365883939231579, kAcc);
}

TEST(calculation, expression_9) {
  s21::MainCalculator calc;
  calc.Calculator("(-(-(-5)))*(-(-5))");
  ASSERT_NEAR(calc.CalculateAnswer(0), -25, kAcc);
}

TEST(calculation, expression_10) {
  s21::MainCalculator calc;
  calc.Calculator("-2^(3+4*5)*(2*2)+2+6/3");
  ASSERT_NEAR(calc.CalculateAnswer(0), -33554428, kAcc);
}

TEST(calculation, expression_11) {
  s21::MainCalculator calc;
  calc.Calculator("56+21-376+(56-22)-(13+10)+(11+(7-(3+2)))");
  ASSERT_NEAR(calc.CalculateAnswer(0), -275, kAcc);
}

TEST(calculation, expression_12) {
  s21::MainCalculator calc;
  calc.Calculator("tan(10)*((5-3)*ln(4)-log(8))*2+7");
  ASSERT_NEAR(calc.CalculateAnswer(0), 9.4242194938376841, kAcc);
}

TEST(calculation, expression_13) {
  s21::MainCalculator calc;
  calc.Calculator(
      "((-(-356.081*4598.63)*803.928*(70.592*(-0.1569))*(-36.1566)))");
  ASSERT_NEAR(calc.CalculateAnswer(0), 527181836601.876000, 1);
}

TEST(calculation, expression_15) {
  s21::MainCalculator calc;
  calc.Calculator("2^(3^4)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 2417851639229258349412352.0, kAcc);
}

TEST(calculation, expression_16) {
  s21::MainCalculator calc;
  calc.Calculator("sin(x+cos(x^x))*tan(x)");
  ASSERT_NEAR(calc.CalculateAnswer(1), 1.5566836754802069187064716, kAcc);
}

TEST(calculation, expression_17) {
  s21::MainCalculator calc;
  calc.Calculator("asin(x+1)+acos(x)-atan(2)");
  ASSERT_NEAR(calc.CalculateAnswer(-0.60), 1.518665563861578471360758, kAcc);
}

TEST(calculation, expression_18) {
  s21::MainCalculator calc;
  calc.Calculator("sqrt(8965)+ln(56253)-log(965)");
  ASSERT_NEAR(calc.CalculateAnswer(0), 102.636771255135727187735, kAcc);
}

TEST(calculation, expression_19) {
  s21::MainCalculator calc;
  calc.Calculator("5.3+8.6-sin(x*1.6-5)/0.5");
  ASSERT_NEAR(calc.CalculateAnswer(-0.60), 13.26482286785592989986, kAcc);
}

TEST(calculation, expression_20) {
  s21::MainCalculator calc;
  calc.Calculator("x");
  ASSERT_NEAR(calc.CalculateAnswer(-0.60), -0.60, kAcc);
}

TEST(calculation, expression_23) {
  s21::MainCalculator calc;
  calc.Calculator("x");
  ASSERT_NEAR(calc.CalculateAnswer(-1), -1, kAcc);
}

TEST(calculation, expression_25) {
  s21::MainCalculator calc;
  calc.Calculator("1/0");
  ASSERT_TRUE(std::isinf(calc.CalculateAnswer(0)));
}

TEST(calculation, expression_26) {
  s21::MainCalculator calc;
  calc.Calculator("-1/0");
  ASSERT_TRUE(std::isinf(calc.CalculateAnswer(0)));
}

TEST(calculation_graph, expression) {
  using namespace s21;
  MainCalculator calc;
  calc.Calculator("x*x");
  calc.CalculateGraph(10, 0, 10, 0, 100);
  MainCalculator::CoordinatesXY result = calc.GetGraph();
  std::vector<double> expected_x = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<double> expected_y = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
  ASSERT_TRUE((result.first == expected_x) && (result.second == expected_y));
}

TEST(credit, ann) {
  s21::CreditCalculator calc;
  calc.CalculateAnnuityCredit(123456, 120, 4.56, s21::Date(05, 10, 2023));
  ASSERT_NEAR(calc.GetResult().total_payment, 153966.24, 1e-2);
  ASSERT_NEAR(calc.GetResult().overpayment, 30510.24, 1e-2);
  ASSERT_NEAR(calc.GetResult().payment, 1283.05, 1e-2);
}

TEST(credit, diff) {
  s21::CreditCalculator calc;
  calc.CalculateDifferentiatedCredit(100000, 6, 12.5, s21::Date(05, 10, 2023));
  ASSERT_NEAR(calc.GetResult().total_payment, 103661.55, 1e-2);
  ASSERT_NEAR(calc.GetResult().overpayment, 3661.55, 1e-2);
}

TEST(deposit, test1) {
  using namespace s21;
  DepositCalculator calc;
  DepositCalculator::ChangeList ReplenishmentsList;
  ReplenishmentsList.insert(std::make_pair(Date(8, 10, 2023), 20000.00));
  ReplenishmentsList.insert(std::make_pair(Date(8, 12, 2023), 60000.00));
  DepositCalculator::ChangeList PartialWithdrawalsList;
  PartialWithdrawalsList.insert(std::make_pair(Date(29, 10, 2025), 300000.00));
  PartialWithdrawalsList.insert(std::make_pair(Date(30, 03, 2028), 30000.00));

  calc.CalculateDeposit(1000000, Date(7, 10, 2023), 12, 2, 5.3, 0.0, 2, 1,
                        ReplenishmentsList, PartialWithdrawalsList);

  ASSERT_NEAR(calc.GetResult().deposit_amount_by_end, 1484028.60, kAcc);
  ASSERT_NEAR(calc.GetResult().accrued_interest, 734028.60, kAcc);
  ASSERT_NEAR(calc.GetResult().tax_amount, 0.0, kAcc);
}

TEST(deposit, test2) {
  using namespace s21;
  DepositCalculator calc;
  DepositCalculator::ChangeList ReplenishmentsList;
  DepositCalculator::ChangeList PartialWithdrawalsList;
  calc.CalculateDeposit(2000, Date(6, 10, 2023), 99, 0, 8.0, 0.0, 0, 1,
                        ReplenishmentsList, PartialWithdrawalsList);
  ASSERT_NEAR(calc.GetResult().deposit_amount_by_end, 2043.86, kAcc);
  ASSERT_NEAR(calc.GetResult().accrued_interest, 43.86, kAcc);
  ASSERT_NEAR(calc.GetResult().tax_amount, 0.0, kAcc);
}

TEST(deposit, test3) {
  using namespace s21;
  DepositCalculator calc;
  DepositCalculator::ChangeList ReplenishmentsList;
  ReplenishmentsList.insert(std::make_pair(Date(2, 03, 2024), 50000));
  ReplenishmentsList.insert(std::make_pair(Date(2, 04, 2024), 50000));
  ReplenishmentsList.insert(std::make_pair(Date(2, 05, 2024), 50000));
  DepositCalculator::ChangeList PartialWithdrawalsList;
  PartialWithdrawalsList.insert(std::make_pair(Date(31, 12, 2025), 30000.00));
  calc.CalculateDeposit(200000, Date(1, 11, 2023), 5, 2, 6.20, 4.25, 3, 0,
                        ReplenishmentsList, PartialWithdrawalsList);
  ASSERT_NEAR(calc.GetResult().deposit_amount_by_end, 419351.25, kAcc);
  ASSERT_NEAR(calc.GetResult().accrued_interest, 99351.25, kAcc);
  ASSERT_NEAR(calc.GetResult().tax_amount, 4222.43, kAcc);
}

TEST(logic_error, incorrect_symbol) {
  s21::MainCalculator calc;
  ASSERT_ANY_THROW(calc.Calculator("2 + $"));
}

TEST(logic_error, incorrect_function_name) {
  s21::MainCalculator calc;
  ASSERT_ANY_THROW(calc.Calculator("2+ sinus(5)"));
}

TEST(logic_error, fail_2) {
  s21::MainCalculator calc;
  ASSERT_ANY_THROW(calc.Calculator("2.5.4 + 6"));
}

TEST(logic_error, fail_3) {
  s21::MainCalculator calc;
  ASSERT_ANY_THROW(calc.Calculator("s"));
}

TEST(logic_error, fail_4) {
  s21::MainCalculator calc;
  calc.Calculator("cos()");
  ASSERT_ANY_THROW(calc.CalculateAnswer(0));
}

TEST(logic_error, fail_5) {
  s21::MainCalculator calc;
  calc.Calculator("2*1+--5");
  ASSERT_ANY_THROW(calc.CalculateAnswer(0));
}

TEST(logic_error, fail_6) {
  s21::MainCalculator calc;
  calc.Calculator("(2-6");
  ASSERT_ANY_THROW(calc.CalculateAnswer(0));
}

TEST(logic_error, fail_7) {
  s21::MainCalculator calc;
  ASSERT_ANY_THROW(calc.Calculator("sqrtd2"));
}

TEST(logic_error, fail_8) {
  s21::MainCalculator calc;
  calc.Calculator("22+7 (5) 4");
  ASSERT_ANY_THROW(calc.CalculateAnswer(0));
}

TEST(logic_error, fail_9) {
  s21::MainCalculator calc;
  calc.Calculator("100+2+");
  ASSERT_ANY_THROW(calc.CalculateAnswer(0));
}

TEST(logic_error, fail_10) {
  s21::MainCalculator calc;
  calc.Calculator("*");
  ASSERT_ANY_THROW(calc.CalculateAnswer(0));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  free(__cxxabiv1::__cxa_get_globals());
  return RUN_ALL_TESTS();
}
