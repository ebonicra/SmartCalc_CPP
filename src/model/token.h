#ifndef MODEL_TOKEN_H_
#define MODEL_TOKEN_H_

#include <cmath>
#include <functional>
#include <map>
#include <string>

namespace s21 {

#define oper1arg(SIGN) [](double a, double b = 0) -> double { return b - a; }
#define oper2arg(SIGN) [](double a, double b) -> double { return a SIGN b; }
#define func1arg(SIGN) \
  [](double a, double b = 0) -> double { return SIGN(b + a); }
#define func2arg(SIGN) [](double a, double b) -> double { return SIGN(a, b); }

enum token_type {
  kNumber,
  kFunction,
  kOperator,
  kUnaryOperator,
  kOpenBracket,
  kCloseBracket
};

enum token_priority { None, Low, Medium, High, Highest };

class Token {
 public:
  using func_punk = std::function<double(double, double)>;

  Token() = default;
  Token(std::string name, token_type type, token_priority priority,
        func_punk oper);
  ~Token() = default;

  std::string GetName();
  token_type GetType();
  token_priority GetPriority();
  func_punk GetOperator();

 private:
  std::string token_name_;
  token_type token_type_;
  token_priority token_priority_;
  func_punk token_operator_;
};

void MakeMapToken(std::map<std::string, s21::Token>& temp_map);

}  // namespace s21

#endif  // TOKEN_H_
