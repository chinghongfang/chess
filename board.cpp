#include"board.h"
#include<QVector>
#include<QDebug>
using namespace std;
// there is a bug, that possible is not big enough
Board::Board():locate(80,0),possible(80, QVector<int>(28,-1)){
    // initialize a normal chess board
    locate[0] = 27;     locate[1] = 24;     locate[2] = 23;     locate[3] = 22;
    locate[4] = 28;     locate[5] = 23;     locate[6] = 24;     locate[7] = 27;
    locate[10] = 29;    locate[11] = 29;    locate[12] = 29;    locate[13] = 29;
    locate[14] = 29;    locate[15] = 29;    locate[16] = 29;    locate[17] = 29;
    locate[70] = 17;    locate[71] = 14;    locate[72] = 13;    locate[73] = 12;
    locate[74] = 18;    locate[75] = 13;    locate[76] = 14;    locate[77] = 17;
    locate[60] = 19;    locate[61] = 19;    locate[62] = 19;    locate[63] = 19;
    locate[64] = 19;    locate[65] = 19;    locate[66] = 19;    locate[67] = 19;
    locate[8] = 74;
    locate[9] = 4;
    selected = -1;
    turns = 1;
    firstPossible();
    reducePossible();
}
void Board::move(int x, int y){     // x => y
    for(int i = 30; i<50; ++i){ // reset passant
        if (locate[i]%10 == 9){
            locate[i] = (locate[i]/10)*10 + 6;
        }
    }
    if (locate[y] == 18 || locate[y] == 11){
        locate[8] = -1;
    }else if (locate[y] == 28 || locate[y] == 21){
        locate[9] = -1;
    }else{}
    if (locate[x] == 16 && locate[y] == 0 && (x-y)!=10 && (x-y)!=-10){ // passant eat
        locate[y] = 16;
        locate[y+10] = 0;
    }else if(locate[x] == 26 && locate[y] == 0 && (x-y)!=10 && (x-y)!=-10){
        locate[y] = 26;
        locate[y-10] = 0;
    }else if(locate[x] == 18){
        if((x-y)==2){      //castling
            locate[y] = 11;
            locate[73] = 15;
            locate[70] = 0;
        }else if((x-y)==-2){
            locate[y] = 11;
            locate[75] = 15;
            locate[77] = 0;
        }else{              //not castling
            locate[y] = 11;
        }
        locate[8] = y;
    }else if (locate[x] == 28){
        if((x-y)==2){      //castling
            locate[y] = 21;
            locate[3] = 25;
            locate[0] = 0;
        }else if((x-y)==-2){
            locate[y] = 21;
            locate[5] = 25;
            locate[7] = 0;
        }else{              //not castling
            locate[y] = 21;
        }
        locate[9] = y;
    }else if (locate[x]%10==7){
        locate[y] = (locate[x]/10)*10 + 5;
    }else if (locate[x]%10 == 9){
        if ((x-y) == 20 || (x-y) == -20){   // jump
            locate[y] = (locate[x]/10)*10 + 9;
        }else{
            locate[y] = (locate[x]/10)*10 + 6;
        }
    }else if (locate[x]%10 == 1){
        locate[y] = locate[x];
        locate[7+locate[x]/10] = y;
    }else{
        //qDebug()<<"\telse";
        locate[y] = locate[x];
    }
    if (locate[x] == 16 && y/10 == 0){
        levelup = true;
    }else if (locate[x] == 26 && y/10 == 7){
        levelup = true;
    }
    locate[x] = 0;
    firstPossible();
    reducePossible();
}
void Board::firstPossible(){
    //qDebug()<<"firstPossible start";
    for(int i = 0; i<80; ++i){      // initialize
        for(int j = 0; j<28; ++j){
            possible[i][j] = -1;
        }
    }
    if (locate[8]<0 || locate[9]<0){    // king dead
        return;
    }
    for(int i = 0; i<80; ++i){
        //qDebug()<<"locate["<<i<<"]="<<locate[i];
        int tmp = i;
        if (locate[i] == 0 || i%10>7){}
        else{
        switch (locate[i]%10){
        case 8:

        case 1:
            if ((i/10)>0 && (i%10)>0 && locate[i-11]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-11;}
            if ((i/10)>0 && locate[i-10]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-10;}
            if ((i/10)>0 && (i%10)<7 && locate[i-9]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-9;}
            if ((i%10)>0 && locate[i-1]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-1;}
            if ((i%10)<7 && locate[i+1]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+1;}
            if ((i/10)<7 && (i%10)>0 && locate[i+9]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+9;}
            if ((i/10)<7 && locate[i+10]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+10;}
            if ((i/10)<7 && (i%10)<7 && locate[i+11]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+11;}
            break;
        case 2:
            while((tmp-11)>=0 && (tmp%10)>0){   // ^<-
                if (!locate[tmp-11]){   // can go
                    tmp = tmp - 11;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if ((locate[tmp-11]/10)!=(locate[i]/10)){   // eat
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-11;
                    break;
                }else{break;}     // block
            }
            tmp = i;
            while((tmp-10)>=0){     // ^
                if (!locate[tmp-10]){
                    tmp = tmp - 10;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if ((locate[tmp-10]/10)!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-10;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp-9)>0 && (tmp%10)<7){ // ->^
                if (!locate[tmp-9]){
                    tmp = tmp - 9;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp-9]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-9;
                    break;
                }else{break;}
            }
            tmp = i;
            while(tmp%10>0){    // <-
                if (!locate[tmp-1]){
                    tmp = tmp - 1;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp-1]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-1;
                    break;
                }else{break;}
            }
            tmp = i;
            while(tmp%10<7){    // ->
                if (!locate[tmp+1]){
                    tmp = tmp + 1;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+1]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+1;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp+9)<78 && tmp%10>0){  // v<-
                if (!locate[tmp+9]){
                    tmp = tmp + 9;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+9]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+9;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp+10)<78){     // v
                if (!locate[tmp+10]){
                    tmp = tmp + 10;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+10]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+10;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp+11)<78 && tmp%10<7){ // ->v
                if (!locate[tmp+11]){
                    tmp = tmp + 11;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+11]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+11;
                    break;
                }else{break;}
            }
            break;
        case 3:
            while((tmp-11)>=0 && (tmp%10)>0){   // ^<-
                if (!locate[tmp-11]){   // can go
                    tmp = tmp - 11;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if ((locate[tmp-11]/10)!=(locate[i]/10)){   // eat
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-11;
                    break;
                }else{break;}     // block
            }
            tmp = i;
            while((tmp-9)>0 && (tmp%10)<7){ // ->^
                if (!locate[tmp-9]){
                    tmp = tmp - 9;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp-9]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-9;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp+9)<78 && tmp%10>0){  // v<-
                if (!locate[tmp+9]){
                    tmp = tmp + 9;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+9]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+9;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp+11)<78 && tmp%10<7){ // ->v
                if (!locate[tmp+11]){
                    tmp = tmp + 11;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+11]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+11;
                    break;
                }else{break;}
            }
            break;
        case 4:
            if ((i/10)>1 && (i%10)>0 && locate[i-21]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-21;}
            if ((i/10)>1 && (i%10)<7 && locate[i-19]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-19;}
            if ((i/10)>0 && (i%10)>1 && locate[i-12]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-12;}
            if ((i/10)<7 && (i%10)>1 && locate[i+8]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+8;}
            if ((i/10)>0 && (i%10)<6 && locate[i-8]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-8;}
            if ((i/10)<7 && (i%10)<6 && locate[i+12]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+12;}
            if ((i/10)<6 && (i%10)>0 && locate[i+19]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+19;}
            if ((i/10)<6 && (i%10)<7 && locate[i+21]/10!=locate[i]/10){
                int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+21;}
            break;
        case 7:
        case 5:
            while((tmp-10)>=0){     // ^
                if (!locate[tmp-10]){
                    tmp = tmp - 10;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if ((locate[tmp-10]/10)!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-10;
                    break;
                }else{break;}
            }
            tmp = i;
            while(tmp%10>0){    // <-
                if (!locate[tmp-1]){
                    tmp = tmp - 1;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp-1]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp-1;
                    break;
                }else{break;}
            }
            tmp = i;
            while(tmp%10<7){    // ->
                if (!locate[tmp+1]){
                    tmp = tmp + 1;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+1]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+1;
                    break;
                }else{break;}
            }
            tmp = i;
            while((tmp+10)<78){     // v
                if (!locate[tmp+10]){
                    tmp = tmp + 10;
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp;
                }else if (locate[tmp+10]/10!=locate[i]/10){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+10;
                    break;
                }else{break;}
            }
            break;
        case 9:
            switch (locate[i]/10){
            case 1:
                if (locate[i-20]!=0 || i/10 != 6 || locate[i-10] != 0){;}
                else{
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-20;}
                break;
            case 2:
                if (locate[i+20] != 0 || i/10!=1 || locate[i+10] != 0){;}   // v
                else{
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+20;}
                break;
            }
        case 6:
            switch (locate[i]/10){
            case 1:     // white
                if (i-10<0){break;}
                if (locate[i-10] != 0){;}   // ^
                else{
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-10;}
                if (i%10>0 && locate[i-11]/10 == 2){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-11;}
                if (i%10<7 && locate[i-9]/10 == 2){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-9;}
                if (i%10>0 && locate[i-1] == 29 && i/10 == 3){   // remember to reset "passant" to 16
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-11;}
                if (i%10<7 && locate[i+1] == 29 && i/10 == 3){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i-9;}
                break;
            case 2:
                if (i+10>79){break;}
                if (locate[i+10] != 0){;}   // v
                else{
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+10;}
                if (i%10>0 && locate[i+9]/10 == 1){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+9;}
                if (i%10<7 && locate[i+11]/10 == 1){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+11;}
                if (i%10>0 && locate[i-1] == 19 && i/10 == 4){   // remember to reset "passant" to 16
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=i+9;}
                if (i%10<7 && locate[i+1] == 19 && i/10 == 4){
                    int j=0;while(possible[i][j]+1){++j;};possible[i][j]=tmp+11;}
                break;
            }
            break;
        }
        }
    }
    // castling.
    if (dieKing() == 2){
        if (locate[74]==18 && locate[75]==0 && locate[76]==0 && locate[77]==17){
            int j=0;while(possible[74][j]+1){++j;};possible[74][j]=76;}
        if (locate[74]==18 && locate[73]==0 && locate[72]==0 && locate[70]==17){
            int j=0;while(possible[74][j]+1){++j;};possible[74][j]=72;}
    }else if (dieKing() == 1){
        if (locate[4]==28 && locate[5]==0 && locate[6]==0 && locate[7]==27){
            int j=0;while(possible[4][j]+1){++j;};possible[4][j]=6;}
        if (locate[4]==28 && locate[3]==0 && locate[2]==0 && locate[0]==27){
            int j=0;while(possible[4][j]+1){++j;};possible[4][j]=2;}
    }else if(dieKing() == 0){
        if (locate[74]==18 && locate[75]==0 && locate[76]==0 && locate[77]==17){
            int j=0;while(possible[74][j]+1){++j;};possible[74][j]=76;}
        if (locate[74]==18 && locate[73]==0 && locate[72]==0 && locate[70]==17){
            int j=0;while(possible[74][j]+1){++j;};possible[74][j]=72;}
        if (locate[4]==28 && locate[5]==0 && locate[6]==0 && locate[7]==27){
            int j=0;while(possible[4][j]+1){++j;};possible[4][j]=6;}
        if (locate[4]==28 && locate[3]==0 && locate[2]==0 && locate[0]==27){
            int j=0;while(possible[4][j]+1){++j;};possible[4][j]=2;}
    }else{}
    //qDebug()<<"firstPossible end.";
}
void Board::reducePossible(){
    QVector<int> tmpLoc(locate);        // not change
    QVector<QVector<int>> tmpPossible(possible);    // not change while firstPossible()
    //qDebug()<<"reducePossible start";
    for(int i = 0; i<80; ++i){
        //qDebug()<<"\ti = "<<i;
        if (tmpLoc[i]/10 == 1){
            for(int j = 0; j<28; ++j){
                if (tmpPossible[i][j]+1){
                    //qDebug()<<"\t\tj="<<j;
                    locate = move(i, tmpPossible[i][j], tmpLoc);
                    firstPossible();    // can eat king
                    if (dieKing() == 1 || dieKing() == 3){
                        //qDebug()<<"\tpossible["<<i<<"]["<<j<<"]="<<tmpPossible[i][j]<<"was reduced";
                        tmpPossible[i][j] = -1;
                    }else{}
                }
            }
        }else if(tmpLoc[i]/10 == 2){
            for(int j = 0; j<28; ++j){
                if (tmpPossible[i][j]+1){
                    locate = move(i, tmpPossible[i][j], tmpLoc);
                    firstPossible();    // can eat king
                    if (dieKing() == 2 || dieKing() == 3){
                        tmpPossible[i][j] = -1;
                    }else{}
                }else{}
            }
        }else{}
    }
    locate = tmpLoc;        // not changed
    possible = tmpPossible; // reduced
    //qDebug()<<"reducePossible end.";
}
int Board::dieKing(){
    int dieWhite = 0;
    int dieBlack = 0;
    for(int i = 0; i<80; ++i){
        if (locate[i]/10 == 1){
            for(int j = 0; j<28; ++j){
                if (locate[9] == possible[i][j] || dieBlack){
                    dieBlack = 2;
                    break;
                }
            }
        }else if(locate[i]/10 == 2){
            for(int j = 0; j<28; ++j){
                if (locate[8] == possible[i][j] || dieWhite){
                    dieWhite = 1;
                    break;
                }
            }
        }else{}
    }
    return (dieWhite+dieBlack);
}

