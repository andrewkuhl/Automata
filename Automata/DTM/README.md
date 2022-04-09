# Deterministic Turing Machine           <div style="text-align: right">[back](https://github.com/andrewkuhl/Automata)</div>

### DTM( Q , E , G , d , q0 , q<sub>accept</sub> , q<sub>reject</sub> ) where:
### Q : finite set of states
### E : finite input alphabet not containing blank
### G : finite tape alphabet containing blank
### d : Q x G &rarr; Q x G x {left,right} is transition function
### q0 in Q: is the start state
### q<sub>accept</sub> in Q: is the accept state
### q<sub>reject</sub> in Q: is the reject state

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

## Output e.g.
```
[Main]: choose machine..
[1][DFA]..
[2][NFA]..
[3][PDA]..
[4][CFG]..
[5][DTM]..
[0][EXIT]
5
[Main]: initializing DTM..
[DTM]: initialized
[DTM]: initializing Controller..
[Controller]: initialized
[DTM]: initializing InputHandler..
[InputHandler]: initialized
[InputHandler]: loading........
[InputHandler]: done
[DTM]: loading...................
[DTM]: done
[DTM]: passed checks.. 
[DTM]: Q: {[q1], [q2], [q3], [q4], [q5], [q6], [q7]}
[DTM]: E: {[0]}
[DTM]: G: {[0], [x], [blank]}
[DTM]: d: {
[q1, q7, blank -> blank, R], 
[q1, q7, x -> x, R], 
[q1, q2, 0 -> blank, R], 
[q2, q2, x -> x, R], 
[q2, q3, 0 -> x, R], 
[q2, q6, blank -> blank, R], 
[q3, q3, x -> x, R], 
[q3, q4, 0 -> 0, R], 
[q3, q5, blank -> blank, L], 
[q4, q3, 0 -> x, R], 
[q4, q4, x -> x, R], 
[q4, q7, blank -> blank, R], 
[q5, q5, 0 -> 0, L], 
[q5, q5, x -> x, L], 
[q5, q2, blank -> blank, R]
}
[DTM]: q0: {[q1]}
[DTM]: qaccept: {[q6]}
[DTM]: qreject: {[q7]}
[DTM]: ready..
[Main]: run DTM? [y/n]  y
[Main]: running DTM..
[DTM]: running...
[DTM]: ..
[DTM]: initializing Tape..
[Tape]: initialized
[DTM]: computing..
[DTM]: ..
[Machine]: [q1, q2, 0 -> blank, R], 
[Machine]: [q2, q3, 0 -> x, R], 
[Machine]: [q3, q4, 0 -> 0, R], 
[Machine]: [q4, q3, 0 -> x, R], 
[Machine]: [q3, q5, blank -> blank, L], 
[Machine]: [q5, q5, x -> x, L], 
[Machine]: [q5, q5, 0 -> 0, L], 
[Machine]: [q5, q5, x -> x, L], 
[Machine]: [q5, q2, blank -> blank, R], 
[Machine]: [q2, q2, x -> x, R], 
[Machine]: [q2, q3, 0 -> x, R], 
[Machine]: [q3, q3, x -> x, R], 
[Machine]: [q3, q5, blank -> blank, L], 
[Machine]: [q5, q5, x -> x, L], 
[Machine]: [q5, q5, x -> x, L], 
[Machine]: [q5, q5, x -> x, L], 
[Machine]: [q5, q2, blank -> blank, R], 
[Machine]: [q2, q2, x -> x, R], 
[Machine]: [q2, q2, x -> x, R], 
[Machine]: [q2, q2, x -> x, R], 
[Machine]: [q2, q6, blank -> blank, R]
[Main]: DTM accepts on input
[Main]: ..
[Main]: run DTM again? [y/n]  n
Program ended with exit code: 0
```
