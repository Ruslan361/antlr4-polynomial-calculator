/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

//
//  main.cpp
//  antlr4-cpp-demo
//
//  Created by Mike Lischke on 13.03.16.
//

#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "TLexer.h"
#include "TParser.h"
#include "tree/IterativeParseTreeWalker.h"
#include "ExceptionErrorListener.h"
#include "CalculatorInterpreter.h"
#include "TParserVisitor.h"

using namespace antlrcpptest;
using namespace antlr4;

void execute_expression(const std::string &expr) {

    // input stream from line
    antlr4::ANTLRInputStream input(expr);

    // lexer
    TLexer lexer(&input);
    lexer.removeErrorListeners();
    lexer.addErrorListener(new ExceptionErrorListener());

    // tokenizer
    antlr4::CommonTokenStream tokens(&lexer);

    // parser
    TParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(new ExceptionErrorListener());

    antlr4::tree::ParseTree *tree = nullptr;

    // the custom made ExceptionErrorListener immediately stop
    // the parsing when an invalid expression is inserted,
    // we don't want to execute an invalid expression!
    try {
        // parse the input
        tree = parser.input();
    }
    catch (antlr4::ParseCancellationException &e) {
        std::cout << e.what() << std::endl;
        exit(0);
    }

    // calculator interpreter
    CalculatorInterpreter interpreter;

    // interpret the operation
    antlr4::tree::IterativeParseTreeWalker walker;
    walker.walk(&interpreter, tree);

    // print results
    //std::cout << interpreter.get_result() << std::endl;
}

int main() {
    std::string prefix = "calc > ";
    std::ifstream stream("/home/ruslan/Desktop/projects/example/example.txt");
    std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    // parse and interpet the expression readen from the standard input
    std::cout << str;
    std::string line;
    execute_expression(str);
    // while( std::getline(std::cin,line) ) {
    //     execute_expression(line);
    //     std::cout << prefix;
    // }

    return 0;
}

//int main(){}