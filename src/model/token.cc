#include "token.h"

s21::Token::Token(std::string name, token_type type, token_priority priority,
                  func_punk oper)
    : token_name_(name),
      token_type_(type),
      token_priority_(priority),
      token_operator_(oper) {}

std::string s21::Token::GetName() { return token_name_; }

s21::token_type s21::Token::GetType() { return token_type_; }

s21::token_priority s21::Token::GetPriority() { return token_priority_; }

std::function<double(double, double)> s21::Token::GetOperator() {
  return token_operator_;
}

void s21::MakeMapToken(std::map<std::string, s21::Token>& temp_map) {
  using namespace std;

  initializer_list<pair<const string, Token>> list = {
      {" ", Token(" ", kNumber, None, nullptr)},
      {"~", Token("~", kUnaryOperator, Highest, oper1arg(-))},
      {"x", Token("x", kNumber, None, nullptr)},
      {"(", Token("(", kOpenBracket, None, nullptr)},
      {")", Token(")", kCloseBracket, None, nullptr)},
      {"+", Token("+", kOperator, Low, oper2arg(+))},
      {"-", Token("-", kOperator, Low, oper2arg(-))},
      {"*", Token("*", kOperator, Medium, oper2arg(*))},
      {"/", Token("/", kOperator, Medium, oper2arg(/))},
      {"^", Token("^", kOperator, High, func2arg(pow))},
      {"mod", Token("mod", kOperator, High, func2arg(fmod))},
      {"cos", Token("cos", kFunction, High, func1arg(cos))},
      {"sin", Token("sin", kFunction, High, func1arg(sin))},
      {"tan", Token("tan", kFunction, High, func1arg(tan))},
      {"acos", Token("acos", kFunction, High, func1arg(acos))},
      {"asin", Token("asin", kFunction, High, func1arg(asin))},
      {"atan", Token("atan", kFunction, High, func1arg(atan))},
      {"sqrt", Token("sqrt", kFunction, High, func1arg(sqrt))},
      {"ln", Token("ln", kFunction, High, func1arg(log))},
      {"log", Token("log", kFunction, High, func1arg(log10))},
  };
  temp_map.insert(list);
}
