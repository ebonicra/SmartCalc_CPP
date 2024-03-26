#include "maincalculator.h"

s21::MainCalculator::MainCalculator() { MakeMapToken(token_map_); }

void s21::MainCalculator::Calculator(const std::string &expression) {
  CheckLength(expression);
  raw_expression_ = ToLowercaseNoBlanks(expression);
  ExaminationExpression();
  ReversePolishNotation();
}

void s21::MainCalculator::ExaminationExpression() {
  infix_ = {};
  for (size_t i = 0; i < raw_expression_.size();) {
    if (std::isdigit(raw_expression_[i])) {
      std::string digit = FindDigit(i);
      infix_.push(Token(digit, kNumber, None, nullptr));
    } else if (raw_expression_[i] == 'x') {
      infix_.push(Token("x", kNumber, None, nullptr));
      ++i;
    } else if (std::isalpha(raw_expression_[i])) {
      std::string func = FindFunction(i);
      PushToken(func);
    } else {
      if (!FindUnary(i)) {
        std::string temp{raw_expression_[i]};
        PushToken(temp);
        ++i;
      }
    }
  }
}

void s21::MainCalculator::ReversePolishNotation() {
  postfix_ = {};
  stack_ = {};
  while (!infix_.empty()) {
    switch (infix_.front().GetType()) {
      case kOpenBracket:
        stack_.push(infix_.front());
        break;
      case kCloseBracket:
        while (!stack_.empty() && stack_.top().GetType() != kOpenBracket) {
          postfix_.push(stack_.top());
          stack_.pop();
        }
        if (!stack_.empty() && stack_.top().GetType() == kOpenBracket)
          stack_.pop();
        else
          throw std::logic_error("The open bracket got lost!");
        break;
      case kOperator:
      case kUnaryOperator:
        while (!stack_.empty() &&
               stack_.top().GetPriority() >= infix_.front().GetPriority()) {
          postfix_.push(stack_.top());
          stack_.pop();
        }
        stack_.push(infix_.front());
        break;
      case kFunction:
        stack_.push(infix_.front());
        break;
      case kNumber:
        postfix_.push(infix_.front());
        if (!stack_.empty() && stack_.top().GetName() == "~") {
          postfix_.push(stack_.top());
          stack_.pop();
        }
        break;
    }
    infix_.pop();
  }
  while (!stack_.empty()) {
    postfix_.push(stack_.top());
    stack_.pop();
  }
}

double s21::MainCalculator::CalculateAnswer(const double &expression_x) {
  double result = 0, a = 0, b = 0;
  result_stack_ = {};
  while (!postfix_.empty()) {
    switch (postfix_.front().GetType()) {
      case kNumber:
        if (postfix_.front().GetName() == "x") {
          result_stack_.push(expression_x);
        } else {
          result_stack_.push(std::stod(postfix_.front().GetName()));
        }
        break;
      case kOperator:
        b = PopTopStackResult();
        a = PopTopStackResult();
        operator_ = postfix_.front().GetOperator();
        result_stack_.push(operator_(a, b));
        break;
      case kUnaryOperator:
      case kFunction:
        a = PopTopStackResult();
        operator_ = postfix_.front().GetOperator();
        result_stack_.push(operator_(a, 0));
        break;
      case kOpenBracket:
        throw std::logic_error("Incorrect input!");
        break;
      default:
        break;
    }
    postfix_.pop();
  }
  if (result_stack_.empty()) {
    throw std::logic_error("Incorrect input!");
  } else {
    result = result_stack_.top();
    result_stack_.pop();
    if (!result_stack_.empty()) {
      throw std::logic_error("Incorrect input!");
    }
    answer_ = result;
    return result;
  }
}

double s21::MainCalculator::PopTopStackResult() {
  if (result_stack_.empty()) {
    throw std::logic_error("Incorrect input!");
  }
  double result = result_stack_.top();
  result_stack_.pop();
  return result;
}

void s21::MainCalculator::CheckLength(std::string str) {
  if (str.size() > 255) throw std::invalid_argument("Expression too big!");
  if (str.size() == 0) throw std::invalid_argument("Expression too small!");
}

std::string s21::MainCalculator::ToLowercaseNoBlanks(const std::string str) {
  std::string result;
  for (size_t i = 0; i < str.size(); ++i) {
    if (std::isblank(str[i])) {
      continue;
    } else {
      result.push_back(tolower(str[i]));
    }
  }
  return result;
}

std::string s21::MainCalculator::FindDigit(size_t &index) {
  std::regex r("\\d+(([.]\\d+)?(e([+-])?\\d+)?)?");
  std::sregex_iterator i = std::sregex_iterator(raw_expression_.begin() + index,
                                                raw_expression_.end(), r);
  std::smatch match = *i;
  index += match.length();
  return match.str();
}

std::string s21::MainCalculator::FindFunction(size_t &index) {
  std::regex r("([a-z]+)");
  std::sregex_iterator i = std::sregex_iterator(raw_expression_.begin() + index,
                                                raw_expression_.end(), r);
  std::smatch match = *i;
  index += match.length();
  return match.str();
}

bool s21::MainCalculator::FindUnary(size_t &index) {
  if ((raw_expression_[index] == '-' || raw_expression_[index] == '+') &&
      (index == 0 || raw_expression_[index - 1] == '(' ||
       raw_expression_[index - 1] == '^')) {
    if (raw_expression_[index] == '-') {
      PushToken("~");
    }
    ++index;
    return true;
  }
  return false;
}

void s21::MainCalculator::PushToken(std::string temp) {
  auto it = token_map_.find(temp);
  if (it != token_map_.end()) {
    infix_.push(it->second);
  } else {
    throw std::logic_error("Incorrect symbol: " + temp);
  }
}

void s21::MainCalculator::CalculateGraph(int amount_of_points, int x_min,
                                         int x_max, int y_min, int y_max) {
  std::vector<double> x, y;
  infix_ = postfix_;
  double step = (x_max - x_min) / double(amount_of_points);
  for (double i = x_min; i <= x_max; i += step) {
    x.push_back(i);
    double res = CalculateAnswer(i);
    if (res > y_max || res < y_min) {
      y.push_back(std::numeric_limits<double>::quiet_NaN());
    } else {
      y.push_back(res);
    }
    postfix_ = infix_;
  }
  coordinates_ = std::make_pair(x, y);
}
