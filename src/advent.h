#ifndef ADVENT_H
#define ADVENT_H

const char* H_TMPL = R"HEADER({{=<% %>=}}#ifndef DAY_<% day %>_H
#define DAY_<% day %>_H
#include "common.h"
#include "ISolution.h"
#include "registration.h"
namespace advent {
    class Day<% day %>: public advent::ISolution {
        public:
            Day<% day %>() {};
            ~Day<% day %>() = default;
            void Part1(istream& in, const vector<string>& args) override {};
            void Part2(istream& in, const vector<string>& args) override {};
            void Parse(istream& in, const vector<string>& args) override {};
            void Solve(istream& in, const vector<string>& args) override;

            static const int DayID() { return dayID; }

        private:
            static const int dayID = <% day %>;
    };

    advent::SolutionRegistry<Day<% day %>> _Day<% day %>(Day<% day %>::DayID());
}
#endif
)HEADER";

const char* CPP_TMPL = R"CPP({{=<% %>=}}#include "day<% day %>.h"
using namespace std;

namespace advent {

    void Day<% day %>::Solve(istream& in, const vector<string>& args) {
        cout << "Called solve for day <% day %>!" << endl;
        for (auto arg : args)
            cout << "Arg: " << arg << endl;

        string input;
        while (getline(in, input)) {
            cout << "Input line:" << input << endl;
        }
    }
}
)CPP";
#endif
