//
// Created by Grant Broadwater on 2/3/18.
//

#ifndef GLITTERBOMB_SEARCHER_H
#define GLITTERBOMB_SEARCHER_H

#include "types.h"
#include "Puzzle.h"

const uint32 EPSILLON = 1u;

struct PuzzleSolution {

    bool solutionExists;
    const Puzzle *initialState;
    uint32 numMovesToSolution;
    const Move *moves;

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

    SearchNode();

    SearchNode( const Puzzle *initialState );

    SearchNode( const SearchNode *parent, const Move *action );

    SearchNode(
        const Puzzle *initialState,
        const SearchNode *parent,
        const Move *action
    );

    SearchNode( const SearchNode &cpy );

    SearchNode operator=( const SearchNode &rhs );

    ~SearchNode();

    Puzzle *getState() const;

    SearchNode *getParent() const;

    Move *getAction() const;

    uint32 getPathCost() const;
};

class Searcher {

private:

public:

    virtual PuzzleSolution *search( Puzzle *puzzle ) const = 0;

};


#endif //GLITTERBOMB_SEARCHER_H
