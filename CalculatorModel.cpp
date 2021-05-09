#include "CalculatorModel.hpp"

CalculatorModel::CalculatorModel()
    :m_state(State::EMPTY), m_leftNumber(""), m_rightNumber("0") {}

std::string CalculatorModel::clickKey(Key k)
{
    if (k == Key::K_CLEAR)
    {
        m_leftNumber = "";
        m_rightNumber = "0";
        m_state = State::EMPTY;
        return m_rightNumber;
    }

    if (m_state == State::EMPTY)
    {
        if (isNumber(k))
        {
            if (m_rightNumber == "0")
                m_rightNumber[0] = static_cast<uint8_t>(k) + '0';
            else
                m_rightNumber += static_cast<uint8_t>(k) + '0';
        }
        else if (isOperator(k))
        {
            m_actionKey = k;
            m_leftNumber = m_rightNumber;
            m_rightNumber = "0";
            m_state = State::ACTION;
        }
        else if (k == Key::K_EQUAL)
            m_state = State::RESULT;
    }
    else if (m_state == State::ACTION)
    {
        if (isNumber(k))
        {
            if (m_rightNumber == "0")
                m_rightNumber[0] = static_cast<uint8_t>(k) + '0';
            else
                m_rightNumber += static_cast<uint8_t>(k) + '0';
        }
        else if (isOperator(k))
        {
            m_leftNumber = performAction();
            m_actionKey = k;
            m_rightNumber = "0";
        }
        else if (k == Key::K_EQUAL)
        {
            m_rightNumber = performAction();
            m_leftNumber = "";
            m_state = State::RESULT;
        }
    }
    else if (m_state == State::RESULT)
    {
        if (isNumber(k))
        {
            m_rightNumber.resize(1);
            m_rightNumber[0] = static_cast<uint8_t>(k) + '0';
            m_state = State::EMPTY;
        }
        else if (isOperator(k))
        {
            m_leftNumber = m_rightNumber;
            m_rightNumber = "0";
            m_actionKey = k;
            m_state = State::ACTION;
        }
    }
    return m_rightNumber;
}

std::string CalculatorModel::performAction()
{
    std::string result;
    switch (m_actionKey)
    {
    case Key::K_SUM:
        result = numToStr(strToNum(m_leftNumber) + strToNum(m_rightNumber));
        break;
    case Key::K_SUB:
        result = numToStr(strToNum(m_leftNumber) - strToNum(m_rightNumber));
        break;
    case Key::K_MULT:
        result = numToStr(strToNum(m_leftNumber) * strToNum(m_rightNumber));
        break;
    case Key::K_DIV:
        result = numToStr(strToNum(m_leftNumber) / strToNum(m_rightNumber));
        break;
    default: break;
    }
    return result;
}

std::string CalculatorModel::getOutputLabel() const
{
    return m_rightNumber;
}

bool CalculatorModel::isNumber(Key k) const
{
    return (static_cast<uint8_t>(k) >= 0 && static_cast<uint8_t>(k) <= 9);
}

bool CalculatorModel::isOperator(Key k) const
{
    return (k == Key::K_SUM || k == Key::K_SUB || k == Key::K_MULT || k == Key::K_DIV);
}

std::string CalculatorModel::numToStr(int num)
{
    return std::to_string(num);
}

int CalculatorModel::strToNum(const std::string& str)
{
    return std::stoi(str);
}
