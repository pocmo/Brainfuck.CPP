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

#include <cstdio>
#include <iostream>
#include "scanner.h"

using namespace std;

void unexpected(int actual, int expected) {
    cout << "Expected " << (char) expected << ". But found ";
    if (actual == EOF) {
        cout << "EOF";
    } else {
        cout << (char) actual;
    }
    cout << "." << endl;
}

bool is_token(int value) {
    return value == '+'
        || value == '-'
        || value == '<'
        || value == '>'
        || value == '['
        || value == ']'
        || value == '.'
        || value == ',';
}

int next_token(istream& input) {
    int character = EOF;

    while (!input.eof() && !is_token(character)) {
        character = input.get();
        if (character == EOF) {
            break;
        }
    }
    return character;
}

Scanner::Scanner(istream& stream) : input(stream) {
    this->currentToken = next_token(input);
    this->nextToken = next_token(input);
}

int Scanner::current() const {
    return currentToken;
}

void Scanner::consume(int token) {
    if (currentToken != token) {
        unexpected(currentToken, token);
        exit(1);
    }
    next();
}

bool Scanner::eof() const {
    return currentToken == EOF;
}

int Scanner::next() {
    currentToken = nextToken;
    if (!input.eof()) {
        nextToken = next_token(input);
    } else {
        nextToken = EOF;
    }
    return currentToken;
}

bool Scanner::match(int token) const {
    return token == currentToken;
}

bool Scanner::matchNext(int token) {
    if (match(token)) {
        next();
        return true;
    }
    return false;
}

bool Scanner::hasNext() const {
    return currentToken != EOF;
}

