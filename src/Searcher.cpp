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


/* Function:
 *   deallocateAll
 *
 * Description:
 *   Recursively deallocate search node and all its children
 */

void deallocateAll( SearchNode *&node ) {

  /* Return if null pointer */
  if ( node == NULL ) {
    return;
  }

  /* Delete all children first */
  for ( int i = 0; i < node->m_children.size(); ++i ) {
    deallocateAll( node->m_children[ i ] );
  }

  /* Deallocate node */
  delete node;
  node = NULL;
}

/* Default Constructor */
PuzzleSolution::PuzzleSolution()
    : solutionExists( false ),
      initialState( NULL ),
      numMovesToSolution( 0 ),
      moves( NULL ) {}


/* De-constructor */
PuzzleSolution::~PuzzleSolution() {

  if( initialState != NULL ) {
    delete initialState;
  }

  if( moves != NULL ) {
    delete [] moves;
  }

}

/* Search Node ****************************************************************/

SearchNode::SearchNode()
    : m_initialState( NULL ),
      m_parent( NULL ),
      m_action( NULL ),
      m_children(),
      m_depth( 0 ) {}


SearchNode::SearchNode( const Puzzle *initialState )
    : m_initialState( NULL ),
      m_parent( NULL ),
      m_action( NULL ),
      m_children(),
      m_depth( 0 ) {

  initialState == NULL ? NULL :
      m_initialState = new Puzzle( *( initialState ));
}


SearchNode::SearchNode( const SearchNode *parent, const Move *action )
    : m_initialState( NULL ),
      m_parent( parent ),
      m_children(),
      m_depth( 0 ) {

  m_action = action == NULL ? NULL : new Move( *( action ));

}


SearchNode::SearchNode( const SearchNode *parent, const Move *action,
                        uint32 depth )
    : m_initialState( NULL),
      m_parent( parent ),
      m_children(),
      m_depth( depth ) {

  m_action = action == NULL ? NULL : new Move( *( action ));

}


SearchNode::SearchNode(
    const Puzzle *initialState,
    const SearchNode *parent,
    const Move *action ) :
    m_depth( 0 ) {


  m_initialState = initialState;
  m_parent = parent;
  m_action = action == NULL ? NULL : new Move( *( action ));

}


SearchNode::SearchNode( const Puzzle *initialState, const SearchNode *parent,
                        const Move *action, const uint32 depth ) :
    m_initialState( initialState ),
    m_parent( parent ),
    m_action( NULL ),
    m_children(),
    m_depth( depth ) {


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
  return m_action == NULL ? NULL : new Move( *( m_action ));
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

MinHeapComparator::MinHeapComparator( const f_function *const eval )
    : m_eval( eval ) {}

MinHeapComparator::~MinHeapComparator() {}

bool MinHeapComparator::operator()(
    const SearchNode *lhs,
    const SearchNode *rhs
) {

  Puzzle *lhs_state = lhs->getState();
  Puzzle *rhs_state = rhs->getState();
  bool result;

  /* Use operator> instead of operator< to make min heap */
  result = m_eval->operator()( *lhs_state )
           >
           m_eval->operator()( *rhs_state );

  delete lhs_state;
  delete rhs_state;

  return result;
}


/* Finds puzzle p in a list of search nodes */
SearchNode *Searcher::findNodeWithPuzzle(
    const std::vector< SearchNode * > &nodes,
    Puzzle *p
) const {

  Puzzle *state;

  for ( int i = 0; i < nodes.size(); ++i ) {

    state = nodes[ i ]->getState();

    if ( *state == *p ) {

      delete state;

      return nodes[ i ];
    }

    delete state;
  }

  return NULL;
}


/* Finds puzzle p in a list of search nodes */
bool Searcher::contains(
    const std::vector< SearchNode * > &nodes,
    Puzzle *p
) const {
  return findNodeWithPuzzle( nodes, p ) != NULL;
}