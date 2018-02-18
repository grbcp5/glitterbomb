//
// Created by Grant Broadwater on 2/3/18.
//

#ifndef GLITTERBOMB_SEARCHER_H
#define GLITTERBOMB_SEARCHER_H

#include <vector>

#include "GlitterbombConstants.h"
#include "types.h"
#include "Puzzle.h"

const uint32 EPSILLON = 1u;

struct PuzzleSolution {

    bool solutionExists;
    const Puzzle *initialState;
    uint32 numMovesToSolution;
    Move *moves;

    /* Default Constructor */
    PuzzleSolution();

    /* De-constructor */
    ~PuzzleSolution();
};

class SearchNode {

private:
    const Puzzle *m_initialState;
    const SearchNode *m_parent;
    const Move *m_action;

public:

    uint32 m_depth;

    std::vector< SearchNode * > m_children;

    SearchNode();

    SearchNode( const Puzzle *initialState );

    SearchNode( const SearchNode *parent, const Move *action );

    SearchNode( const SearchNode *parent, const Move *action, uint32 depth );

    SearchNode(
        const Puzzle *initialState,
        const SearchNode *parent,
        const Move *action
    );

    SearchNode(
        const Puzzle *initialState,
        const SearchNode *parent,
        const Move *action,
        const uint32 depth
    );

    SearchNode( const SearchNode &cpy );

    SearchNode operator=( const SearchNode &rhs );

    ~SearchNode();

    Puzzle *getState() const;

    SearchNode *getParent() const;

    Move *getAction() const;

    uint32 getPathCost() const;

    std::vector< Move > *getAllActions() const;
};


class f_function {
public:
    virtual double operator()( const Puzzle &p ) const = 0;

    virtual ~f_function() {}
};


struct MinHeapComparator {

    const f_function *const m_eval;

    MinHeapComparator( const f_function *const eval )
        : m_eval( eval ) {}

    ~MinHeapComparator() {}

    bool operator()( const SearchNode *lhs, const SearchNode *rhs ) {

      /* Use operator> instead of operator< to make min heap */
      return (( *m_eval )( *( lhs->getState())))
             >
             (( *m_eval )( *( rhs->getState())));
    }
};

class Searcher {
public:

    virtual PuzzleSolution *search( Puzzle *puzzle ) const = 0;

    virtual ~Searcher() {};

};


void deallocateAll( SearchNode *&node );

#endif //GLITTERBOMB_SEARCHER_H
