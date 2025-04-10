# Hash Table (Single List Model) – C++ Implementation

This project presents an alternative hash table implementation that stores all elements in a **single linked list**, offering a simplified memory model for managing collisions and entry lookup.

## Key Features

- Custom hash table using a single global list (no buckets)
- Supports insertion and search operations
- Reads input from text files
- Emphasizes memory simplicity and linear lookup for collisions
- Built with Visual Studio `.sln`

## Technologies Used

- C++ (OOP and STL-free logic)
- File I/O for input loading
- Visual Studio project (.sln, .vcxproj)

## How to Run

1. Open `hash7.sln` in Visual Studio.
2. Build the project (Ctrl + Shift + B).
3. Run the program (F5) and test using sample file input or manual entry.

## Design Note

Unlike traditional hash tables that use multiple buckets (each with a separate list), this design:
- Relies on **a single global list**
- Performs lookups by traversing this list
- Simplifies memory management and debug logic

## Learning Outcomes

- Hash table design trade-offs
- Linear collision handling via a unified structure
- File-based data processing
