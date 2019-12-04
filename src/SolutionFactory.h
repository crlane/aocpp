#ifndef REGISTRATION_FACTORY_H
#define REGISTRATION_FACTORY_H

#include "common.h"
#include "ISolution.h"

namespace advent {

    class SolutionFactory {
        public:
            // SolutionCreatorFunc is a pointer to a function that takes no arguments and returns a unique ptr
            // to an ISolution implementer
            using SolutionCreatorFunc = unique_ptr<ISolution>(*)();

        public:
            static SolutionFactory& Get() {
                static SolutionFactory instance;
                return instance;
            }

            bool Register(const int day, const SolutionCreatorFunc& funcCreate);
            static unique_ptr<ISolution> Create(const int day);

        private:
            SolutionFactory();
            // SolutionFactory(const SolutionFactory&);
            ~SolutionFactory() = default;
            unordered_map<int, SolutionCreatorFunc> m_generators;
    };
}

using SolutionCreatorFunc = advent::SolutionFactory::SolutionCreatorFunc;
#endif
