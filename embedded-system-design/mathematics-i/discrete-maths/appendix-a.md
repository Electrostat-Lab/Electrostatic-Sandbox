# Discrete Mathematics I: Appendix-A: Symbolic Designation for mathematical analysis

<div align=center><img src="https://electrostat-lab.github.io/Mathematics-I/discrete-maths/archive/algorithm-analysis-using-machines.jpg" width=550 height=850/></div>

## The following is the symbolic designation legend to aid in the subsequent mathematical analysis: 
- $N_c$: the number of times of execution of the closure $c$ imposed by the enclosing executing environment $E_e$ or the superclosure.
- $E_{e}$: the superclosure of the current closure that is of interest; the superclosure defines the executing environment that imposes the syntactical interpretation of iterations and machine transitions.
- $C_c$: the clock-complexity function; defines the number of cycles needed by the CPU to execute a set of machines inside an environment.
- ${\tau\}$: the transition-complexity function; defines the approximate clock-complexity taken by some machinery transitions among a set of specified machinery states (e.g., $M_{\alpha} = [\{\mu}_n, \{\mu}\_{n+1}, ..., \{\mu}\_{N-1}, \{\mu}\_{N}]$), and it follows that the transition-complexity function formula is the same as the clock-complexity function formula (i.e., ${\{\tau\}\'\}\_n = {C^{''}}_c$).
- $t_c$: the physical time-complexity function; defines the approximate time taken in seconds to execute the specified runnable set of machines in seconds unit.
- ${\epsilon}$: the error rate complexity function; defines the error rate as a result of calculating the exact physical time taken to execute some machines.

## The following is the generalized formula: 

$$Since, N_c = \prod_{i=1}^I E_{e_i}$$

$$C_c = N_c * \sum_{n=1}^N {\tau}\_n$$

- Such that, ${\tau}\_n = C'_c$, and ${\{\tau\}\'\}\_n = {C^{''}}_c$, and so on; as it represents the transition between machinery states, so this is a recursive formula re-evaluating on the most inner closures.

$$Then, C_c = \prod_{i=1}^I E_{e_i} * \sum_{n=0}^N {\tau}\_n = (E_{e_1} * E_{e_2} * ... * E_{e_{I-1}} * E_{e_{I}}) * ({\tau}\_{1} + {\tau}\_{2}  + ... + {\tau}\_{(N-1)} + {\tau}\_{(N)})$$

$$And, t_c = (C_c/F_{CPU}) + {\epsilon}$$
