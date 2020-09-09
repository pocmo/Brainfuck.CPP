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

#include <iostream>
#include "parser.h"
#include "printer.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "File name required." << endl;
        exit(1);
    }

    std::ifstream ifile(argv[1]);

    if (!ifile.is_open()) {
        cout << "Can't open input file. :(" << endl;
        exit(1);
    }

    auto program = parse(ifile);
    ifile.close();

    // For now we just print the AST to
    auto visitor = new ProgramPrinter();
    program->accept(visitor);

    delete program;

    return 0;
}