QVector<QVector<int>> Board::getPossible()const{
    return possible;
}
QVector<int> Board::getLocate()const{
    return locate;
}
int Board::getTurns()const{
    return turns;
}
QVector<int> Board::move(int x, int y, QVector<int> locate){
    if (locate[y] == 18 || locate[y] == 11){
        locate[8] = -1;
    }else if (locate[y] == 28 || locate[y] == 21){
        locate[9] = -1;
    }else{}
    if (locate[x] == 16 && locate[y] == 0 && (x-y)!=10 && (x-y)!=-10){ // passant eat
        locate[y] = 16;
        locate[y+10] = 0;
    }else if(locate[x] == 26 && locate[y] == 0 && (x-y)!=10 && (x-y)!=-10){
        locate[y] = 26;
        locate[y-10] = 0;
    }else if(locate[x] == 18){
        if((x-y)==2){      //castling
            locate[y] = 11;
            locate[73] = 15;
            locate[70] = 0;
        }else if((x-y)==-2){
            locate[y] = 11;
            locate[75] = 15;
            locate[77] = 0;
        }else{              //not castling
            locate[y] = 11;
        }
        locate[8] = y;
    }else if (locate[x] == 28){
        if((x-y)==2){      //castling
            locate[y] = 21;
            locate[3] = 25;
            locate[0] = 0;
        }else if((x-y)==-2){
            locate[y] = 21;
            locate[5] = 25;
            locate[7] = 0;
        }else{              //not castling
            locate[y] = 21;
        }
        locate[9] = y;
    }else if (locate[x]%10==7){
        locate[y] = (locate[x]/10)*10 + 5;
    }else if (locate[x]%10 == 9){
        if ((x-y) == 20 || (x-y) == -20){   // jump
            locate[y] = (locate[x]/10)*10 + 9;
        }else{
            locate[y] = (locate[x]/10)*10 + 6;
        }
    }else if (locate[x] == 11){
        locate[y] = 11;
        locate[8] = y;
    }else if (locate[x] == 21){
        locate[y] = 21;
        locate[9] = y;
    }else{
        locate[y] = locate[x];
    }
    locate[x] = 0;
    return locate;
}

