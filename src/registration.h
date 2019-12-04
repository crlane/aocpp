#include "ISolution.h"
#include "SolutionFactory.h"

namespace advent {
    template <typename T>
    class SolutionRegistry {
        public:
            SolutionRegistry(const int id) {
                SolutionFactory::Get().Register(
                    id,
                    []() { return static_cast<unique_ptr<ISolution>>(make_unique<T>()); }
                );
            }
    };

}
