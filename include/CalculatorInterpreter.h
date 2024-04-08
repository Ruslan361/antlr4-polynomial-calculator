
#pragma once
#include <iostream>
//#include "CalculatorBaseListener.h"
#include "TParserBaseListener.h"
#include "TParser.h"
#include "TLexer.h"
#include "polynom.h"
//#include "TParserBaseListener.java"
#include <stack> 
#include <map>


/*
 * interpet an aritmetic expression on integer
 * supported operation: +,-,*,/
 */
//using namespace antlrcpptest;
namespace antlrcpptest {
class CalculatorInterpreter: public TParserBaseListener {

    // results stack
    std::stack<Polynom<int>> pol_stack;
    std::map<std::string, Polynom<int>> variables;
    std::stack<std::string> var_stack;
    std::stack<int> integers;
    
    int x_degree;
    int y_degree;
    int z_degree;

    std::stack<std::string> mon_var;

public:
    CalculatorInterpreter()
    {
        x_degree = y_degree = z_degree =0;
    }
    // int get_result()
    // {
    // return 5;
    // }

    void exitPlusOp( TParser::PlusOpContext *ctx) override;
    void exitBinaryMinusOp( TParser::BinaryMinusOpContext * ctx) override;
    void exitUnaryMinusOp( TParser::UnaryMinusOpContext * ctx) override;
    void exitMultOp( TParser::MultOpContext * ctx) override;
    void exitSetValue(TParser::SetValueContext *ctx) override;
    void enterSetValue(TParser::SetValueContext *ctx) override;
    void exitGetValue(TParser::GetValueContext *ctx) override;
    void exitConvertToInt(TParser::ConvertToIntContext * ctx) override;
    void exitReadUserVar(TParser::ReadUserVarContext * ctx) override 
    {
        var_stack.push(ctx->getText());
    }
    virtual void exitPrint(TParser::PrintContext * /*ctx*/) override 
    {
        std::cout << pol_stack.top() << std::endl;
        pol_stack.pop();
    }
    void exitReadVar(TParser::ReadVarContext * ctx) override 
    { 
        mon_var.push(ctx->getText());
    }
    void exitPow(TParser::PowContext * /*ctx*/) override;
    void enterMonom(TParser::MonomContext * /*ctx*/) override 
    {
        x_degree = y_degree = z_degree =0;
    }
    void exitMonom(TParser::MonomContext * /*ctx*/) override 
    {

    }
    void enterFullMonom(TParser::FullMonomContext * /*ctx*/) override 
    {

    }
    virtual void exitFullMonom(TParser::FullMonomContext * /*ctx*/) override 
    {
        int coeff = integers.top();
        integers.pop();
        TSingleLinkedList<Monom<int>> monoms;
        monoms.Add(Monom<int>(coeff, std::vector<int>{x_degree, y_degree, z_degree}));
        Polynom<int> polynom (monoms, {"x", "y", "z"});
        pol_stack.push(polynom);
    }
    void exitMonomZeroPower(TParser::MonomZeroPowerContext * /*ctx*/) override 
    {
        int coeff = integers.top();
        integers.pop();
        
        TSingleLinkedList<Monom<int>> monoms;
        monoms.Add(Monom<int>(coeff, std::vector<int>{x_degree, y_degree, z_degree}));
        Polynom<int> polynom (monoms, {"x", "y", "z"});
        pol_stack.push(polynom);
    }
    void enterMonomWithouCoefficient(TParser::MonomWithouCoefficientContext * /*ctx*/) override 
    {
        int coeff = 1;
        TSingleLinkedList<Monom<int>> monoms;
        monoms.Add(Monom<int>(coeff, std::vector<int>{x_degree, y_degree, z_degree}));
        Polynom<int> polynom (monoms, {"x", "y", "z"});
        pol_stack.push(polynom);
    }
    void exitCalculate(TParser::CalculateContext * /*ctx*/) override 
    {
        int x_point = integers.top();
        integers.pop();
        int y_point = integers.top();
        integers.pop();
        int z_point = integers.top();
        integers.pop();
        Polynom<int> current = pol_stack.top();
        int result = current.Calculate({x_point, y_point, y_point});
        std::cout << "calculate at point ("<< x_point << ", " << y_point << ", "<< z_point << ") = "<< result << std::endl;
        pol_stack.pop();
    }
};
}

//   virtual void enterInput(TParser::InputContext *ctx) = 0;
//   virtual void exitInput(TParser::InputContext *ctx) = 0;

//   virtual void enterSetValue(TParser::SetValueContext *ctx) = 0;
//   virtual void exitSetValue(TParser::SetValueContext *ctx) = 0;

//   virtual void enterPrint(TParser::PrintContext *ctx) = 0;
//   virtual void exitPrint(TParser::PrintContext *ctx) = 0;

//   virtual void enterCalculate(TParser::CalculateContext *ctx) = 0;
//   virtual void exitCalculate(TParser::CalculateContext *ctx) = 0;

//   virtual void enterToMultOrDiv(TParser::ToMultOrDivContext *ctx) = 0;
//   virtual void exitToMultOrDiv(TParser::ToMultOrDivContext *ctx) = 0;

//   virtual void enterBinaryMinusOp(TParser::BinaryMinusOpContext *ctx) = 0;
//   virtual void exitBinaryMinusOp(TParser::BinaryMinusOpContext *ctx) = 0;

//   virtual void enterPlusOp(TParser::PlusOpContext *ctx) = 0;
//   virtual void exitPlusOp(TParser::PlusOpContext *ctx) = 0;

//   virtual void enterToAtom(TParser::ToAtomContext *ctx) = 0;
//   virtual void exitToAtom(TParser::ToAtomContext *ctx) = 0;

//   virtual void enterMultOp(TParser::MultOpContext *ctx) = 0;
//   virtual void exitMultOp(TParser::MultOpContext *ctx) = 0;

//   virtual void enterUnaryMinusOp(TParser::UnaryMinusOpContext *ctx) = 0;
//   virtual void exitUnaryMinusOp(TParser::UnaryMinusOpContext *ctx) = 0;

//   virtual void enterParenthesisOp(TParser::ParenthesisOpContext *ctx) = 0;
//   virtual void exitParenthesisOp(TParser::ParenthesisOpContext *ctx) = 0;

//   virtual void enterMonom(TParser::MonomContext *ctx) = 0;
//   virtual void exitMonom(TParser::MonomContext *ctx) = 0;

//   virtual void enterGetValue(TParser::GetValueContext *ctx) = 0;
//   virtual void exitGetValue(TParser::GetValueContext *ctx) = 0;

//   virtual void enterMon(TParser::MonContext *ctx) = 0;
//   virtual void exitMon(TParser::MonContext *ctx) = 0;

//   virtual void enterPow(TParser::PowContext *ctx) = 0;
//   virtual void exitPow(TParser::PowContext *ctx) = 0;