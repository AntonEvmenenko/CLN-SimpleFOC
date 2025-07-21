import os
import shutil

Import("env")

def replace_canopen_od():
    # Get the directory where the script is located
    root_dir = env.get("PROJECT_DIR")
    print(f"Project root directory = {root_dir}")

    # Define source and destination directories
    src_dir = os.path.abspath(os.path.join(root_dir, "src/CANopen/OD"))
    dst_dir = os.path.abspath(os.path.join(root_dir, "lib/CanOpenSTM32-wrapper/CanOpenSTM32/CANopenNode_STM32"))

    # List of files to copy
    files = ["OD.c", "OD.h"]

    for file_name in files:
        src_file = os.path.join(src_dir, file_name)
        dst_file = os.path.join(dst_dir, file_name)

        try:
            # Copy the file with metadata, overwriting the destination if it exists
            shutil.copy2(src_file, dst_file)
            print(f"File '{file_name}' was successfully copied to the destination.")
        except FileNotFoundError:
            print(f"Source file '{src_file}' was not found.")
        except Exception as e:
            print(f"Error copying '{file_name}': {e}")

replace_canopen_od()