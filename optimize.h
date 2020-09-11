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

#ifndef CPPBRAINFUCK_OPTIMIZE_H
#define CPPBRAINFUCK_OPTIMIZE_H

#include "ast.h"

class Optimizer : public Visitor {
private:
    vector<Statement*> statements;

    LoopStatement* createOptimizedLoopStatement();

public:
    Program* createOptimizedProgram();

    void visitProgram(Program* program) override;

    void visitMove(MoveStatement* move) override;

    void visitChange(ChangeStatement* change) override;

    void visitRead(ReadStatement* read) override;

    void visitPrint(PrintStatement* print) override;

    void visitLoop(LoopStatement* loop) override;
};

#endif //CPPBRAINFUCK_OPTIMIZE_H
