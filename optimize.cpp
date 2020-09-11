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

#include "optimize.h"

Program *Optimizer::createOptimizedProgram() {
    auto program = new Program();
    for (auto statement : statements) {
        program->addStatement(statement);
    }
    return program;
}

LoopStatement *Optimizer::createOptimizedLoopStatement() {
    auto loop = new LoopStatement();
    for (auto statement : statements) {
        loop->addToBlock(statement);
    }
    return loop;
}

void Optimizer::visitProgram(Program *program) {
    for (auto statement : program->getStatements()) {
        statement->accept(this);
    }
}

void Optimizer::visitLoop(LoopStatement *loop) {
    auto loopOptimizer = new Optimizer();
    for (auto statement : loop->getBlock()) {
        statement->accept(loopOptimizer);
    }

    statements.push_back(loopOptimizer->createOptimizedLoopStatement());
    delete loopOptimizer;
}

void Optimizer::visitMove(MoveStatement *move) {
    statements.push_back(new MoveStatement(move->getSteps()));
}

void Optimizer::visitChange(ChangeStatement *change) {
    statements.push_back(new ChangeStatement(change->getValue()));
}

void Optimizer::visitPrint(PrintStatement *print) {
    statements.push_back(new PrintStatement());
}

void Optimizer::visitRead(ReadStatement *read) {
    statements.push_back(new ReadStatement());
}

void Optimizer::visitClear(ClearStatement *clear) {
    statements.push_back(new ClearStatement());
}