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

#include "parser.h"
#include "ast.h"
#include "scanner.h"
#include <iostream>

Statement* change(Scanner* scanner) {
    signed int value = 0;
    bool matches = true;

    while (matches) {
        if (scanner->matchNext('+')) {
            value++;
        } else if (scanner->matchNext('-')) {
            value--;
        } else {
            matches = false;
        }
    }
    return new ChangeStatement(value);
}

Statement* move(Scanner* scanner) {
    signed int steps = 0;
    bool matches = true;

    while (matches) {
        if (scanner->matchNext('>')) {
            steps++;
        } else if (scanner->matchNext('<')) {
            steps--;
        } else {
            matches = false;
        }
    }
    return new MoveStatement(steps);
}

// Forward declaration so that loop() can call statement() and statement() can call loop().
Statement* statement(Scanner* scanner);

Statement* loop(Scanner* scanner) {
    auto loop = new LoopStatement();

    scanner->consume('[');

    while (!scanner->eof() && scanner->current() != ']') {
        loop->addToBlock(statement(scanner));
    }

    scanner->consume(']');

    return loop;
}

Statement* statement(Scanner* scanner) {
    switch (scanner->current()) {
        case '+':
        case '-':
            return change(scanner);
        case '>':
        case '<':
            return move(scanner);
        case '.':
            scanner->consume('.');
            return new PrintStatement();
        case ',':
            scanner->consume(',');
            return new ReadStatement();
        case '[':
            return loop(scanner);

        default:
            scanner->next();
            return nullptr;
    }
}

Program* parse(ifstream& input) {
    auto* program = new Program();
    auto* scanner = new Scanner(input);

    while (scanner->hasNext()) {
        program->addStatement(statement(scanner));
    }

    delete scanner;

    return program;
}

