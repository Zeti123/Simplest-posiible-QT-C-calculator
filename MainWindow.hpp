#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "CalculatorModel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void onNumberClick(char num);
    void onClick(const QString& qs);

private:
    Ui::MainWindow *m_ui;
    CalculatorModel m_calc;
};
#endif // MAINWINDOW_HPP
