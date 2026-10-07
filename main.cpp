/*

Quantum State Vector Simulator

An N-qubit state vector simulator modeling quantum registers and gate
operations using exact linear algebra and matrix multiplication.

Mathematical Foundations:
State Representation: |ψ⟩ ∈ ℂ^(2^N)
 
Quantum Gates: Unitary 2x2 matrices applied via tensor/pairwise products
Measurement Probabilities: Born's Rule (P = |a + bi|^2 = norm(amplitude))

Language: C++17
 
*/



#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

//synonym for complex number (a+bi)
using Complex = std::complex<double>;

//synonym for qubit condition vector (complex numbers array)
using StateVector = std::vector<Complex>;

//synonym for gate matrix (two-dimentional array)
using Matrix = std::vector<std::vector<Complex>>;

//Register.
//It calculates for array size depending on qubit quantity
StateVector CreateRegister(int numQubits) {
    size_t stateSize = 1ULL << numQubits; // 2^N
    StateVector state(stateSize, Complex(0.0, 0.0));
    state[0] = Complex(1.0, 0.0); // 100% chance for |00...0>
    
    return state;
}

//Gate library

//Pauli-X (NOT) matrix
Matrix getGateX() {
    return {
        { Complex(0, 0), Complex(1, 0) },
        { Complex(1, 0), Complex(0, 0) }
    };
}
//Hadamard matrix
Matrix getGateH() {
    double invSqrt2 = 1.0 / std::sqrt(2.0);
    return {
        { Complex(invSqrt2, 0), Complex(invSqrt2, 0) },
        { Complex(invSqrt2, 0), Complex(-invSqrt2, 0) }
    };
}
//Pauli-Z (Phase flip) matrix
Matrix getGateZ() {
    return {
        { Complex(1, 0), Complex(0, 0) },
        { Complex(0, 0), Complex(-1, 0) }
    };
}

//Index to binary function
std::string toBinary(size_t index, int qubits) {
    std::string bin = "";
    for (int i = qubits - 1; i >= 0; --i) {
        bin += ((index >> i) & 1) ? '1' : '0';
    }
    return bin;
}



//Apply Gate engine
void applyGate(StateVector& state, const Matrix& gate, int targetQubit, int totalQubits) {
    size_t stateSize = state.size();
    size_t step = 1ULL << targetQubit;
    
    for (size_t i = 0; i < stateSize; i += 2 * step) {
        for (size_t j = 0; j < step; ++j) {
            size_t idx0 = i + j;
            size_t idx1 = i + j + step;
            
            Complex v0 = state[idx0];
            Complex v1 = state[idx1];
            
            state[idx0] = gate[0][0] * v0 + gate[0][1] * v1;
            state[idx1] = gate[1][0] * v0 + gate[1][1] * v1;
            
            std::cout << "Pair (|" << toBinary(idx0, totalQubits)
                        << ">, |" << toBinary(idx1, totalQubits) << ">):\n";
            std::cout << "  Input  : v0=" << v0 << ", v1=" << v1 << "\n";
            std::cout << "  Output : state[" << toBinary(idx0, totalQubits) << "] = " << state[idx0] << "\n";
            std::cout << "           state[" << toBinary(idx1, totalQubits) << "] = " << state[idx1] << "\n\n";
        }
    }
}

void printState (const StateVector& state, int qubits) {
    std::cout << "\n Current state vector \n";
    for (size_t i = 0; i < state.size(); ++i) {
        double prob = std::norm(state[i]);
        std::cout << "State |" << toBinary(i, qubits) << "> : "
        << "Ampl = " << state[i]
        << " | Prob = " << prob * 100 << "%\n";
    }
}

// MAIN
int main() {
    
    //Enter qubit quantity
    int qubits;
    
    std::cout << "Enter qubit quantity: ";
    std::cin >> qubits;
    
    StateVector myQubits = CreateRegister(qubits);
    std::cout << "\n[INFO] Register for " << qubits << " qubits created successfully!\n";
    std::cout << "[INFO] Size of state vector: " << myQubits.size() << " elements (2^" << qubits << ").\n";

    printState(myQubits, qubits);

    //Just a menu
    bool running = true;
    while (running) {
        std::cout << "CIRCUIT MENU \n";
        std::cout << "1. Apply Hadamard (H) gate\n";
        std::cout << "2. Apply Pauli-X (NOT) gate\n";
        std::cout << "3. Apply Pauli-Z (Phase) gate\n";
        std::cout << "4. Show current state vector\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            running = false;
            std::cout << "Exiting quantum simulator...\n";
            break;
        }

        if (choice >= 1 && choice <= 3) {
            int target;
            std::cout << "Enter target qubit index (0 to " << qubits - 1 << "): ";
            std::cin >> target;

            if (target < 0 || target >= qubits) {
                std::cout << "Invalid qubit index!\n";
                continue;
            }

            if (choice == 1) {
                applyGate(myQubits, getGateH(), target, qubits);
            } else if (choice == 2) {
                applyGate(myQubits, getGateX(), target, qubits);
            } else if (choice == 3) {
                applyGate(myQubits, getGateZ(), target, qubits);
            }

            printState(myQubits, qubits);

        } else if (choice == 4) {
            printState(myQubits, qubits);
        } else {
            std::cout << "Unknown option, try again.\n";
        }
    }

    return 0;
}
