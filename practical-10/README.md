# Practical 10: Custom Exceptions: Banking Transaction

- **Student Name:** Satinderpal Singh Chaney
- **Roll Number:** E26B00S2034

## Aim
To practise reporting application-specific failures and handling different errors in a controlled way.

## Question
Create a custom exception hierarchy and throw/catch specific exceptions in a banking transaction program.

## Custom Exception Hierarchy & What Each Exception Represents

```text
std::exception
  └── BankingException   (Base domain exception for banking errors)
        ├── InvalidAmount       (Withdrawal/deposit amount <= 0)
        └── InsufficientFunds   (Requested withdrawal > available balance)
```

- **`BankingException`:** Base exception class derived from `std::exception` that stores a descriptive error message and overrides `what()`.
- **`InvalidAmount`:** Represents invalid user input where a requested transaction amount is zero or negative (`amount <= 0`).
- **`InsufficientFunds`:** Represents a business-rule violation where a valid positive withdrawal exceeds the account's current `balance_`.
- **Exception Safety Guarantee:** `BankAccount::withdraw()` validates both conditions *before* mutating `balance_`, ensuring that failed transactions leave the account balance completely unchanged (`Rs. 8000`).

## Compilation & Execution

### Windows (PowerShell / MinGW `g++`)
```powershell
g++ -std=c++17 -Wall -Wextra practical10.cpp -o practical10.exe
.\practical10.exe
```

### Linux / macOS (`g++` / `clang++`)
```bash
g++ -std=c++17 -Wall -Wextra practical10.cpp -o practical10
./practical10
```

## Memory-Checking Instructions

### Option 1: AddressSanitizer & UndefinedBehaviorSanitizer (GCC / Clang — Linux, macOS, WSL)
```bash
g++ -std=c++17 -g -O1 -fsanitize=address,undefined practical10.cpp -o practical10_asan
./practical10_asan
```

### Option 2: Valgrind (Linux / WSL)
```bash
g++ -std=c++17 -g practical10.cpp -o practical10_dbg
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./practical10_dbg
```
Expected summary: `All heap blocks were freed -- no leaks are possible` and `0 errors from 0 contexts`.

## Uploading to GitHub
1. Create a new repository on GitHub (for example, `practical-10-custom-exceptions-banking` or `practical 10`).
2. Extract the ZIP archive into a local folder and push:
   ```bash
   git init
   git add .
   git commit -m "Add Practical 10: Custom Exceptions - Banking Transaction"
   git branch -M main
   git remote add origin <YOUR_GITHUB_REPOSITORY_URL>
   git push -u origin main
   ```
