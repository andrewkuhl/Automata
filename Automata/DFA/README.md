# Deterministic Finite Automata           <div style="text-align: right">[back](https://github.com/andrewkuhl/Automata)</div>

### DFA( Q , E , d , q0 , F ) where:
### Q : finite set of states
### E : finite alphabet
### d : Q x E &rarr; Q is transition function
### q0: is the start state
### F in Q: is the set of final states

## Machine Specification File e.g.
```
Q{ q1 q2 q3 }
E{ 0 1 }
d{ 
q1 0 q1 ,
q1 1 q2 ,
q2 0 q3 ,
q2 1 q2 ,
q3 0 q2 ,
q3 1 q2
}
q0{ q1 }
F{ q2 }
```

## Input File e.g.
```
input{ 0 0 1 0 1 0 0 1 }
```
