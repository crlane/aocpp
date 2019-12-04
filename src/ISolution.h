#ifndef ISOLUTION_H
#define ISOLUTION_H

#include <istream>
#include <vector>

using namespace std;

namespace advent {

    class ISolution {

        public:
            ISolution() = default;
            ~ISolution() = default;
            virtual void Parse(istream& in, const vector<string>& args) = 0;
            virtual void Part1(istream& in, const vector<string>& args) = 0;
            virtual void Part2(istream& in, const vector<string>& args) = 0;
            virtual void Solve(istream& in, const vector<string>& args) = 0;
            static const int DayID();
    };
}
#endif
