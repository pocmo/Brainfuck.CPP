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
#include <chrono>
#include "parser.h"
#include "printer.h"
#include "vm.h"
#include "optimize.h"
#include "counter.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "File name required." << endl;
        exit(1);
    }

    ifstream ifile(argv[1]);

    if (!ifile.is_open()) {
        cout << "Can't open input file. :(" << endl;
        exit(1);
    }

    auto parseTimeStart = chrono::high_resolution_clock::now();

    auto program = parse(ifile);
    ifile.close();

    auto parseTime = chrono::duration_cast<chrono::milliseconds>(
        chrono::high_resolution_clock::now() - parseTimeStart
    ).count();

    // For now we just print the AST
    auto visitor = new ProgramPrinter();
    program->accept(visitor);
    delete visitor;

    cout << endl;
    cout << "Parse time: " << parseTime << "ms" << endl;

    auto counter = new Counter();
    program->accept(counter);
    cout << "Statements: " << counter->getCount() << endl;
    counter->reset();

    auto optimizeTimeStart = chrono::high_resolution_clock::now();

    auto optimizer = new Optimizer();
    program->accept(optimizer);
    auto optimized = optimizer->createOptimizedProgram();
    delete program;

    auto optimizeTime = chrono::duration_cast<chrono::milliseconds>(
        chrono::high_resolution_clock::now() - optimizeTimeStart
    ).count();

    cout << "Optimize time: " << optimizeTime << "ms" << endl;

    optimized->accept(counter);
    cout << "Statements (optimized): " << counter->getCount() << endl << endl;

    auto runTimeStart = chrono::high_resolution_clock::now();

    // Let's interpret the AST
    auto vm = new VM();
    optimized->accept(vm);
    delete vm;

    auto runTime = chrono::duration_cast<chrono::milliseconds>(
        chrono::high_resolution_clock::now() - runTimeStart
    ).count();

    cout << endl << endl;
    cout << "Run time:   " << runTime << "ms" << endl;

    delete optimized;

    return 0;
}
