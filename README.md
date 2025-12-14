# DOS Loan Management System

A 16-bit DOS-based loan management program written in x86 assembly. The application allows users to view, add, update, and delete loan records using a keyboard-driven interface.

---

## Requirements

* **DOSBox** (or any DOS-compatible emulator)
* A working build environment configured for the project (assembler + linker as provided)

---

## Mounting and Running in DOSBox

1. Open **DOSBox**.
2. Mount the project directory:

   ```
   mount c <path-to-project-folder>
   c:
   ```
3. Run the program by typing:

   ```
   build
   ```

---

## Controls / Navigation

* **Arrow Keys** – Navigate through loans and menu options
* **Enter** – Select / confirm an option

The interface is entirely keyboard-driven.

---

## Application Behavior Notes

* When performing **Update** or **Delete**, the operation is applied to **the last loan record that the cursor was pointing to**.
* Loan records are displayed per user, and navigation is bounded by the current loan count.
* Adding a loan appends it to the end of the selected user’s loan table.

---

## Features

* Multiple users with independent loan tables
* Add, update, and delete loan records
* Structured data storage using assembly `STRUC`
* Visual cursor highlighting for navigation

---

## Notes

* This program is intended to run in a **real-mode DOS environment**.
* Make sure DOSBox is configured with sufficient memory and correct mounting paths.

---

## Demo Video

A short demonstration of the program running in DOSBox is available on YouTube:

* **Demo:** [https://youtu.be/tDFyyxZqnvo](https://youtu.be/tDFyyxZqnvo)

This video showcases navigation, loan selection, and basic operations.

---

## Author / Project Context

This project was built as a low-level systems exercise focusing on:

* 16-bit x86 addressing modes
* Data structures in assembly
* Keyboard input handling
* Manual memory and pointer management

---

Enjoy exploring classic DOS-era programming!
