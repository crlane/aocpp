#include "SolutionFactory.h"

advent::SolutionFactory::SolutionFactory() {};

bool advent::SolutionFactory::Register(const int day, const SolutionCreatorFunc& funcCreate) {
    cout << "Registering solution class for day " << day << endl;
    return m_generators.insert(make_pair(day, funcCreate)).second;
}

unique_ptr<advent::ISolution> advent::SolutionFactory::Create(const int day) {

    auto factory = SolutionFactory::Get();
    auto it = factory.m_generators.find(day);
    if (it == factory.m_generators.end()) {
        throw out_of_range{"No such solution has been created"};
    }
    return (*it).second();
}
