#ifndef TETRIS_VISITOR_H
#define TETRIS_VISITOR_H

#include "game.h"
#include "tetris_board.h"
#include "tetris_piece.h"
#include "component_visitor.h"

class TetrisVisitor : public ComponentVisitor
{
public:

  TetrisVisitor( TetrisBoard& board, Game& game );

  void visitTetrisPiece( TetrisPiece& piece ) override;

  void visitTetrisBoard( TetrisBoard& piece ) override;

private:

  TetrisBoard& board;
  Game& game;
  
};

#endif
