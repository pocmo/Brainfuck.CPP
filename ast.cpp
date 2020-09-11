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

#include <vector>
#include "ast.h"

using namespace std;;

MoveStatement::MoveStatement(int steps) {
    this->steps = steps;
}

void MoveStatement::accept(Visitor* visitor) {
    visitor->visitMove(this);
}

int MoveStatement::getSteps() {
    return steps;
}

StatementType MoveStatement::type() {
    return MOVE;
}

ChangeStatement::ChangeStatement(int value) {
    this->value = value;
}

void ChangeStatement::accept(Visitor* visitor) {
    visitor->visitChange(this);
}

int ChangeStatement::getValue() {
    return value;
}

StatementType ChangeStatement::type() {
    return CHANGE;
}

void PrintStatement::accept(Visitor *visitor) {
    visitor->visitPrint(this);
}

StatementType PrintStatement::type() {
    return PRINT;
}

void ReadStatement::accept(Visitor *visitor) {
    visitor->visitRead(this);
}

StatementType ReadStatement::type() {
    return READ;
}

LoopStatement::~LoopStatement() {
    for (auto statement : block) {
        delete statement;
    }
}

void LoopStatement::addToBlock(Statement *statement) {
    block.push_back(statement);
}

vector<Statement*> LoopStatement::getBlock() {
    return block;
}

void LoopStatement::accept(Visitor *visitor) {
    visitor->visitLoop(this);
}

StatementType ClearStatement::type() {
    return CLEAR;
}

void ClearStatement::accept(Visitor *visitor) {
    visitor->visitClear(this);
}

StatementType LoopStatement::type() {
    return LOOP;
}

void Program::addStatement(Statement *statement) {
    statements.push_back(statement);
}

void Program::accept(Visitor *visitor) {
    visitor->visitProgram(this);
}

vector<Statement*> Program::getStatements() {
    return statements;
}

Program::~Program() {
    for (auto statement : statements) {
        delete statement;
    }
}
