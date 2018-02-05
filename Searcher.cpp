/******************************************************************************
 *
 * File:
 *   Searcher
 *
 * Author:
 *   Grant Broadwater
 *
 * Project:
 *   glitterbomb
 *
 ******************************************************************************/

#include "Searcher.h"

/* Default Constructor */
PuzzleSolution::PuzzleSolution()
    : solutionExists( false ),
      initialState( NULL ),
      numMovesToSolution( 0 ),
      moves( NULL ) {}


/* De-constructor */
PuzzleSolution::~PuzzleSolution() {

  delete initialState;
  delete moves;

}

/* Search Node ****************************************************************/

SearchNode::SearchNode()
    : m_initialState( NULL ),
      m_parent( NULL ),
      m_action( NULL ),
      m_children() {}


SearchNode::SearchNode( const Puzzle *initialState )
    : m_initialState( NULL ),
      m_parent( NULL ),
      m_action( NULL ),
      m_children() {

  initialState == NULL ? NULL :
      m_initialState = new Puzzle( *( initialState ));
}


SearchNode::SearchNode( const SearchNode *parent, const Move *action )
    : m_initialState( NULL ),
      m_children() {

  m_parent = parent;
  m_action = action == NULL ? NULL : new Move( *( action ));

}


SearchNode::SearchNode(
    const Puzzle *initialState,
    const SearchNode *parent,
    const Move *action ) {


  m_initialState = initialState;
  m_parent = parent;
  m_action = action == NULL ? NULL : new Move( *( action ));

}


SearchNode::SearchNode( const SearchNode &cpy ) {

  cpy.m_initialState == NULL ? NULL :
      m_initialState = new Puzzle( *( cpy.m_initialState ));
  m_parent = cpy.m_parent;
  m_action = cpy.m_action == NULL ? NULL : new Move( *( cpy.m_action ));

  for ( uint32 i = 0; i < cpy.m_children.size(); ++i ) {
    m_children.push_back( cpy.m_children[ i ] );
  }
}


SearchNode SearchNode::operator=( const SearchNode &rhs ) {

  if ( &rhs == this ) {
    return *this;
  }

  delete m_parent;
  m_parent = new SearchNode( *( rhs.m_parent ));

  delete m_action;
  m_action = new Move( *( rhs.m_action ));

  m_children.clear();
  for ( uint32 i = 0; i < rhs.m_children.size(); ++i ) {
    m_children.push_back( rhs.m_children[ i ] );
  }

  return *this;
}


SearchNode::~SearchNode() {

  delete m_initialState;
  delete m_parent;
  delete m_action;

}


Puzzle *SearchNode::getState() const {

  /* Local variables */
  Puzzle *state = NULL;
  Move *action;

  /* Recursive base case */
  if ( m_initialState != NULL || m_parent == NULL ) {
    return new Puzzle( *( m_initialState ));
  }

  /* Get result after all parent manipulations */
  state = m_parent->getState();

  action = new Move( *m_action );
  /* Make manipulation */
  if ( m_action != NULL ) {
    state->makeMove( *action );
  }
  delete action;

  return state;
}


SearchNode *SearchNode::getParent() const {
  return new SearchNode( *( m_parent ));
}


Move *SearchNode::getAction() const {
  return new Move( *( m_action ));
}


uint32 SearchNode::getPathCost() const {
  if ( m_parent == NULL ) {
    return 0;
  }

  return m_parent->getPathCost() + EPSILLON;
}

std::vector< Move > *SearchNode::getAllActions() const {

  /* Recursive base case */
  if ( m_parent == NULL ) {
    return new std::vector< Move >();
  }

  /* Get all preceeding actions */
  std::vector< Move > *parentMoves = m_parent->getAllActions();

  /* Add this action to list */
  parentMoves->push_back( Move( *m_action ));

  return parentMoves;
}
