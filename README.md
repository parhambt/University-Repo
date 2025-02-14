# Judge Script README

This script is used to compile and run tests for your code, and then compare the results against expected outputs.

## Setup

1. **Place `judge.sh` in the same directory** as your `src` folder.

2. **Make `judge.sh` executable**:
   - In the terminal, run the following command to make the script executable:

     ```bash
     chmod +x judge.sh
     ```

3. **Prepare your tests**:
   - Create a `tests` folder in the same directory as `judge.sh`.
   - Inside the `tests` folder, create subfolders for each test case. Each subfolder should contain:
     - An input file (e.g., `01.in`) that provides input to your program.
     - An output file (e.g., `01.out`) that contains the expected output for your program.

   Example directory structure:

   ```text
    .
    ├── README.md
    ├── judge.sh
    ├── src
    │   └── main.cpp
    └── tests
        ├── 01
        │   ├── 01.in
        │   └── 01.out
        ├── 02
        │   ├── 02.in
        │   └── 02.out
        └── ...
   ```

## How to Run Tests

1. Open a terminal.

2. **Run the tests** by executing the following command:

   ```bash
   ./judge.sh -t
   ```

3. The script will:
   - Compile your code.
   - Run each test case (using the `.in` file as input).
   - Compare the output against the expected `.out` file.
   - Print whether each test passed or failed, along with details for any failed tests.

## After Testing

- Once the script finishes running, check the output in the terminal.
  - **Passed tests** will be marked as "Accepted".
  - **Failed tests** will show "Wrong answer" along with a diff of the differences if available.

## Cleaning Up

1. **Remove test outputs and diffs** (if needed) by running:

   ```bash
   ./judge.sh -r
   ```

   This will delete any `.result` and `.diff` files generated during the tests.
