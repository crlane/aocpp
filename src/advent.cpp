#include "advent.h"
#include <mustache.hpp>
#include <cxxopts.hpp>
#include "SolutionFactory.h"
#include <fstream>

using namespace std;
using namespace kainjow::mustache;


#define USAGE "./advent (run|new) DAY [args...]"
enum class Actions {
    RUN,
    NEW,
};

void usage() {
    cout << USAGE << endl;
}


struct DayCreator {

    public:
        void NewDay(const int day) {
            string sday{to_string(day)};
            ofstream hof{"./src/day" + sday + ".h", ofstream::binary};
            ofstream cppof{"./src/day" + sday + ".cpp", ofstream::binary};
            hof << this->h_tmpl.render({"day", sday}) << endl;
            cppof << this->cpp_tmpl.render({"day", sday}) << endl;
        }
    private:
        mustache h_tmpl{H_TMPL};
        mustache cpp_tmpl{CPP_TMPL};
};

int main(int argc, char* argv[]) {
   cxxopts::Options options("options", "Run c++ advent of code problems");


   try {
       options.add_options()
           ("cmd", "Command to run, one of `run` or `new`", cxxopts::value<string>())
           ("day", "Day, should be number in [1, 25]", cxxopts::value<int>())
           ("args", "Additional arguments for your puzzle", cxxopts::value<vector<string>>())
           ;
       options.parse_positional({"cmd", "day", "args"});
       auto opts = options.parse(argc, argv);
       auto cmd = opts["cmd"].as<string>();
       auto day = opts["day"].as<int>();
       vector<string> args;

       if (opts.count("args")) {
           args = opts["args"].as<vector<string>>();
           for (auto v: args) {
                cout << v << ", ";
           }
           cout << endl;
       }
       auto action = cmd == "run" ? Actions::RUN : Actions::NEW;
       switch(action) {
           case Actions::RUN: {
               cout << "Running " << "day " << day << " with input: " << endl;
               try {
                   auto solution = advent::SolutionFactory::Create(day);
                   solution->Solve(cin, args);
               } catch (out_of_range& e) {
                cerr << "No such solution exists for day " << day << "! Create it with `advent new n`. See help for details." << endl;
                    exit(1);
               }
            } break;
           case Actions::NEW: {
            DayCreator creator;
            creator.NewDay(day);
            cout << "Created new class files" << endl;
           } break;
           default:
                cerr << "Unknown command type" << endl;
                exit(1);
       }
   } catch (const cxxopts::invalid_option_format_error& e) {
        cerr << "Problem parsing options " << e.what();
        options.help({"", "options"});
   } catch (const cxxopts::OptionException& e) {
        cerr << "Problem with options " << e.what();
        options.help({"", "options"});
   }
}
