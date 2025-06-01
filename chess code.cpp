#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>
#include<fstream>
char ch_R='R',ch_N='N',ch_B='B',ch_K='K',ch_Q='Q',ch_P='P',sm_p='p',sm_r='r',sm_n='n',sm_b='b',sm_k='k',sm_q='q';
int new_position,old_position;
void write_on_board(int ri,int ci,char A[],int dim,bool turn);
void erase_position(char A[],int old_position,int dim);
void player1_move(char A[],int old_row,int old_col,int dim,int ri,int ci,bool turn);
void player2_move(char A[],int old_row,int old_col,int dim,int ri,int ci,bool turn);

void gotoRowCol(int rpos, int cpos)
{
int xpos=cpos, ypos = rpos;
COORD scrn;
HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
scrn.X = cpos;
scrn.Y = rpos;
SetConsoleCursorPosition(hOuput, scrn);
}
void sleep(int m)
{
        for(int j=0;j<m*21000;j++)
        {

        }
}
void printboard(int row,int col,int dim)
{
    for (int i=row;i<=(row+dim*6);i+=6)     // row will increase by 6;
    {                                       // col will increase by 10;
        char ch_row=176;
        for(int j=col;j<=(col+dim*10);j++)
        {
           gotoRowCol(i,j);
           cout << ch_row;
        }


    }
    for (int i=col;i<=(col+dim*10);i+=10)
    {
        char ch_col=176;
        for(int j=row;j<=(row+dim*6);j++)
        {
           gotoRowCol(j,i);     //here j is name of row and i is for col;
           cout << ch_col;
        }

    }
}
void init (char A[],int dim)
{
    for (int i=0;i<dim*dim;i++)
    {
          if(i==0 || i==7)
          {
              A[i]=ch_R;
          }
          else if(i==1 || i==6)
          {
              A[i]=ch_N;
          }
          else if(i==2 || i==5)
          {
             A[i]=ch_B;
          }
          else if(i==3)
          {
             A[i]=ch_K;
          }
          else if(i==4)
          {
             A[i]=ch_Q;
          }
          else if(i<=15 && i>=8)
          {
              A[i]=ch_P;
          }
          else if(i>=48 && i<=55)
          {
              A[i]=sm_p;
          }
          else if(i==56 || i==63)
          {
              A[i]=sm_r;
          }
          else if(i==57 || i==62)
          {
              A[i]=sm_n;
          }
          else if (i==58 || i==61)
          {
              A[i]=sm_b;
          }
          else if(i==59)
          {
              A[i]=sm_q;
          }
          else if(i==60)
          {
              A[i]=sm_k;
          }
          else
          {
               A[i]='-';
          }
    }
}
void array_board(char A[],int dim)
{
   int rh=11;
   int cv=5;
   ofstream file("saved_game.txt");
   for(int i=0;i<(dim*dim);i++)
    {
          gotoRowCol(rh,cv);
          cout << A[i];
          file << A[i];
        if(i%dim==dim-1)
             {
             cout << endl;
             file << endl;
             rh=rh+6;
             cv=5;
             }
         else
            {
             cv=cv+10;
            }
            // sleep(200);
     }
     file.close();
}
int twoD_to_oneD(int row,int col,int dim)
{
    return (row-1)*dim+(col-1);
}
void promotion(int new_position,char A[],int dim,bool turn)
{
    char prom;
    gotoRowCol(45,105);
    cout << "Congratulation now you can promote your pawn"<< endl;
    gotoRowCol(46,105);
    cout << "To proceed your promotion please press ENTER"<< endl;
    getch();
    gotoRowCol(47,105);
    cout<<"Enter the character in which you want to promote your pawn: ";
    cin >> prom;
    gotoRowCol(45,105);
    cout << "                                              "<< endl;
    gotoRowCol(46,105);
    cout << "                                              "<< endl;
    gotoRowCol(47,105);
    cout << "                                                              "<< endl;
    if( turn==1 && (prom=='Q' || prom=='B' || prom=='R' || prom=='N') )
    {
        A[new_position]=prom;
        array_board(A,dim);
    }
    else if( turn==0 && (prom=='q' || prom=='b' || prom=='r' || prom=='n') )
    {
        A[new_position]=prom;
        array_board(A,dim);
    }
    else
    {
        promotion(new_position,A,dim,turn);  // if user press the wrong key then promotion will be called again;
    }
}
void print_Pawn(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(old_position>=8 && old_position<=15)   //for first time of every pawn;
      {
        if(new_position==old_position+9 || new_position==old_position+7)  // to check diagonal
           {
              if( A[new_position]=='p' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='q' || A[new_position]=='k')
                {
                  A[new_position]=ch_P;
                  array_board(A,dim);
                  erase_position(A,old_position,dim);
               }
               else    // it is diagonally this check is to verify that there should be a piece of opponent on new position otherwise take values again;
               {
                   player1_move(A,old_row,old_col,dim,ri,ci,turn);

               }
           }
         else if(new_position==old_position+8 || new_position==old_position+16)
           {
               if(A[new_position]=='-' && A[old_position+8]=='-') // the and condition is to verify that for the first time move of related pawn has no piece in its path;
                {
                   A[new_position]=ch_P;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
                }
                else   // this is straight move of pawn for first move and to verify that there should be space on new position;
                {
                    player1_move(A,old_row,old_col,dim,ri,ci,turn);                }
           }
         else  // this check is to verify that new position should be according to rules;
           {
               player1_move(A,old_row,old_col,dim,ri,ci,turn);
           }
      }
     else if(old_position>15)
       {
           if(new_position==old_position+9 || new_position==old_position+7)  // this check is to tell that in diagonal there is opponent piece;
              {
                 if(A[new_position]=='p' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='q' || A[new_position]=='k')
                   {
                        A[new_position]=ch_P;
                        array_board(A,dim);
                        erase_position(A,old_position,dim);
                        if(new_position/dim==7)
                        {
                            promotion(new_position,A,dim,turn);
                        }
                   }
                 else   //  this check is to verify that on new position there should be a piece of opponent;
                   {

                      player1_move(A,old_row,old_col,dim,ri,ci,turn);
                   }

              }
            else if(new_position==old_position+8)  // this will deal the straight move of pawn;
              {
                  if(A[new_position]=='-')
                    {
                      A[new_position]=ch_P;
                      array_board(A,dim);
                      erase_position(A,old_position,dim);
                      if(new_position/dim==7)
                      {
                            promotion(new_position,A,dim,turn);
                      }
                    }
                  else   // this check is used to verify that there should be space on new position;it is straight move;
                    {
                       player1_move(A,old_row,old_col,dim,ri,ci,turn);
                    }

              }
            else  // this check is used to verify that there should be new moves according to rules;
              {
                player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
     }
}
void print_Knight(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(new_position==old_position+15 || new_position==old_position+17 || new_position==old_position+10 || new_position==old_position+6 || new_position==old_position-6 || new_position==old_position-10 || new_position==old_position-15 || new_position==old_position-17)
    {
        if(A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='r' || A[new_position]=='n' || A[new_position]=='k' || A[new_position]=='q' || A[new_position]=='-')
        {
            A[new_position]=ch_N;
            array_board(A,dim);
            erase_position(A,old_position,dim);
        }
        else
        {
             player1_move(A,old_row,old_col,dim,ri,ci,turn);  //this to verify that at new position of knight should contain opponent piece or space
        }
    }
    else
    {
         player1_move(A,old_row,old_col,dim,ri,ci,turn); //this is to verify that new position should be L-shaped;
    }


}
void print_Rook(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
     if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='k' || A[new_position]=='q')
     {
         if(new_position%dim==old_position%dim) // this is vertical movement;
         {
             if(new_position > old_position)  // frontward movement;
             {
                int countt=0;//this for is to check is its path clear;
                for(int i=old_position;i<new_position;i+=dim)
                 {
                    if(A[i] !='-')
                     {
                         countt=countt+1;
                     }
                 }
                if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
                 {
                     A[new_position]=ch_R;
                     array_board(A,dim);
                     erase_position(A,old_position,dim);
                 }
                else
                 {
                        player1_move(A,old_row,old_col,dim,ri,ci,turn);
                 }
             }
            else if(new_position < old_position)  // backward movement;
             {
                int countt=0; // to check that is path clear;
                for (int i=old_position;i>new_position;i-=dim)
                {
                    if(A[i] != '-')
                    {
                        countt=countt+1;
                    }
                }
                if(countt==1)
                {
                    A[new_position]=ch_R;
                    array_board(A,dim);
                    erase_position(A,old_position,dim);
                }
                else
                {
                    player1_move(A,old_row,old_col,dim,ri,ci,turn);
                }
             }
             else
             {
                 player1_move(A,old_row,old_col,dim,ri,ci,turn);
             }
         }
         else if(new_position/dim==old_position/dim) // for horizontal movement;
         {
             if(new_position>old_position) // right movement;
             {
                int countt=0;//this for is to check is its path clear;
                for(int i=old_position;i<new_position;i+=dim)
                 {
                    if(A[i] !='-')
                     {
                         countt=countt+1;
                     }
                 }
                if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
                 {
                     A[new_position]=ch_R;
                     array_board(A,dim);
                     erase_position(A,old_position,dim);
                 }
                else
                 {
                        player1_move(A,old_row,old_col,dim,ri,ci,turn);
                 }
              }
             else if(new_position<old_position)
              {
                  int countt=0;//this for is to check is its path clear;
                  for(int i=old_position;i>new_position;i-=dim)
                   {
                        if(A[i] !='-')
                          {
                              countt=countt+1;
                          }
                   }
                   if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
                    {
                       A[new_position]=ch_R;
                       array_board(A,dim);
                       erase_position(A,old_position,dim);
                    }
                  else
                   {
                        player1_move(A,old_row,old_col,dim,ri,ci,turn);
                   }
               }
         }
         else
         {
             player1_move(A,old_row,old_col,dim,ri,ci,turn);
         }
      }
     else
      {
         player1_move(A,old_row,old_col,dim,ri,ci,turn); // if new position contain piece of its own;
      }
}
void print_Bishop(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='k' || A[new_position]=='q')
    {
        if(new_position%9==old_position%9)  // this is for the top left to bottom right diagonal;
        {
            if(new_position<old_position)  // this is for the movement to top left corner from bottom right corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_B;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom right corner from top left corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_B;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
        }
        else if(old_position%7==new_position%7)  // this is for the top right to left bottom diagonal or vice versa;
        {
            if(new_position<old_position)  // this is for the movement to top right corner from bottom left corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_B;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom left corner from top right corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_B;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
        }
        else
        {
            player1_move(A,old_row,old_col,dim,ri,ci,turn);  // if at new position is not a diagonal;
        }
    }
    else
    {
        player1_move(A,old_row,old_col,dim,ri,ci,turn);  // if new position contain piece of its own;
    }
}
void print_King(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='r' || A[new_position]=='n' || A[new_position]=='k' || A[new_position]=='q' || A[new_position]=='-')
    {
      if(new_position==old_position+1 || new_position==old_position-1 || new_position==old_position-8 || new_position==old_position+8 || new_position==old_position-7 || new_position==old_position+7 || new_position==old_position-9 || new_position==old_position+9)
      {
          A[new_position]=ch_K;
          array_board(A,dim);
          erase_position(A,old_position,dim);
      }
      else
      {
         player1_move(A,old_row,old_col,dim,ri,ci,turn); // this is to verify that if new position is not valid ;
      }
    }
    else
    {
         player1_move(A,old_row,old_col,dim,ri,ci,turn);  // this is to verify that is the new position contain space or opponent piece;
    }
}
void print_Queen(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='k' || A[new_position]=='q')
     {
         if(new_position%dim==old_position%dim) // this is for the vertical movement;
         {
             if(new_position<old_position) // backward movement of player1;
             {
               int countt=0;
               for(int i=old_position;i>new_position;i-=dim)  //this for is to check is its path clear;
               {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
               }
               if(countt==1)
               {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
               }
               else
               {
                 player1_move(A,old_row,old_col,dim,ri,ci,turn);
               }
             }
             else if(new_position>old_position)  // forward movement;
             {
                int countt=0;
               for(int i=old_position;i<new_position;i+=dim)  //this for is to check is its path clear;
               {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
               }
               if(countt==1)
               {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
               }
               else
               {
                 player1_move(A,old_row,old_col,dim,ri,ci,turn);
               }
             }
          }
         else if(new_position/dim==old_position/dim) // this is for horizontal move;
          {
             if(new_position>old_position) // this is for right move;
             {
                 int countt=0;
                 for(int i=old_position;i<new_position;i++)
                 {
                     if(A[i]!='-')
                     {
                         countt=countt+1;
                     }
                 }
                 if(countt==1)
                 {
                     A[new_position]=ch_Q;
                     array_board(A,dim);
                     erase_position(A,old_position,dim);
                 }
                 else
                 {
                     player1_move(A,old_row,old_col,dim,ri,ci,turn);  // if the path is not clear;
                 }
             }
             else if(new_position<old_position) // left move
             {
                int countt=0;
                for(int i=old_position;i>new_position;i--) // to check is its path clear;
                {
                    if(A[i]!='-')
                    {
                        countt=countt+1;
                    }
                }
                if(countt==1)
                {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
                }
                else
                {
                   player1_move(A,old_row,old_col,dim,ri,ci,turn);
                }
             }
         }
        else if(new_position%9==old_position%9)  // this is for the top left to bottom right diagonal;
         {
            if(new_position<old_position)  // this is for the movement to top left corner from bottom right corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom right corner from top left corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
         }
        else if(old_position%7==new_position%7)  // this is for the top right to left bottom diagonal or vice versa;
         {
            if(new_position<old_position)  // this is for the movement to top right corner from bottom left corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom left corner from top right corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=ch_Q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player1_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
         }
        else
         {
             player1_move(A,old_row,old_col,dim,ri,ci,turn); // for invalid move;
         }
     }
     else
     {
       player1_move(A,old_row,old_col,dim,ri,ci,turn); // if at new position there is no opponent piece or space then take inputs again;
     }

}
//player 2 gotti
void print_s_pawn(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(old_position>=48 && old_position<=55)   //for first time of every pawn;
      {
          if(new_position==old_position-9 || new_position==old_position-7)  // it checks if player want to go to diagonal
           {
              if( A[new_position]=='P' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='Q' || A[new_position]=='K')
                {
                  A[new_position]=sm_p;
                  array_board(A,dim);
                  erase_position(A,old_position,dim);
                }
               else  // this to verify that on new position there should be opponent piece; diagonally
                {
                   player2_move(A,old_row,old_col,dim,ri,ci,turn);
                }
           }
          else if(new_position==old_position-8 || new_position==old_position-16)  // this the step that tells that you can move two or one step for first time;
           {
               if(A[new_position]=='-' && A[old_position-8]=='-') // the and condition is to verify that for the first time move of related pawn has no piece in its path;
                {
                   A[new_position]=sm_p;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
                }
                else // this is to verify that on new position there should be space; it is straight move; for first time
                {
                    player2_move(A,old_row,old_col,dim,ri,ci,turn);
                }
            }
           else  // this is to verify that correct input according to pawn rule;
            {
                player2_move(A,old_row,old_col,dim,ri,ci,turn);
            }
      }
    else if(old_position<48)
      {
          if(new_position==old_position-9 || new_position==old_position-7) // this is to go to diagonal;
             {
                 if(A[new_position]=='P' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='Q' || A[new_position]=='K')
                   {
                        A[new_position]=sm_p;
                        array_board(A,dim);
                        erase_position(A,old_position,dim);
                        if(new_position/dim==0)
                        {
                            promotion(new_position,A,dim,turn);
                        }
                    }
                 else  // this is to verify that on new position there should be opponent piece; secondly
                    {
                         player2_move(A,old_row,old_col,dim,ri,ci,turn);
                    }

             }
          else if(new_position==old_position-8)  // this to be the straight move ;
            {
                if(A[new_position]=='-')
                   {
                      A[new_position]=sm_p;
                      array_board(A,dim);
                      erase_position(A,old_position,dim);
                      if(new_position/dim==0)
                        {
                            promotion(new_position,A,dim,turn);
                        }
                   }
                else   // this check is used to verify that there should be space on new position second time or greater than it
                   {
                       player2_move(A,old_row,old_col,dim,ri,ci,turn);
                   }

            }
            else  // this check is to verify that inputs should be according to the rules of pawn;
            {
                player2_move(A,old_row,old_col,dim,ri,ci,turn);
            }
     }

}
void print_s_knight(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(new_position==old_position+15 || new_position==old_position+17 || new_position==old_position+10 || new_position==old_position+6 || new_position==old_position-6 || new_position==old_position-10 || new_position==old_position-15 || new_position==old_position-17)
    {
        if(A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='R' || A[new_position]=='N' || A[new_position]=='K' || A[new_position]=='Q' || A[new_position]=='-')
        {
            A[new_position]=sm_n;
            array_board(A,dim);
            erase_position(A,old_position,dim);
        }
        else
        {
             player2_move(A,old_row,old_col,dim,ri,ci,turn);  //this to verify that at new position of knight should contain opponent piece or space
        }
    }
    else
    {
         player2_move(A,old_row,old_col,dim,ri,ci,turn);   // this is to verify that new position should be L-shaped;
    }
}
void print_s_rook(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='K' || A[new_position]=='Q')
     {
         if(new_position%dim==old_position%dim) // this is for the vertical movement;
         {
             if(new_position<old_position) // forward movement of player2
             {
               int countt=0;
               for(int i=old_position;i>new_position;i-=dim)  //this for is to check is its path clear;
               {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
               }
               if(countt==1)
               {
                   A[new_position]=sm_r;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
               }
               else
               {
                 player2_move(A,old_row,old_col,dim,ri,ci,turn);
               }
             }
             else if(new_position>old_position)  // backward movement;
             {
                int countt=0;
               for(int i=old_position;i<new_position;i+=dim)  //this for is to check is its path clear;
               {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
               }
               if(countt==1)
               {
                   A[new_position]=sm_r;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
               }
               else
               {
                 player2_move(A,old_row,old_col,dim,ri,ci,turn);
               }
             }
         }
         else if(new_position/dim==old_position/dim) // this is for horizontal move;
         {
             if(new_position>old_position) // this is for right move;
             {
                 int countt=0;
                 for(int i=old_position;i<new_position;i++)
                 {
                     if(A[i]!='-')
                     {
                         countt=countt+1;
                     }
                 }
                 if(countt==1)
                 {
                     A[new_position]=sm_r;
                     array_board(A,dim);
                     erase_position(A,old_position,dim);
                 }
                 else
                 {
                     player2_move(A,old_row,old_col,dim,ri,ci,turn);  // if the path is not clear;
                 }
             }
             else if(new_position<old_position) // left move
             {
                int countt=0;
                for(int i=old_position;i>new_position;i--) // to check is its path clear;
                {
                    if(A[i]!='-')
                    {
                        countt=countt+1;
                    }
                }
                if(countt==1)
                {
                   A[new_position]=sm_r;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
                }
                else
                {
                   player2_move(A,old_row,old_col,dim,ri,ci,turn);
                }
             }
         }
         else
         {
             player2_move(A,old_row,old_col,dim,ri,ci,turn); // for invalid move;
         }
     }
     else
     {
       player2_move(A,old_row,old_col,dim,ri,ci,turn); // if at new position there is no opponent piece or space then take inputs again;
     }

}
void print_s_bishop(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='K' || A[new_position]=='Q')
    {
        if(new_position%9==old_position%9)  // this is for the top left to bottom right diagonal;
        {
            if(new_position<old_position)  // this is for the movement to top left corner from bottom right corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_b;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom right corner from top left corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_b;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
        }
        else if(old_position%7==new_position%7)  // this is for the top right to left bottom diagonal or vice versa;
        {
            if(new_position<old_position)  // this is for the movement to top right corner from bottom left corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_b;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom left corner from top right corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_b;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
        }
        else
        {
            player2_move(A,old_row,old_col,dim,ri,ci,turn);  // if at new position is not a diagonal;
        }
    }
    else
    {
        player2_move(A,old_row,old_col,dim,ri,ci,turn);  // if new position contain piece of its own;
    }
}
void print_s_king(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
    if(A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='R' || A[new_position]=='N' || A[new_position]=='K' || A[new_position]=='Q' || A[new_position]=='-')
    {
      if(new_position==old_position+1 || new_position==old_position-1 || new_position==old_position-8 || new_position==old_position+8 || new_position==old_position-7 || new_position==old_position+7 || new_position==old_position-9 || new_position==old_position+9)
      {
          A[new_position]=sm_k;
          array_board(A,dim);
          erase_position(A,old_position,dim);
      }
      else
      {
         player2_move(A,old_row,old_col,dim,ri,ci,turn); // this is to verify that if new position is not valid ;
      }
    }
    else
    {
         player2_move(A,old_row,old_col,dim,ri,ci,turn);  // this is to verify that is the new position contain space or opponent piece;
    }
}
void print_s_queen(int new_position,char A[],int dim,bool turn,int old_row,int old_col,int ri,int ci)
{
     if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='K' || A[new_position]=='Q')
     {
         if(new_position%dim==old_position%dim) // this is for the vertical movement;
         {
             if(new_position<old_position) // forward movement of player2
             {
               int countt=0;
               for(int i=old_position;i>new_position;i-=dim)  //this for is to check is its path clear;
               {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
               }
               if(countt==1)
               {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
               }
               else
               {
                 player2_move(A,old_row,old_col,dim,ri,ci,turn);
               }
             }
             else if(new_position>old_position)  // backward movement;
             {
                int countt=0;
               for(int i=old_position;i<new_position;i+=dim)  //this for is to check is its path clear;
               {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
               }
               if(countt==1)
               {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
               }
               else
               {
                 player2_move(A,old_row,old_col,dim,ri,ci,turn);
               }
             }
          }
         else if(new_position/dim==old_position/dim) // this is for horizontal move;
          {
             if(new_position>old_position) // this is for right move;
             {
                 int countt=0;
                 for(int i=old_position;i<new_position;i++)
                 {
                     if(A[i]!='-')
                     {
                         countt=countt+1;
                     }
                 }
                 if(countt==1)
                 {
                     A[new_position]=sm_q;
                     array_board(A,dim);
                     erase_position(A,old_position,dim);
                 }
                 else
                 {
                     player2_move(A,old_row,old_col,dim,ri,ci,turn);  // if the path is not clear;
                 }
             }
             else if(new_position<old_position) // left move
             {
                int countt=0;
                for(int i=old_position;i>new_position;i--) // to check is its path clear;
                {
                    if(A[i]!='-')
                    {
                        countt=countt+1;
                    }
                }
                if(countt==1)
                {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
                }
                else
                {
                   player2_move(A,old_row,old_col,dim,ri,ci,turn);
                }
             }
         }
        else if(new_position%9==old_position%9)  // this is for the top left to bottom right diagonal;
         {
            if(new_position<old_position)  // this is for the movement to top left corner from bottom right corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom right corner from top left corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=9) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
         }
        else if(old_position%7==new_position%7)  // this is for the top right to left bottom diagonal or vice versa;
         {
            if(new_position<old_position)  // this is for the movement to top right corner from bottom left corner;
            {
              int countt=0;
              for (int i=old_position;i>new_position;i-=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
            else if(new_position>old_position)  // this is for the movement to bottom left corner from top right corner;
            {
                int countt=0;
              for (int i=old_position;i<new_position;i+=7) // this is to verify that is its path clear?
              {
                  if(A[i]!='-')
                  {
                      countt=countt+1;
                  }
              }
              if(countt==1) // here it equal to 1 as for first time loop will start from old position and this old is included in loop and here definitely the piece of player already exist;
              {
                   A[new_position]=sm_q;
                   array_board(A,dim);
                   erase_position(A,old_position,dim);
              }
              else
              {
                  player2_move(A,old_row,old_col,dim,ri,ci,turn);
              }
            }
         }
        else
         {
             player2_move(A,old_row,old_col,dim,ri,ci,turn); // for invalid move;
         }
     }
     else
     {
       player2_move(A,old_row,old_col,dim,ri,ci,turn); // if at new position there is no opponent piece or space then take inputs again;
     }

}
void erase_position(char A[],int old_position,int dim)
{
    A[old_position]='-';
    array_board(A,dim);
}
void turn_chng(bool &turn)
{

    if(turn==1)
    {
        turn=0;
    }
    else
    {
        turn=1;
    }
}
void player1_move(char A[],int old_row,int old_col,int dim,int ri,int ci,bool turn)
{
     gotoRowCol(20,110);
        cout <<"player 1"<< endl;
        gotoRowCol(21,110);
        cout << "Enter the previous row: ";
        cin >> old_row;
        gotoRowCol(22,110);
        cout << "Enter the previous column: ";
        cin >> old_col;
            if(old_row>0 && old_col>0 && old_row<=dim && old_col<=dim)
            {
                old_position=twoD_to_oneD(old_row,old_col,dim);
                gotoRowCol(24,110);
                cout <<"Enter the next row: ";
                cin>> ri;
                gotoRowCol(25,110);
                cout << "Enter the next column: ";
                cin>> ci;
                    if(ri>0 && ci>0 && ri<=dim && ci<=dim)
                    {
                        new_position=twoD_to_oneD(ri,ci,dim);
                        if(A[old_position]=='P')
                        {
                           print_Pawn(new_position,A,dim,turn,old_row,old_col,ri,ci);
                        }
                        else if(A[old_position]=='N')
                        {
                            print_Knight(new_position,A,dim,turn,old_row,old_col,ri,ci);
                        }
                        else if(A[old_position]=='R')
                        {
                            print_Rook(new_position,A,dim,turn,old_row,old_col,ri,ci);
                        }
                        else if(A[old_position]=='B')
                        {
                            print_Bishop(new_position,A,dim,turn,old_row,old_col,ri,ci);
                        }
                        else if(A[old_position]=='K')
                        {
                            print_King(new_position,A,dim,turn,old_row,old_col,ri,ci);
                        }
                        else if(A[old_position]=='Q')
                        {
                            print_Queen(new_position,A,dim,turn,old_row,old_col,ri,ci);
                        }
                        else
                        {
                            player1_move(A,old_row,old_col,dim,ri,ci,turn);
                        }
                    }
                    else
                    {
                        player1_move(A,old_row,old_col,dim,ri,ci,turn);
                    }
            }
            else
            {
                player1_move(A,old_row,old_col,dim,ri,ci,turn);

            }
}
void player2_move(char A[],int old_row,int old_col,int dim,int ri,int ci,bool turn)
{
    gotoRowCol(28,110);
        cout <<"player 2"<< endl;
        gotoRowCol(29,110);
        cout << "Enter the previous row: ";
        cin >> old_row;
        gotoRowCol(30,110);
        cout << "Enter the previous  column: ";
        cin >> old_col;
        if(old_row>0 && old_col>0 && old_row<=dim && old_col<=dim)
            {
                old_position=twoD_to_oneD(old_row,old_col,dim);
                gotoRowCol(32,110);
                cout <<"Enter the next row: ";
                cin>> ri;
                gotoRowCol(33,110);
                cout << "Enter the next column: ";
                cin>> ci;
                if(ri<=dim && ci <=dim && ri>0 && ci>0)
                {
                    new_position=twoD_to_oneD(ri,ci,dim);
                    if(A[old_position]=='p')
                    {
                        print_s_pawn(new_position,A,dim,turn,old_row,old_col,ri,ci);
                    }
                    else if(A[old_position]=='n')
                    {
                        print_s_knight(new_position,A,dim,turn,old_row,old_col,ri,ci);
                    }
                    else if(A[old_position]=='r')
                    {
                        print_s_rook(new_position,A,dim,turn,old_row,old_col,ri,ci);
                    }
                    else if(A[old_position]=='b')
                    {
                        print_s_bishop(new_position,A,dim,turn,old_row,old_col,ri,ci);
                    }
                    else if(A[old_position]=='k')
                    {
                        print_s_king(new_position,A,dim,turn,old_row,old_col,ri,ci);
                    }
                    else if(A[old_position]=='q')
                    {
                        print_s_queen(new_position,A,dim,turn,old_row,old_col,ri,ci);
                    }
                    else  // this check will works when user give that row and column that is empty;
                    {
                        player2_move(A,old_row,old_col,dim,ri,ci,turn);
                    }

                }
                else
                {
                    player2_move(A,old_row,old_col,dim,ri,ci,turn);
                }
            }
            else
            {
                player2_move(A,old_row,old_col,dim,ri,ci,turn);
            }

}
void legal_move(char A[],int old_row,int old_col,int dim,int ri,int ci,bool turn)
{
   while(true)
   {
    if(turn==1)
       {
          player1_move(A,old_row,old_col,dim,ri,ci,turn);
          old_position=0;
          new_position=0;
          turn_chng(turn);
       }
      // player 2
      else if(turn==0)
       {
          player2_move(A,old_row,old_col,dim,ri,ci,turn);
          old_position=0;
          new_position=0;
          turn_chng(turn);
       }
   }
}
void loaded_game(char A[], int dim, bool turn)
{
    ifstream file("saved_game.txt");
    for(int i=0;i<dim*dim;i++)
    {
        file>>A[i];
    }
    file.close();
}
void labelling(int row,int col,int dim)
{
    int counting=1;
    for(int i=5;i<=(col+dim*10);i+=10)
    {
      gotoRowCol(6,i);
      cout << counting;
      counting++;
    }
    counting=1;
    for(int i=11;i<=(row+dim*6);i+=6)
    {
      gotoRowCol(i,82);
      cout << counting;
      counting++;
    }
    counting=1;
    for(int i=5;i<=(col+dim*10);i+=10)
    {
      gotoRowCol(58,i);
      cout << counting;
      counting++;
    }
}

int main()
{
    cout << "As the pieces take their positions on the battlefield, the silent war is about to unfold."<< endl;
    cout << "This is the game of GAME CHANGERS."<<endl;
    cout << "its name is CHESS the latest version {ChronoStrategia: The Ever-Changing Chessscape}" << endl;
    int choice;
    cout<<"To start new game, press 1"<<endl;
    cout<<"To load previous game, press 2"<<endl;
    cin>>choice;
    int row=8,col=0,dim=8,old_row,old_col,ri,ci;
    bool turn=1;
    char A[dim*dim];
    if(choice==1)
    {
        system("cls");
        printboard(row,col,dim);
        labelling(row,col,dim);
        init(A,dim);
        array_board(A,dim);
       legal_move( A,old_row,old_col,dim,ri,ci,turn);
    }
    else if(choice==2)
    {
        system("cls");
        loaded_game(A,dim,turn);
        printboard(row,col,dim);
        labelling(row,col,dim);
        array_board(A,dim);
        legal_move( A,old_row,old_col,dim,ri,ci,turn);
    }
    return 0;
}
