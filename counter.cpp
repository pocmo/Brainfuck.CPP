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

#include "counter.h"

int Counter::getCount() {
    return count;
}

void Counter::reset() {
    count = 0;
}

void Counter::visitProgram(Program *program) {
    for (auto statement : program->getStatements()) {
        statement->accept(this);
    }
}

void Counter::visitLoop(LoopStatement *loop) {
    count++;
    for (auto statement : loop->getBlock()) {
        statement->accept(this);
    }
}

void Counter::visitClear(ClearStatement *clear) {
    count++;
}

void Counter::visitChange(ChangeStatement *change) {
    count++;
}

void Counter::visitRead(ReadStatement *read) {
    count++;
}

void Counter::visitPrint(PrintStatement *print) {
    count++;
}

void Counter::visitMove(MoveStatement *move) {
    count++;
}

