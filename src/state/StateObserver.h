#pragma once

#include "state/State.h"

#include <memory>

namespace state {
/// State observers interface
class StateObserver {
public:
    virtual ~StateObserver() = default;
    /** will be called when state changes.
     * @param state current state.
     */
    virtual void update(const State& state) const = 0;
};

using StateObserverPtr = std::unique_ptr<StateObserver>;
}
