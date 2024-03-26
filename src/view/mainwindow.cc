#include "mainwindow.h"

#include "ui_mainwindow.h"

using namespace s21;

MainWindow::MainWindow(Controller *c) : ui(new Ui::MainWindow), controller_(c) {
  ui->setupUi(this);
  ui->main_line->installEventFilter(this);
  connect(ui->buttonGroup, &QButtonGroup::buttonClicked, this,
          &MainWindow::button);
  this->setFixedSize(this->geometry().width(), this->geometry().height());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_main_line_textEdited(const QString &arg1) {
  expression = arg1;
}

void MainWindow::button(QAbstractButton *btn) {
  QString buttonnayStr = btn->text();
  expression += buttonnayStr;
  if (buttonnayStr[0] == 'c' || buttonnayStr[0] == 's' ||
      buttonnayStr[0] == 't' || buttonnayStr[0] == 'a' ||
      buttonnayStr[0] == 'l') {
    expression += '(';
  }
  ui->main_line->setText(expression);
}

void MainWindow::on_smallClean_but_clicked() {
  QString tmp_str;
  for (int i = 0; i < expression.length() - 1; i++) {
    tmp_str += expression[i];
  }
  expression.clear();
  for (int i = 0; i < tmp_str.length(); i++) {
    expression += tmp_str[i];
  }
  ui->main_line->setText(expression);
}

void MainWindow::on_bigClean_but_clicked() {
  expression.clear();
  ui->main_line->setText(expression);
}

double MainWindow::GetXValue() { return ui->x_value->text().toDouble(); }

void MainWindow::on_enter_but_clicked() {
  try {
    std::string exp = ui->main_line->text().toStdString();
    double result = controller_->CalculatorAnswer(exp, GetXValue());
    expression.clear();
    expression = QString::number(result, 'g', 15);
    ui->main_line->setText(expression);
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Warning", e.what());
  }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
  if (obj == ui->main_line && event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
      on_enter_but_clicked();
      return true;
    }
  }
  return QObject::eventFilter(obj, event);
}

void MainWindow::on_graph_but_clicked() {
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  try {
    std::string exp = ui->main_line->text().toStdString();
    MainCalculator::CoordinatesXY &coordinates = controller_->DrawGraph(
        exp, GetAmountOfpoints(), GetXMin(), GetXMax(), GetYMin(), GetYMax());
    QVector<double> x(coordinates.first.begin(), coordinates.first.end());
    QVector<double> y(coordinates.second.begin(), coordinates.second.end());
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->xAxis->setRange(GetXMin(), GetXMax());
    ui->widget->yAxis->setRange(GetYMin(), GetYMax());
    ui->widget->replot();
  } catch (const std::exception &e) {
    QMessageBox::critical(this, "Warning", e.what());
  }
}

int MainWindow::GetXMin() { return ui->Xmin->text().toInt(); }

int MainWindow::GetXMax() { return ui->Xmax->text().toInt(); }

int MainWindow::GetYMin() { return ui->Ymin->text().toInt(); }

int MainWindow::GetYMax() { return ui->Ymax->text().toInt(); }

int MainWindow::GetAmountOfpoints() {
  return ui->amount_of_points->text().toInt();
}

void MainWindow::on_credit_but_clicked() {
  Credit credit_window(nullptr, controller_);
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_deposit_but_clicked() {
  Deposit deposit_window(nullptr, controller_);
  deposit_window.setModal(true);
  deposit_window.exec();
}
