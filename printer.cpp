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

#include "printer.h"

void ProgramPrinter::indent() const {
    for (int i = 0; i < indentation; i++) {
        cout << "  ";
    }
}

ProgramPrinter::ProgramPrinter() {
    this->indentation = 0;
}

ProgramPrinter::ProgramPrinter(int indentation) {
    this->indentation = indentation;
}

void ProgramPrinter::visitProgram(Program *program) {
    cout << "programm {" << endl;

    auto subPrinter = new ProgramPrinter(indentation + 1);

    for (auto statement : program->getStatements()) {
        statement->accept(subPrinter);
    }

    delete subPrinter;

    cout << "}" << endl;
}

void ProgramPrinter::visitMove(MoveStatement *move) {
    indent();
    cout <<  "move(" << move->getSteps() << ")" << endl;
}


void ProgramPrinter::visitChange(ChangeStatement *change) {
    indent();
    cout << "value(" << change->getValue() << ")" << endl;
}

void ProgramPrinter::visitPrint(PrintStatement *print) {
    indent();
    cout << "print()" << endl;
}

void ProgramPrinter::visitRead(ReadStatement *read) {
    indent();
    cout << "read()" << endl;
}

void ProgramPrinter::visitLoop(LoopStatement *loop) {
    indent();
    cout << "loop {" << endl;

    auto subPrinter = new ProgramPrinter(indentation + 1);

    for (auto statement : loop->getBlock()) {
        statement->accept(subPrinter);
    }

    delete subPrinter;

    indent();
    cout << "}" << endl;
}

void ProgramPrinter::visitClear(ClearStatement *clear) {
    indent();
    cout << "clear()" << endl;
}
