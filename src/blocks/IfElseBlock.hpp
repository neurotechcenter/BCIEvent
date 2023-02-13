// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef IFELSEBLOCK_H
#define IFELSEBLOCK_H

#include "Actor.hpp"
#include "Expression.hpp"
#include "StatementCloseBlock.hpp"
namespace BCIEvent_N{

class IfElseEndBlock : public StatementCloseBlock{
    public:
    Block* run(Sequence& sequence);
};

class IfElseElseBlock : public StatementCloseBlock{
    IfElseEndBlock* _endBlock;
    bool _ifCondition;
    friend class IfElseStartBlock;

    void setCond(bool cond) { _ifCondition = cond; }
    public:
    IfElseElseBlock(IfElseEndBlock* endBlock);
    Block* run(Sequence& sequence) override;

};

class IfElseStartBlock : public Block{
    IfElseElseBlock* _elseBlock;
    IfElseEndBlock* _endBlock;
    BooleanExpression _condition;
    

    public:
        IfElseStartBlock(Block* previous, BooleanExpression condition, IfElseElseBlock* elseBlock, IfElseEndBlock* endBlock);
    Block* run(Sequence& sequence) override;
   
};



}


#endif

