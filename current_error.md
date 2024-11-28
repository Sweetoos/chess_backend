kacper@Kacpers-MacBook-Pro backend2 % ninja -C build
ninja: Entering directory `build'
[1/10] Building CXX object CMakeFiles/run.dir/src/rook.cpp.o
FAILED: CMakeFiles/run.dir/src/rook.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/rook.cpp.o -MF CMakeFiles/run.dir/src/rook.cpp.o.d -o CMakeFiles/run.dir/src/rook.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/rook.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:20: error: unknown type name 'Rook'
        return new Rook(color, col, row);
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:28:35: warning: unused parameter 'color' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:28:47: warning: unused parameter 'row' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                              ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:28:56: warning: unused parameter 'col' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:38:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Queen *'
        return new Queen(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:46:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Knight *'
        return new Knight(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
3 warnings and 20 errors generated.
[2/10] Building CXX object CMakeFiles/run.dir/src/king.cpp.o
FAILED: CMakeFiles/run.dir/src/king.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/king.cpp.o -MF CMakeFiles/run.dir/src/king.cpp.o.d -o CMakeFiles/run.dir/src/king.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/king.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:38:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Queen *'
        return new Queen(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:46:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Knight *'
        return new Knight(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
[3/10] Building CXX object CMakeFiles/run.dir/src/piece.cpp.o
FAILED: CMakeFiles/run.dir/src/piece.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/piece.cpp.o -MF CMakeFiles/run.dir/src/piece.cpp.o.d -o CMakeFiles/run.dir/src/piece.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/piece.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
[4/10] Building CXX object CMakeFiles/run.dir/src/knight.cpp.o
FAILED: CMakeFiles/run.dir/src/knight.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/knight.cpp.o -MF CMakeFiles/run.dir/src/knight.cpp.o.d -o CMakeFiles/run.dir/src/knight.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/knight.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:38:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Queen *'
        return new Queen(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:46:20: error: unknown type name 'Knight'
        return new Knight(color, col, row);
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:44:35: warning: unused parameter 'color' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:44:47: warning: unused parameter 'row' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                              ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:44:56: warning: unused parameter 'col' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                                       ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
3 warnings and 20 errors generated.
[5/10] Building CXX object CMakeFiles/run.dir/src/main.cpp.o
FAILED: CMakeFiles/run.dir/src/main.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/main.cpp.o -MF CMakeFiles/run.dir/src/main.cpp.o.d -o CMakeFiles/run.dir/src/main.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/main.cpp:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
[6/10] Building CXX object CMakeFiles/run.dir/src/bishop.cpp.o
FAILED: CMakeFiles/run.dir/src/bishop.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/bishop.cpp.o -MF CMakeFiles/run.dir/src/bishop.cpp.o.d -o CMakeFiles/run.dir/src/bishop.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/bishop.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
[7/10] Building CXX object CMakeFiles/run.dir/src/queen.cpp.o
FAILED: CMakeFiles/run.dir/src/queen.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/queen.cpp.o -MF CMakeFiles/run.dir/src/queen.cpp.o.d -o CMakeFiles/run.dir/src/queen.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/queen.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:38:20: error: unknown type name 'Queen'
        return new Queen(color, col, row);
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:36:35: warning: unused parameter 'color' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:36:47: warning: unused parameter 'row' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                              ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:36:56: warning: unused parameter 'col' [-Wunused-parameter]
    Piece *createPiece(PieceColor color, char row, int col)
                                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:46:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Knight *'
        return new Knight(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
3 warnings and 20 errors generated.
[8/10] Building CXX object CMakeFiles/run.dir/src/board.cpp.o
FAILED: CMakeFiles/run.dir/src/board.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/board.cpp.o -MF CMakeFiles/run.dir/src/board.cpp.o.d -o CMakeFiles/run.dir/src/board.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:6:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/board.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
[9/10] Building CXX object CMakeFiles/run.dir/src/pawn.cpp.o
FAILED: CMakeFiles/run.dir/src/pawn.cpp.o 
/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  -I/Users/kacper/studia/infa/cpp/projekt/backend2/inc -Wall -Wextra -Wpedantic -g -std=gnu++17 -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.5.sdk -MD -MT CMakeFiles/run.dir/src/pawn.cpp.o -MF CMakeFiles/run.dir/src/pawn.cpp.o.d -o CMakeFiles/run.dir/src/pawn.cpp.o -c /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:10:5: error: use of undeclared identifier 'Board'
    Board::Square *m_square;
    ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:20:27: error: use of undeclared identifier 'Board'
    virtual void putPiece(Board::Square *square) = 0;
                          ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:21:40: error: unknown type name 'Board'
    virtual void checkAvailableSquares(Board board) = 0;
                                       ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:30:20: error: use of undeclared identifier 'Board'
    void setSquare(Board::Square *square) { m_square = square; }
                   ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/piece.h:31:5: error: use of undeclared identifier 'Board'
    Board::Square *getSquare() { return m_square; }
    ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:3:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/bishop.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:19:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/rook.h:20:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:5:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/queen.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:7:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:18:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/knight.h:19:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:8:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:17:19: error: use of undeclared identifier 'Board'
    void putPiece(Board::Square *square) override;
                  ^
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/king.h:18:32: error: unknown type name 'Board'
    void checkAvailableSquares(Board board) override;
                               ^
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/src/pawn.cpp:1:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/pawn.h:2:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/classes.h:15:
In file included from /Users/kacper/studia/infa/cpp/projekt/backend2/inc/board.h:4:
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:22:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Bishop *'
        return new Bishop(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:30:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Rook *'
        return new Rook(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:38:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Queen *'
        return new Queen(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/kacper/studia/infa/cpp/projekt/backend2/inc/factory.h:46:16: error: cannot initialize return object of type 'Piece *' with an rvalue of type 'Knight *'
        return new Knight(color, col, row);
               ^~~~~~~~~~~~~~~~~~~~~~~~~~~
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
ninja: build stopped: subcommand failed.