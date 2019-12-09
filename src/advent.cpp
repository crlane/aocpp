#include "advent.h"
#include <mustache.hpp>
#include <cxxopts.hpp>
#include "SolutionFactory.h"
#include <fstream>

using namespace std;
using namespace kainjow::mustache;


enum class Actions {
    RUN,
    NEW,
};


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
   cxxopts::Options options("advent", "Run c++ advent of code problems");
   options
     .positional_help("(run|new) day [args...]");


   try {
       options.add_options("required")
           ("cmd", "Command to run, one of `run` or `new`. Required.", cxxopts::value<string>())
           ("day", "Day, should be number in [1, 25]. Required.", cxxopts::value<int>())
           ("args", "additional arguments for your puzzle. Optional", cxxopts::value<vector<string>>());
       options.add_options()
           ("h,help", "Print this message")
           ("v,verbose", "Enable debug logging");
       options.parse_positional({"cmd", "day", "args"});
       auto opts = options.parse(argc, argv);
       if (opts.count("h")) {
           std::cout << options.help({""}) << std::endl;
           exit(0);
       }

       auto cmd = opts["cmd"].as<string>();
       auto day = opts["day"].as<int>();
       vector<string> args;

       if (opts.count("args")) {
           args = opts["args"].as<vector<string>>();
       }


       auto action = cmd == "run" ? Actions::RUN : Actions::NEW;
       switch(action) {
           case Actions::RUN: {
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
