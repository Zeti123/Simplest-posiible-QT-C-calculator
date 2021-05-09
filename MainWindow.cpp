#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    auto grid = m_ui->grid;
    for (int i = 0; i < grid->count(); i++)
    {
        auto o = grid->itemAt(i)->widget();
        auto button = dynamic_cast<QPushButton*>(o);
        if (button != nullptr && button->text()[0] >= '0' && button->text()[0] <= '9')
            connect(button, &QPushButton::clicked, this, [=](){ onNumberClick(button->text().toStdString()[0]); });
        else
            connect(button, &QPushButton::clicked, this, [=](){ onClick(button->text()); });
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onNumberClick(char num)
{
    std::string ans = m_calc.clickKey(static_cast<CalculatorModel::Key>(num - '0'));
    QString s = QString::fromUtf8(ans.c_str());;
    m_ui->label->setText(s);
}

void MainWindow::onClick(const QString& qs)
{
    std::string ans;
    if (qs == "C")
        ans = m_calc.clickKey(CalculatorModel::Key::K_CLEAR);
    if (qs == "+")
        ans = m_calc.clickKey(CalculatorModel::Key::K_SUM);
    if (qs == "-")
        ans = m_calc.clickKey(CalculatorModel::Key::K_SUB);
    if (qs == "×")
        ans = m_calc.clickKey(CalculatorModel::Key::K_MULT);
    if (qs == "/")
        ans = m_calc.clickKey(CalculatorModel::Key::K_DIV);
    if (qs == "=")
        ans = m_calc.clickKey(CalculatorModel::Key::K_EQUAL);

    QString s = QString::fromUtf8(ans.c_str());;
    m_ui->label->setText(s);
}

