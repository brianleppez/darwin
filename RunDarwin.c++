// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2014
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

     // ----
     // best
     // ----
     /*
     0: if_random 3
     1: left
     2: go 4
     3: right
     4: if_enemy 10
     5: if_wall 8
     6: hop
     7: go 0
     8: if_random 3
     9: go 1
     10: infect
     11: go 0
    */



    // ----------
    // darwin 8x8
    // ----------

        Species food('f');
        food.addInstruction(LEFT);
        food.addInstruction(GO, 0);

        Species hopper('h');
        hopper.addInstruction(HOP);
        hopper.addInstruction(GO, 0);

        Species rover('r');
        rover.addInstruction(IF_ENEMY, 9);  //0
        rover.addInstruction(IF_EMPTY, 7);  //1
        rover.addInstruction(IF_RANDOM, 5); //2
        rover.addInstruction(LEFT);         //3
        rover.addInstruction(GO, 0);        //4
        rover.addInstruction(RIGHT);        //5
        rover.addInstruction(GO, 0);         //6
        rover.addInstruction(HOP);          //7
        rover.addInstruction(GO, 0);        //8
        rover.addInstruction(INFECT);       //9
        rover.addInstruction(GO, 0);        //10

        Species trap('t');

        trap.addInstruction(IF_ENEMY, 3);
        trap.addInstruction(LEFT);
        trap.addInstruction(GO, 0);
        trap.addInstruction(INFECT);
        trap.addInstruction(GO, 0);

        Species best('b');

        best.addInstruction(IF_ENEMY, 7);  //0
        best.addInstruction(IF_EMPTY, 5);  //1 
        best.addInstruction(LEFT);         //2
        best.addInstruction(GO, 0);        //3   
        best.addInstruction(GO, 0);         //4
        best.addInstruction(HOP);          //5
        best.addInstruction(GO, 0);        //6
        best.addInstruction(INFECT);       //7
        best.addInstruction(GO, 0);         //8
/*
        *** Darwin 8x8 *** START BOARD
                Turn = 0.
                  01234567
                0 f.......
                1 ........
                2 ........
                3 ...hh...
                4 ...hh...
                5 ........
                6 ........
                7 .......f

*/

        //cout << "darwin 8x8 debugging: " << d.board[3][3]->direction << endl;

        //d.darwin_run(5, std::cout);
     
    // Creature c1(&s1);
    // Creature c2(&s2);
    // vector<Creature> cr;
    // for (int i = 0; i < 4; ++i) {
    //  cr.push_back(c1);
    // }
    // cr.push_back(c2);
    // cr.push_back(c2);
    // for (int i = 0; i < cr.size(); ++i) {
    //  cout << "Size: " << cr.size() << endl;
    //  d.addCreature(cr[i], NORTH, 3, 3);
    //  d.addCreature(cr[i], EAST, 3, 4);
    //  d.addCreature(cr[i], SOUTH, 4, 4);
    //  d.addCreature(cr[i], WEST, 4, 3);
    //  d.addCreature(cr[i], EAST, 0, 0);
    //  d.addCreature(cr[i], NORTH, 7, 7);
    // }

    // d.darwin_print(cout);

    //  {
        
    //     Darwin d(10, 10);
    //     Species hopper('h');
    //     Species food('f');

    //     //cout << "hopper:  " << hopper.symbol << endl;


    //     hopper.addInstruction(1);
    //     food.addInstruction(1);

    //     //cout << "hopper2:  " << hopper.symbol << endl;
    //     Creature h1(&hopper);
    //     //cout << "Direction at addCreature0:" << h1.direction << endl;
    //     Creature h2(&food);
    //     //cout << "Direction at addCreature0.1:" << h1.direction << endl;

    //     //cout << "hopper3:  " << hopper.symbol << endl;


    //     d.addCreature(h1, SOUTH, 1, 2);
    //     //cout << "Direction at addCreature:" << d.board[1][1]->direction << endl;
    //     //cout << "hopper4:  " << hopper.symbol << endl;
    //     d.addCreature(h2, NORTH, 9, 2);
    //     cout << "Direction of Creature1: " << d.board[1][2]->direction << endl;
    //     cout << "Direction of Creature2: " << d.board[9][2]->direction << endl;
    //     d.darwin_print(cout);
        


        
        
    //     // d.addCreature(monster, NORTH, 0, 0);
    //     // d.addCreature(monster, SOUTH, 9, 8);
    //     // d.addCreature(monster, EAST, 9, 9);

    //     //d.addCreature(monster, NORTH, 1, 2);

    //     //d.darwin_run(9, std::cout);
    // }
    

    cout << "*** Darwin 8x8 ***" << endl;
    
    // 8x8 Darwin
    // Food,   facing east,  at (0, 0)
    // Hopper, facing north, at (3, 3)
    // Hopper, facing east,  at (3, 4)
    // Hopper, facing south, at (4, 4)
    // Hopper, facing west,  at (4, 3)
    // Food,   facing north, at (7, 7)
    // Simulate 5 moves.
    // Print every grid.
    
    {
        Darwin d(8,8);
        Creature f1(&food);
        Creature f2(&food);
        Creature c1(&hopper);
        Creature c2(&hopper);
        Creature c3(&hopper);
        Creature c4(&hopper);


        
        d.addCreature(f1, EAST, 0, 0);
        d.addCreature(f2, NORTH, 7, 7);
        d.addCreature(c1, NORTH, 3, 3);
        d.addCreature(c2, EAST, 3, 4);        
        d.addCreature(c3, WEST, 4, 3);
        d.addCreature(c4, SOUTH, 4, 4);
        d.darwin_run(5, std::cout);
    }


    //-------------
    //  ROVER TEST
    //-------------

    // {
    //     Creature rov(&rover);
    //     Darwin d(9,9);
    //     d.addCreature(rov, NORTH, 7, 8);
    //     d.darwin_run(15, std::cout);
    // }

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    {
        srand(0);
        Darwin d(7,9);
        Creature t1(&trap);
        Creature t2(&trap);
        Creature h1(&hopper);
        Creature r1(&rover);

        d.addCreature(t1, SOUTH, 0, 0);
        d.addCreature(h1, EAST, 3, 2);
        d.addCreature(r1, NORTH, 5, 4);
        d.addCreature(t2, WEST, 6, 8);
        d.darwin_run(5, std::cout);
    }
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    {
        int n = 72;
        int total = n*n;
        Darwin d(72, 72);
        std::vector<Creature> foods (10, Creature (&food));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(foods[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> hoppers (10, Creature (&hopper));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(hoppers[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> rovers (10, Creature (&rover));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(rovers[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> traps (10, Creature (&trap));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(traps[i], dir, (pos/n), (pos%n)); 
        }
        d.darwin_run(1000, std::cout);
    }
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    {
        int n = 72;
        int total = n*n;
        Darwin d(72, 72);
        std::vector<Creature> foods (10, Creature (&food));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(foods[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> hoppers (10, Creature (&hopper));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(hoppers[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> rovers (10, Creature (&rover));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(rovers[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> traps (10, Creature (&trap));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(traps[i], dir, (pos/n), (pos%n)); 
        }

        std::vector<Creature> bests (10, Creature (&best));
        for(int i = 0; i < 10; ++i){
            int pos = rand() % total;
            int dir = rand() % 4;
            
            d.addCreature(bests[i], dir, (pos/n), (pos%n)); 
        }


        d.darwin_run(1000, std::cout);
    }
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;

}
