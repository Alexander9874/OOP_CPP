#include "enums.h"

dead_states & operator ++ (dead_states & state) // ++state
{
    if(state == VAMPIRE) throw Exception("already_max_state");
    state = static_cast<dead_states>(static_cast<int>(state) + 1);
    return state;
}

dead_states & operator -- (dead_states & state) // --state
{
    if(state == GHOST) throw Exception("already_min_state");
    state = static_cast<dead_states>(static_cast<int>(state) - 1);
    return state;
}

dead_states operator ++ (dead_states & state, int) // state++
{
    if(state == VAMPIRE) throw Exception("already_max_state");
    dead_states tmp = state;
    state = static_cast<dead_states>(static_cast<int>(state) + 1);
    return tmp;
}

dead_states operator -- (dead_states & state, int) // state--
{
    if(state == GHOST) throw Exception("already_min_state");
    dead_states tmp = state;
    state = static_cast<dead_states>(static_cast<int>(state) - 1);
    return tmp;
}