void Board::setBoard(int loc, int chess){
    if (loc<80){
        if (loc<0){}
        else{
            locate[loc] = chess;
        }
    }else if (loc == 100){      // set turns
        turns = chess;          // borrow the chess variable
    }else if (loc ==200){       // for blank the board
        for(int i = 0; i<8; ++i){
            for(int j = 0; j<8; ++j){
                locate[i*10+j] = chess;
            }
        }
        locate[8] = -1;
        locate[9] = -1;
    }else{
        qDebug()<<"invalid";
    }
    firstPossible();
    reducePossible();
}
void Board::setBoard(QVector<int> v){
    locate = v;
    firstPossible();
    reducePossible();
}
void Board::setBoard(){     // initialize
    for(int i = 0; i<80; ++i){
        locate[i] = 0;
    }
    locate[0] = 27;     locate[1] = 24;     locate[2] = 23;     locate[3] = 22;
    locate[4] = 28;     locate[5] = 23;     locate[6] = 24;     locate[7] = 27;
    locate[10] = 29;    locate[11] = 29;    locate[12] = 29;    locate[13] = 29;
    locate[14] = 29;    locate[15] = 29;    locate[16] = 29;    locate[17] = 29;
    locate[70] = 17;    locate[71] = 14;    locate[72] = 13;    locate[73] = 12;
    locate[74] = 18;    locate[75] = 13;    locate[76] = 14;    locate[77] = 17;
    locate[60] = 19;    locate[61] = 19;    locate[62] = 19;    locate[63] = 19;
    locate[64] = 19;    locate[65] = 19;    locate[66] = 19;    locate[67] = 19;
    locate[8] = 74;
    locate[9] = 4;
    selected = -1;
    turns = 1;
    firstPossible();
    reducePossible();
}

