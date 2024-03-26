#ifndef MODEL_MAINCALCULATOR_H_
#define MODEL_MAINCALCULATOR_H_

#include <map>
#include <queue>
#include <regex>
#include <stack>
#include <string>

#include "token.h"

namespace s21 {
class MainCalculator {
 public:
  using CoordinatesXY = std::pair<std::vector<double>, std::vector<double>>;

  MainCalculator();
  ~MainCalculator() = default;

  void Calculator(const std::string& expression);
  double CalculateAnswer(const double& expression_x);
  double GetAnswer() const { return answer_; };

  void CalculateGraph(int amount_of_points, int x_min, int x_max, int y_min,
                      int y_max);
  CoordinatesXY& GetGraph() { return coordinates_; };

 private:
  double answer_;
  CoordinatesXY coordinates_;
  std::string raw_expression_;
  std::map<std::string, Token> token_map_;
  Token::func_punk operator_;

  std::queue<Token> infix_;
  std::queue<Token> postfix_;
  std::stack<Token> stack_;
  std::stack<double> result_stack_;

  void ExaminationExpression();
  void ReversePolishNotation();
  double PopTopStackResult();
  std::string ToLowercaseNoBlanks(const std::string str);
  std::string FindDigit(size_t& index);
  std::string FindFunction(size_t& index);
  bool FindUnary(size_t& index);
  void PushToken(std::string temp);
  void CheckLength(std::string expression);
};
}  // namespace s21

#endif  // MODEL_MAINCALCULATOR_H_
