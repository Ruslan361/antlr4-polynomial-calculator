#include <iostream>
#include <stack> 
#include "CalculatorInterpreter.h"
namespace antlrcpptest{

void CalculatorInterpreter::exitPlusOp(  TParser::PlusOpContext *ctx) {
    auto r = pol_stack.top(); pol_stack.pop();
    auto l = pol_stack.top(); pol_stack.pop();
    pol_stack.push(l+r);
}

void CalculatorInterpreter::exitBinaryMinusOp(  TParser::BinaryMinusOpContext *ctx) {
    auto r = pol_stack.top(); pol_stack.pop();
    auto l = pol_stack.top(); pol_stack.pop();
    pol_stack.push(l-r);
}

void CalculatorInterpreter::exitUnaryMinusOp(  TParser::UnaryMinusOpContext *ctx) {
    pol_stack.top() = pol_stack.top() * (-1);
}


void CalculatorInterpreter::exitMultOp(  TParser::MultOpContext *ctx) {
    auto r = pol_stack.top(); pol_stack.pop();
    auto l = pol_stack.top(); pol_stack.pop();
    pol_stack.push(l*r);
}
void CalculatorInterpreter::exitSetValue(TParser::SetValueContext *ctx)
{
    //std::cout << ctx->getText() << std::endl;
    Polynom<int> current = pol_stack.top();
    std::string var_name = var_stack.top();
    std::pair<std::string, Polynom<int>> pair(var_name, current);
    variables.erase(var_name);
    variables.insert(pair);
    pol_stack.pop();
    var_stack.pop();
}

void CalculatorInterpreter::exitGetValue(TParser::GetValueContext *ctx)
{
    std::string var_name = var_stack.top();
    var_stack.pop();
    try{
    Polynom<int> current = variables.at(var_name);
    pol_stack.push(current);
    }
    catch(std::out_of_range )
    {
        std::string message = var_name + " not find";
        throw std::out_of_range(message);
    }
}

void CalculatorInterpreter::enterSetValue(TParser::SetValueContext *ctx) 
{
    //std::cout << "start" << ctx->getText() << std::endl;
}
void CalculatorInterpreter::exitConvertToInt(TParser::ConvertToIntContext * ctx)
{
    integers.push(std::stoi(ctx->getText()));
}
void CalculatorInterpreter::exitPow(TParser::PowContext * ctx)
{
    int power = integers.top();
    std::string var = mon_var.top();
    if (var == "x")
    {
         x_degree+=power;
    }
    if (var == "y")
    {
         y_degree+=power;
    }
    if (var == "z")
    {
         z_degree+=power;
    }
    integers.pop();
    mon_var.pop();
}
/*
void CalculatorInterpreter::exitDivOp(  TParser::DivOpContext *ctx) {
    auto r = int_stack.top(); int_stack.pop();
    auto l = int_stack.top(); int_stack.pop();
    int_stack.push(l/r);
}

void CalculatorInterpreter::exitInt(  TParser::IntContext *ctx) {
    int_stack.push(std::stoi(ctx->getText()));
}
*/
}