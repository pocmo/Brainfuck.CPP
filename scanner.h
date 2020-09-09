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

#ifndef CPPBRAINFUCK_SCANNER_H
#define CPPBRAINFUCK_SCANNER_H

using namespace std;

class Scanner {
private:
    istream& input;
    int currentToken;
    int nextToken;

public:
    explicit Scanner(istream& stream);

    bool eof() const;
    void consume(int token);
    int current() const;
    int next();
    bool match(int token) const;
    bool matchNext(int token);
    bool hasNext() const;
};

#endif //CPPBRAINFUCK_SCANNER_H
