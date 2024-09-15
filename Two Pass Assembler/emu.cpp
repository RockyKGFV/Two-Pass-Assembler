// Author Name: VISHWAS S
//ROLL NUMBER :- 2201CS78

#include <bits/stdc++.h>
using namespace std;

// Vector to store machine codes
vector<int> MachineCodes;

// Array to simulate memory
int memory[1 << 24];

// Registers
int A, B, PC, SP, lines = 0;

// Pair to store read/write information
pair<int, int> rwPair;

// All operations according to the ISA given

// Load Constant: Load a constant value into register A
void ldc(int value) {
    B = A;
    A = value;
}

// Add Constant: Add a constant value to register A
void adc(int value) {
    A += value;
}

// Load Local: Load a value from memory into register A
void ldl(int offset) {
    B = A;
    A = memory[SP + offset];
    rwPair = {SP + offset, 0}; // Store read information
}

// Store Local: Store the value in register A into memory
void stl(int offset) {
    rwPair = {SP + offset, memory[SP + offset]}; // Store write information
    memory[SP + offset] = A;
    A = B;
}

// Load Non-Local: Load a value from memory into register A
void ldnl(int offset) {
    A = memory[A + offset];
    rwPair = {SP + offset, 0}; // Store read information
}

// Store Non-Local: Store the value in register B into memory
void stnl(int offset) {
    rwPair = {SP + offset, memory[SP + offset]}; // Store write information
    memory[A + offset] = B;
}

// Add: Add the values in registers A and B
void add(int value) {
    A += B;
}

// Subtract: Subtract the value in register A from register B
void sub(int value) {
    A = B - A;
}

// Shift Left: Shift the value in register B left by the value in register A
void shl(int value) {
    A = B << A;
}

// Shift Right: Shift the value in register B right by the value in register A
void shr(int value) {
    A = B >> A;
}

// Adjust: Adjust the stack pointer by a given value
void adj(int value) {
    SP += value;
}

// A to SP: Move the value in register A to the stack pointer
void a2sp(int value) {
    SP = A;
    A = B;
}

// SP to A: Move the value in the stack pointer to register A
void sp2a(int value) {
    B = A;
    A = SP;
}

// Call: Call a subroutine at a given offset
void call(int offset) {
    B = A;
    A = PC;
    PC += offset;
}

// Return: Return from a subroutine
void ret(int value) {
    PC = A;
    A = B;
}

// Branch if Zero: Branch to a given offset if the value in register A is zero
void brz(int offset) {
    if (A == 0) {
        PC += offset;
    }
}

// Branch if Less than Zero: Branch to a given offset if the value in register A is less than zero
void brlz(int offset) {
    if (A < 0) {
        PC += offset;
    }
}

// Branch: Branch to a given offset
void br(int offset) {
    PC += offset;
}

// Halt: Stop execution
void halt(int value) {
    // stop
    return;
}

// Vector of mnemonics
vector<string> mnemonics = {"ldc", "adc", "ldl", "stl", "ldnl", "stnl", "add", "sub", "shl", "shr", "adj", "a2sp", "sp2a", "call", "return", "brz", "brlz", "br", "HALT"};

// Array of function pointers to call respective functions for each operation
void (*func[])(int value) = {ldc, adc, ldl, stl, ldnl, stnl, add, sub, shl, shr, adj, a2sp, sp2a, call, ret, brz, brlz, br, halt};

// Opcode table
map<string, pair<string, int> > opTab; // {mnemonic, opcode, type of operand}

// Function to fill the opcode table
void fillOpcodeTable() {
    // Initialize the opcode table with mnemonics, opcodes, and operand types
    opTab = {{"data", {"", 1}}, 
             {"ldc", {"00", 1}}, 
             {"adc", {"01", 1}}, 
             {"ldl", {"02", 2}},
             {"stl", {"03", 2}}, 
             {"ldnl", {"04", 2}}, 
             {"stnl", {"05", 2}}, 
             {"add", {"06", 0}},
             {"sub", {"07", 0}}, 
             {"shl", {"08", 0}}, 
             {"shr", {"09", 0}}, 
             {"adj", {"0A", 1}},
             {"a2sp", {"0B", 0}}, 
             {"sp2a", {"0C", 0}}, 
             {"call", {"0D", 2}}, 
             {"return", {"0E", 0}},
             {"brz", {"0F", 2}}, 
             {"brlz", {"10", 2}}, 
             {"br", {"11", 2}}, 
             {"HALT", {"12", 0}},
             {"SET", {"", 1}}};
}

// Function to convert a decimal number to an 8-bit hexadecimal string
string decToHex(int num) {
    stringstream sss;
    sss << hex << setw(8) << setfill('0') << num; // Set width while converting the number in stream to hex
    string result = sss.str();
    return result;
}

// Function to throw an error
void throwError() {
    cout << "Segmentation Fault (or maybe infinite loop)" << endl;
    cout << "Please check your code" << endl;
    exit(0);
}

// Function to print the registers
void Trace(ofstream& outfile) {
    // Write values to file
    outfile << "PC = " << std::setfill('0') << std::setw(8) << std::hex << PC << ", ";
    outfile << "SP = " << std::setfill('0') << std::setw(8) << std::hex << SP << ", ";
    outfile << "A = " << std::setfill('0') << std::setw(8) << std::hex << A << ", ";
    outfile << "B = " << std::setfill('0') << std::setw(8) << std::hex << B << std::endl;

    printf("PC = %08X, SP = %08X, A = %08X, B = %08X ", PC, SP, A, B);
    // cout << endl;
}

