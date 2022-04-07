# Noneterministic Finite Automata           <div style="text-align: right">[back](https://github.com/andrewkuhl/Automata)</div>

### NFA(Q,E,d,q0,F) where:
### Q : finite set of states
### E : finite alphabet
### d : Q x E -> Q is transition function including epsilon
### q0: is the start state
### F in Q: is the set of final states

# Machine Specification File e.g.
```
Q{ q1 q2 q3 q4 }
E{ 0 1 eps }
d{
q1 0 q1 ,
q1 1 q1 ,
q1 1 q2 ,
q2 0 q3 ,
q2 eps q3 ,
q3 1 q4 ,
q4 1 q4 ,
q4 0 q4 
}
q0{ q1 }
F{ q4 }
```

# Input File e.g.
```
input{ 0 0 1 1 0 0 1 }
```
