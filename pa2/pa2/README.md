# Command Description

> You can compile and run the code with the following commands under root directory **b09901080_pa2**.
  
## Compile
* Compile all executables just with **make** command.
    ```bash
    # Compile bin/mps
    make
    ```

## Run mps
* Commands are in the following format:
    ```bash
    # Run bin/mps
    ./bin/mps inputs/<input_file_name> outputs/<output_file_name>
    ```
* For example, run mps to **inputs/12.in** and export result as **outputs/12.out** with
    ```bash
    # Import from inputs/12.in
    # Export to outputs/12.out
    ./bin/mps inputs/12.in outputs/12.out
    ```

## Remove All Executables
* Remove **bin/mps**.
    ```bash
    make clean
    ```
## Remove All Output Files
* Remove **outputs/*.out**
    ```bash
    make rmout
     ```
