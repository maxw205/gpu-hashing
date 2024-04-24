import random
import os

def generate_random_text(size_in_mb, filename):
    # Calculate the size in bytes
    size_in_bytes = size_in_mb * 1024 * 1024

    # Characters to choose from
    chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 \n'

    # Open the file in write mode
    with open(filename, 'w') as file:
        while os.path.getsize(filename) < size_in_bytes:
            # Write random characters to the file
            file.write(''.join(random.choice(chars) for _ in range(1024)))  # Writing 1024 chars at a time

# Usage
generate_random_text(100, 'random_text6.txt')
