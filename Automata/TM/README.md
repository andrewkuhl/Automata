# Turing Machine           <div style="text-align: right">[back](https://github.com/andrewkuhl/Automata)</div>

### PDA( Q , E , G , d , q0 , F ) where:
### Q : finite set of states
### E : finite input alphabet
### G : finite stack alphabet
### d : Q x E<sub>eps</sub> x G<sub>eps</sub> &rarr; P(Q x G<sub>eps</sub>) is transition function
### q0: is the start state
### F in Q: is the set of final states

<br>

## Machine Specification File e.g.
```
Q{ q1 q2 q3 q4 }
E{ 0 1 }
G{ 0 1 $ }
d{
q1 q2 eps eps -> $ ,
q2 q2 0 eps -> 0 ,
q2 q3 1 0 -> eps ,
q3 q3 1 0 -> eps ,
q3 q4 eps $ -> eps
}
q0{ q1 }
F{ q1 q4 }
```

## Input File e.g.
```
input{ 0 0 0 0 0 0 1 1 1 1 1 1 }
```
