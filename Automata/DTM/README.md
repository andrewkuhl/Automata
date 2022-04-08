# Deterministic Turing Machine           <div style="text-align: right">[back](https://github.com/andrewkuhl/Automata)</div>

### DTM( Q , E , G , d , q0 , q<sub>accept</sub> , q<sub>reject</sub> ) where:
### Q : finite set of states
### E : finite input alphabet not containing blank
### G : finite tape alphabet containing blank
### d : Q x G &rarr; Q x G x {left,right} is transition function
### q0 in Q: is the start state
### q<sub>accept</sub> in Q: is the accept state
### q<sub>reject</sub> in Q: is the final state

<br>

## Machine Specification File e.g.
```
Q{ q1 q2 q3 q4 q5 q6 q7 }
E{ 0 }
G{ 0 x blank }
d{
q1 q7 blank -> , R ;
q1 q7 x -> , R ;
q1 q2 0 -> blank , R ;
q2 q2 x -> , R ;
q2 q3 0 -> x , R ;
q2 q6 blank -> , R ;
q3 q3 x -> , R ;
q3 q4 0 -> , R ;
q3 q5 blank -> , L ;
q4 q3 0 -> x , R ;
q4 q4 x -> , R ;
q4 q7 blank -> , R ;
q5 q5 0 -> , L ;
q5 q5 x -> , L ;
q5 q2 blank -> , R 
}
q0{ q1 }
qaccept{ q6 }
qreject{ q7 }
```

## Input File e.g.
```
input{ 0 0 0 0 }
```
