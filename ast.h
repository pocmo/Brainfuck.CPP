/*
 * Copyright 2020 Sebastian Kaspari
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CPPBRAINFUCK_AST_H
#define CPPBRAINFUCK_AST_H

#include <iostream>
#include <vector>

using namespace std;

// Forward declaration of Visitor so that statements can reference it and Visitor can reference the statements.
class Visitor;

enum StatementType {
    MOVE,
    CHANGE,
    PRINT,
    READ,
    LOOP
};

class Statement {
public:
    virtual StatementType type() = 0;

    virtual void accept(Visitor* visitor) = 0;

    virtual ~Statement() = default;
};

class MoveStatement: public Statement {
private:
    int steps;

public:
    StatementType type() override;

    explicit MoveStatement(int steps);

    int getSteps();

    void accept(Visitor* visitor) override;
};

class ChangeStatement: public Statement {
private:
    int value;

public:
    StatementType type() override;

    explicit ChangeStatement(int value);

    int getValue();

    void accept(Visitor* visitor) override;
};

class PrintStatement: public Statement {
    StatementType type() override;

    void accept(Visitor* visitor) override;
};

class ReadStatement: public Statement {
    StatementType type() override;

    void accept(Visitor* visitor) override;
};

class LoopStatement: public Statement {
private:
    vector<Statement*> block;

public:
    StatementType type() override;

    void addToBlock(Statement* statement);

    vector<Statement*> getBlock();

    ~LoopStatement() override;

    void accept(Visitor* visitor) override;
};

class Program {
private:
    vector<Statement*> statements;
public:
    void addStatement(Statement* statement);

    vector<Statement*> getStatements();

    void accept(Visitor* visitor);

    ~Program();
};

class Visitor {
public:
    virtual void visitProgram(Program* program) = 0;

    virtual void visitMove(MoveStatement* move) = 0;

    virtual void visitChange(ChangeStatement* change) = 0;

    virtual void visitRead(ReadStatement* read) = 0;

    virtual void visitPrint(PrintStatement* print) = 0;

    virtual void visitLoop(LoopStatement* loop) = 0;
};


#endif //CPPBRAINFUCK_AST_H
