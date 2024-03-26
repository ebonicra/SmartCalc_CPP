#ifndef MODEL_DATE_H
#define MODEL_DATE_H

#include <string>

namespace s21 {

class Date {
 public:
  Date() = default;
  Date(int day, int month, int year);
  ~Date() = default;

  int GetDayInMonth();
  int GetDayInYear();
  void SetDate(int day, int month, int year);
  void Add(int days, int months, int years);
  bool operator==(const Date& o) const;
  bool operator>(const Date& o) const;
  bool operator>=(const Date& o) const;
  bool operator<(const Date& o) const;

  int GetDay() { return day_; };
  int GetMonth() { return month_; }
  int GetYear() { return year_; };
  std::string ConvertDateToString();

 private:
  int day_;
  int month_;
  int year_;
};

}  // namespace s21

#endif
