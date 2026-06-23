# Simple ATM System

A console-based ATM simulation built in C++ that supports account creation, PIN-authenticated login, and core banking operations using file-based persistent storage.

---

## Features

- **Create Account** — Register with an account number, name, 4-digit PIN, and starting balance
- **Secure Login** — PIN verification with a 3-attempt lockout policy
- **Balance Inquiry** — View current account balance
- **Withdraw** — Withdraw funds with a $20,000 per-transaction limit
- **Fast Cash** — Quick withdrawal presets ($500 – $5,000)
- **Deposit** — Add funds to your account
- **Persistent Storage** — All account data is saved to and read from `account.txt`

---

### Prerequisites
- A C++ compiler (g++, MSVC, or Clang)

### Compile & Run

```bash
g++ atm.cpp -o atm
./atm
```

---

## Usage

```
========================================
     WELCOME TO SIMPLE ATM SYSTEM
========================================

===== MAIN MENU =====
1. Create Account
2. Login
3. Exit
```

1. Select **Create Account** to register a new user
2. Select **Login** and enter your account number and PIN
3. Use the ATM menu to perform transactions

---

## File Structure

```
├── main.cpp          # Main source file
└── account.txt      # Auto-generated data file (created on first run)
```

---

## Limitations

- Data is stored in plain text — not suitable for production use
- No encryption on PINs or balances
- Single-file storage; not designed for concurrent access

---

## Tech Stack

**Language:** C++ 
**I/O:** File streams (`fstream`) 
**Standard:** C++11
