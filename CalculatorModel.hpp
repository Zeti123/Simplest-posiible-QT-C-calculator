#ifndef CALCULATORMODEL_HPP
#define CALCULATORMODEL_HPP

#include<string>

class CalculatorModel
{   
public:
    enum class Key: uint8_t
    {
        K_0 = 0, K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9,
        K_SUM, K_SUB, K_MULT, K_DIV, K_EQUAL, K_CLEAR
    };

public:
    CalculatorModel();
    /* returns output label */
    std::string clickKey(Key k);

    /* returns output label */
    std::string getOutputLabel() const;

private:
    enum class State
    {
        EMPTY,
        ACTION,
        RESULT
    };

private:
    bool isNumber(Key k) const;
    bool isOperator(Key k) const;

private:
    /* returns calculation result */
    std::string performAction();
    std::string numToStr(int num);
    int strToNum(const std::string& str);

    State m_state;
    std::string m_leftNumber;
    std::string m_rightNumber;
    Key m_actionKey;
};

#endif // CALCULATORMODEL_HPP
