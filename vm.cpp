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

#include "vm.h"

VM::VM() = default;

void VM::visitProgram(Program *program) {
    for (auto statement : program->getStatements()) {
        statement->accept(this);
    }
}

void VM::visitMove(MoveStatement *move) {
    this->position += move->getSteps();
}

void VM::visitChange(ChangeStatement *change) {
    this->memory[position] += change->getValue();
}

void VM::visitPrint(PrintStatement *print) {
    cout << this->memory[position];
}

void VM::visitRead(ReadStatement *read) {
    cin.get(this->memory[position]);
}

void VM::visitLoop(LoopStatement *loop) {
    while (this->memory[position] != 0) {
        for (auto statement : loop->getBlock()) {
            statement->accept(this);
        }
    }
}
