# Quantum State Vector Simulator (C++17)
A lightweight $N$-qubit quantum circuit simulator built from scratch using pure C++17 standard libraries.

I built this project to dive deep into quantum computing fundamentals—exploring how linear algebra, complex state vectors, and measurement probabilities actually work under the hood without relying on external high-level frameworks.

Created for my research project at the **Minor Academy of Sciences of Ukraine (MAN)** and featured in my **MIT Maker Portfolio**. *(And yes, picking the [MIT License](LICENSE) was an absolute non-negotiable pun).*

## What It Does
* **$N$-Qubit State Register:** Dynamically allocates state vectors in $2^N$-dimensional Hilbert space using `std::complex<double>`.
* **Quantum Gates Engine:** Applies pure unitary transformation matrices directly to state vectors:
  * **Hadamard ($H$):** Creates equal superposition states.
  * **Pauli-X ($X$):** Performs quantum NOT / bit-flip operations.
  * **Pauli-Z ($Z$):** Applies phase-flip transformations.
* **Born's Rule Calculations:** Computes exact measurement probability distributions ($P = \vert{}\psi\vert{}^2$).
* **Terminal State Visualizer:** Prints step-by-step state vector amplitudes directly to stdout.

## Math Behind the Code
1. **State Vector Representation:**
   $$\vert{}\psi\rangle = \sum_{i=0}^{2^N-1} \alpha_i \vert{}i\rangle \quad \text{where} \quad \alpha_i \in \mathbb{C}, \quad \sum \vert{}\alpha_i\vert{}^2 = 1$$

2. **Quantum Gate Application:**

$$U = \begin{pmatrix} u_{00} & u_{01} \\ u_{10} & u_{11} \end{pmatrix}$$

3. **Born's Rule:**
   $$P(\vert{}i\rangle) = \vert{}\alpha_i\vert{}^2 = \text{Re}(\alpha_i)^2 + \text{Im}(\alpha_i)^2$$

## Quick Start
You only need a modern C++ compiler supporting C++17 (`clang++` or `g++`). No heavy external dependencies required!

```bash
# Clone the repository
git clone https://github.com/thaissh/quantum-simulator.git

# Compile the engine
g++ -std=c++17 main.cpp -o quantum_sim

# Run the simulator
./quantum_sim
