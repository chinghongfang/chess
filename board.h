#ifndef BOARD_H
#define BOARD_H
#include<QVector>
class Board{
public:
    Board();
    void move(int, int);
    QVector<int> getLocate ()const;
    void firstPossible();
    QVector<QVector<int>> getPossible()const;
    int getTurns()const;
    void setBoard(int, int);
    void setBoard(QVector<int>);
    void setBoard();

    int manage(int);  // optional
private:
    QVector<int> locate;
    QVector<QVector<int>> possible;
    QVector<QVector<int>> record;   //{ {(white)/(black),x,y} {} ...}

    int dieKing();
    QVector<int> move(int, int, QVector<int>);
    void reducePossible();
    int victory();
    int turns;
    int selected;   // optional. Represent axis selected. -1 ==> not selected.
    bool levelup;

};

#endif // BOARD_H
