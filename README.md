# miniGEMM

This is a prototype, miniature version of the GEneral Matrix Multiply (GEMM), a routine used in Basic Linear Algebra Subprograms (BLAS) specifications. In this project, we aim to provide an intelligent systems implementation of the algorithm, as well as show a performance comparison with the brute force variant of this algorithm.

# Introduction

The level 3 implementation of BLAS specifies the GEMM operation. Given a matrix $C \in \mathbb{R}^{n \times m}$, we perform this update operation by taking in parameters $A \in \mathbb{R}^{n \times k}, B \in \mathbb{R}^{k \times m}, \alpha, \beta \in \mathbb{R}$, via the update rule,

$C \gets \alpha AB + \beta C$.

While this is cumbersome, it nicely generalizes many other linear algebra operations.

\begin{itemize}
\item{If $\alpha = 0$, this is scalar multiplication on $C$.}
\end{itermize}