// Function to print a read operation
void Read() {
    cout << "Reading memory[" << decToHex(rwPair.first) << "] finds " << decToHex(A) << endl;
}

// Function to print a write operation
void Write() {
    cout << "Writing memory[" << decToHex(rwPair.first) << "] was " << decToHex(rwPair.second) << " now " << decToHex(memory[rwPair.first]) << endl;
}

// Function to print the memory before execution
void Before() {
    cout << "memory dump before execution" << endl;
    for (int i = 0; i < (int)MachineCodes.size(); i += 4) {
        cout << decToHex(i) << " ";
        for (int j = i; j < min((int)MachineCodes.size(), i + 4); ++j) {
            cout << decToHex(MachineCodes[j]) << " ";
        }
        cout << endl;
    }
}

// Function to print the memory after execution
void After() {
    cout << "memory dump after execution" << endl;
    for (int i = 0; i < (int)MachineCodes.size(); i += 4) {
        cout << decToHex(i) << " ";
        for (int j = i; j < min((int)MachineCodes.size(), i + 4); ++j) {
            cout << decToHex(memory[j]) << " ";
        }
        cout << endl;
    }
}

// Function to reset the registers
void Wipe() {
    A = B = SP = PC = 0;
}

// Function to print the instruction set architecture
void ISA() {
    cout << "Opcode Mnemonic Operand" << '\n';
    cout << "0      ldc      value " << "\n";
    cout << "1      adc      value " << "\n";
    cout << "2      ldl      value " << "\n";
    cout << "3      stl      value " << "\n";
    cout << "4      ldnl     value " << "\n";
    cout << "5      stnl     value " << "\n";
    cout << "6      add            " << "\n";
    cout << "7      sub            " << "\n";
    cout << "9      shr            " << "\n";
    cout << "10     adj      value " << "\n";
    cout << "11     a2sp           " << "\n";
    cout << "12     sp2a           " << "\n";
    cout << "13     call     offset" << "\n";
    cout << "14     return         " << "\n";
    cout << "15     brz      offset" << "\n";
    cout << "16     brlz     offset" << "\n";
    cout << "17     br       offset" << "\n";
    cout << "18     HALT           " << "\n";
    cout << "       SET      value " << "\n";
}

// Function to execute an instruction
bool executeInstruction(int currentLine, int flag, ofstream& outfile) {
    int opcode = (currentLine & 0xFF);
    int value = (currentLine - opcode);
    value >>= 8;
    ++lines;
    (func[opcode])(value);
    if ((PC < 0) or (PC > (int)MachineCodes.size()) or (lines > (1 << 24))) {
        throwError();
        return true;
    }
    if (flag == 0) {
        Trace(outfile);
        cout << mnemonics[opcode] << " ";
        if (opTab[mnemonics[opcode]].second > 0) cout << decToHex(value);
        cout << endl;
    } else if (flag == 1 and (opcode == 2 or opcode == 4)) Read();
    else if (flag == 2 and (opcode == 3 or opcode == 5)) Write();
    if (opcode >= 18) return true;
    return false;
}

// Function to run the emulator for each line of code
void Run(int flag, ofstream& outfile) {
    // Loop until the end of the machine code is reached
    while (PC < (int)MachineCodes.size()) {
        int currentLine = MachineCodes[PC++];
        bool toQuit = executeInstruction(currentLine, flag, outfile);
        if (toQuit) break;
    }
}

// Function to execute a command
void executeCommand(string command, ofstream& outfile) {
    if (command == "-trace") {
        Run(0, outfile);
        cout << "Program execution finished!" << endl << "Trace File Generated" << endl;
    } else if (command == "-read") Run(1, outfile);
    else if (command == "-write") Run(2, outfile);
    else if (command == "-before") {
        Run(3, outfile);
        Before(); 
    } else if (command == "-after") {
        Run(3, outfile);
        After();
    } else if (command == "-wipe") Wipe();
    else if (command == "-isa") ISA();
    else {
        cout << "Invalid command" << endl;
        exit(0);
    }
    cout << lines << " instructions executed" << endl;
}

// Function to extract the filename without the extension
string extractFilenameWithoutExtension(const std::string& filename) {
    // Find the position of the last '.' character
    size_t dotPos = filename.find_last_of(".");
    if (dotPos == std::string::npos) {
        // If no dot is found, return the entire string
        return filename;
    } else {
        // Return the substring before the last '.'
        return filename.substr(0, dotPos);
    }
}

// Function to read input from a .o file
void takeInput(string filename) {
    ifstream file(filename, ios::in | ios::binary);
    unsigned int cur;
    int counter = 0;
    while (file.read((char*)&cur, sizeof(int))) { 
        MachineCodes.push_back(cur);
        memory[counter++] = cur;
    }
}

// Main function
int main(int argc, char* argv[]) {
    if (argc <= 2) {
        cout << "Invalid Format" << endl;
        cout << "Expected format: ./emu [command] filename.o" << endl;
        cout << "Commands are " << endl;
        cout << "-trace  show instruction trace" << endl;
        cout << "-read   show memory reads" << endl;
        cout << "-write  show memory writes" << endl;
        cout << "-before show memory dump before execution" << endl;
        cout << "-after  show memory dump after execution" << endl;
        cout << "-wipe   wipe written flags before execution" << endl;
        cout << "-isa    display ISA" << endl;
        return 0;
    }
    string filename = argv[2];
    string tracefilename = extractFilenameWithoutExtension(filename) + ".trace";
    // Open file for writing
    std::ofstream outfile(tracefilename);
    fillOpcodeTable();
    takeInput(filename);
    string command = argv[1];
    executeCommand(command, outfile);
    return 0;
}