int Board::victory(){
    int white = 0;
    int black = 0;
    for(int i = 0; i<80; ++i){
        if (locate[i] == -1){}
        else if (locate[i]/10 == 1){
            for(int j = 0; j<28; ++j){
                if (possible[i][j]+1){  //  white has some chess to move
                    white = 1;
                    break;
                }else{}
            }
        }
    }
    for(int i = 0; i<80; ++i){
        if (locate[i] == -1){}
        else if (locate[i]/10 == 2){
            for(int j = 0; j<28; ++j){
                if (possible[i][j]+1){black = 2;break;}
                else{}        //  white has some chess to move
            }
        }
    }
    return (white+black);
}

int Board::manage(int in){      // 0: don't print, 1: pawn upgrade,

    /*for(int i = 0; i<21; ++i){
        qDebug()<<"possible["<<in<<"]: "<<possible[in][i];
    }*/
    if (levelup){
        //qDebug()<<"levelup mode";
        if (in/100>0){
            setBoard(selected,in-100);
            selected = -1;
            turns = 3 - turns;
            levelup = false;
            if (victory()==1){return 600+in;}      // black nowhere to move
            else if (victory()==2){return 700+in;}
            else{}
            return 100;
        }else {
            return turns*100+300;
        }
    }
    /*qDebug()<<"locate[in]: "<<locate[in];
    qDebug()<<"turns"<<turns;
    qDebug()<<"selected"<<selected;*/
    if (selected+1){
        for(int i = 0; i<21; ++i){

            if (possible[selected][i] == in){   // can go
                //qDebug()<<"can go";
                move(selected, in);
                selected = -1;
                if (levelup){
                    selected = in;      // borrow "selected" to save the chess who need to level up.
                    return turns*100+300;
                }
                turns = 3 - turns;
                if (victory()==1){return 600+in;}
                else if (victory()==2){return 700+in;}
                else{}
                return in;
            }else{}
        }
    }else{     // selected == -1
        if (turns == locate[in]/10){
            selected = in;
            return in+300;
        }else{      // select enemy or blank.
            selected = -1;
            return in+200;
        }
    }
    if (locate[in]/10 == turns){    // selected but can't go. (cannot delete it!!)
        selected = in;
        return in+300;
    }else{
        selected = -1;
        return in+200;
    }
}

