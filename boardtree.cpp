#include "boardtree.h"
#include <algorithm>

BoardTree::BoardTree(const Board& board) : root(new BoardNode(board)) {}

BoardTree::~BoardTree() {
  if (root != nullptr) {
    delete root;
  }
}

BoardTree* BoardTree::getSubTree(const BoardCoordinate& coords) {
    int row = coords.row;
    int col = coords.col;
    
    // Build the sub-tree if it is empty
    if (root->subTree[row][col].isEmpty()) {
        // Create a new board by making the move at the specified coordinates
        Board newBoard = root->board;
        if (newBoard.play(coords)) {
            // If the move is valid, create a new subtree rooted at the resulting board
            root->subTree[row][col] = BoardTree(newBoard);
        }

    }
    
    // Return a pointer to the specified sub-tree
    return &(root->subTree[row][col]);
}


BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth) {
  
}
